#include "neuton_nn_inference_engine.h"
#include "neuton_nn_user_config_resolver.h"

#include "../../../neuton/include/neuton/neuton.h"
#include "../../../neuton_generated/neuton_user_model.inc.h"

//////////////////////////////////////////////////////////////////////////////

static neuton_coeff_t model_accumulators_[NEUTON_NN_MODEL_NEURONS_NUM];
static neuton_output_t model_outputs_[NEUTON_NN_MODEL_OUTPUTS_NUM];

//////////////////////////////////////////////////////////////////////////////

__NEUTON_STATIC_FORCEINLINE 
neuton_model_input_t get_neuron_input_(neuton_u16_t index,
                                        const neuton_input_t* p_input_features,
                                        const neuton_feature_t* p_extracted_features)
{
    static const neuton_u16_t INPUTS_COUNT = NEUTON_NN_INPUTS_WINDOW_SIZE;

#if (NEUTON_NN_USE_LAG_FEATURES || NEUTON_NN_USE_INPUT_FEATURES)
    if (index < INPUTS_COUNT)
    {
        neuton_model_input_t* p_neuron_inputs = (neuton_model_input_t*)p_input_features;
        return p_neuron_inputs[index];
    }
#else
    NEUTON_UNUSED(p_input_features);
    /** index of neuron input should be shifted by INPUTS_COUNT if inputs features is not used */
    index += INPUTS_COUNT;
#endif

#if NEUTON_NN_USE_DSP_FEATURES
    index -= INPUTS_COUNT;

    if (index < NEUTON_NN_DSP_FEATURES_NUM)
    {
        neuton_model_input_t* p_neuron_inputs = (neuton_model_input_t*)p_extracted_features;
        return p_neuron_inputs[index];
    }
#else
    NEUTON_UNUSED(p_extracted_features);
#endif

    return NEUTON_NN_NEURON_BIAS;
}

//////////////////////////////////////////////////////////////////////////////

static void denormalize_outputs_(neuton_output_t* p_outputs, neuton_u16_t outputs_num)
{
#if ((NEUTON_NN_MODEL_TASK_TYPE == NEUTON_NN_MODEL_TASK_BIN_CLASS) || \
    (NEUTON_NN_MODEL_TASK_TYPE == NEUTON_NN_MODEL_TASK_MULT_CLASS))

    NEUTON_NN_LOG_DEBUG("Denormalize %d outputs for classification task\r\n", outputs_num);

    neuton_f32_t sum = 0;

    for (neuton_u16_t i = 0; i < outputs_num; ++i)
        sum += p_outputs[i];

    if (sum > NEUTON_F32_EPSILON)
    {
        for (neuton_u16_t i = 0; i < outputs_num; ++i)
            p_outputs[i] = p_outputs[i] / sum;
    }
    else
    {
        NEUTON_NN_LOG_DEBUG("Sum of outputs is 0! Incorrect denormalization behaviour!\r\n");

        for (neuton_u16_t i = 0; i < outputs_num; ++i)
            p_outputs[i] = 0;
    }

#elif (NEUTON_NN_MODEL_TASK_TYPE == NEUTON_NN_MODEL_TASK_REGRESSION)

    NEUTON_NN_LOG_DEBUG("Denormalize %d outputs for regression task\r\n", outputs_num);

    for (neuton_u16_t i = 0; i < outputs_num; i++)
    {
       p_outputs[i] = p_outputs[i] * (MODEL_OUTPUT_SCALE_MAX[i] - MODEL_OUTPUT_SCALE_MIN[i]) + MODEL_OUTPUT_SCALE_MIN[i];

    #if NEUTON_NN_OUTPUTS_LOG_SCALED 
        if (MODEL_OUTPUT_SCALE_LOG_FLAGS[i])
            { p_outputs[i] = expf(p_outputs[i]) - MODEL_OUTPUT_SCALE_LOG[i]; }
    #endif
    }
    
#endif
}

//////////////////////////////////////////////////////////////////////////////

void nn_engine_make_inference(const neuton_input_t* p_input_features,
                                    const neuton_feature_t* p_extracted_features)
{
    NEUTON_NN_LOG_DEBUG("Run inference of model with %d neurons\r\n", NEUTON_NN_MODEL_NEURONS_NUM);

    neuton_weights_num_t weight_idx = 0;

    for (neuton_neurons_num_t neuron = 0; neuron < NEUTON_NN_MODEL_NEURONS_NUM; ++neuron)
    {
        neuton_accum_t sum = 0;
        neuton_weights_num_t boundary = MODEL_INTERNAL_LINKS_BOUNDARIES[neuron];

        while (weight_idx < boundary)
        {
            const neuton_2x_q_t weight = MODEL_WEIGHTS[weight_idx];
            const neuton_2x_q_t acc    = model_accumulators_[MODEL_LINKS[weight_idx]];

            sum += (weight * acc);
            ++weight_idx;
        }

        boundary = MODEL_EXTERNAL_LINKS_BOUNDARIES[neuron];

        while (weight_idx < boundary)
        {
            const neuton_2x_q_t weight = MODEL_WEIGHTS[weight_idx];
            const neuton_2x_q_t input  = get_neuron_input_(MODEL_LINKS[weight_idx],
                                                            p_input_features, p_extracted_features);
            
            sum += (weight * input);
            ++weight_idx;
        }

        model_accumulators_[neuron] = funcwrapper_activation(MODEL_ACTIVATION_COEFFS[neuron], sum);
    }
}

//////////////////////////////////////////////////////////////////////////////

neuton_i16_t nn_engine_get_inference_results(neuton_u16_t* index, 
                                            const neuton_output_t** pp_outputs)
{
    /** Dequantize output neurons */
    for (neuton_neurons_num_t i = 0; i < NEUTON_NN_MODEL_OUTPUTS_NUM; ++i)
    {
        neuton_coeff_t coeff = model_accumulators_[MODEL_OUTPUT_NEURONS[i]];
        model_outputs_[i] = funcwrapper_dequantize_outputs(coeff);
    }

    /** Denormalize outputs to get actual results */
    denormalize_outputs_(model_outputs_, NEUTON_NN_MODEL_OUTPUTS_NUM);

    /** Find index of predicted output with highest probabilities*/
    if (index)
    {
        neuton_u16_t target = 0;
        neuton_f32_t max = 0.0f;

        for (neuton_u16_t i = 0; i < NEUTON_NN_MODEL_OUTPUTS_NUM; ++i)
        {
            if (max < model_outputs_[i])
            {
                max = model_outputs_[i];
                target = i;
            }
        }
        *index = target;
        NEUTON_NN_LOG_DEBUG("Among the %d outputs the highest probability is %0.3f in %d index\r\n", 
                            NEUTON_NN_MODEL_OUTPUTS_NUM, max, target);
    }

    if (pp_outputs)
        *pp_outputs = model_outputs_;

    return NEUTON_NN_MODEL_OUTPUTS_NUM;
}

//////////////////////////////////////////////////////////////////////////////

#if (NEUTON_NN_MODEL_FLOAT_SUPPORT == 0)

neuton_coeff_t nn_activation_sigmoid_q(neuton_accum_t accum)
{
    neuton_coeff_t q_result = 0;
    neuton_coeff_t second_point_y = 0;
    neuton_coeff_t first_point_y = 0;

    static const uint8_t QLVL = NEUTON_NN_MODEL_QLVL;
    static const uint8_t QLVLM1 = QLVL - 1;

    const neuton_coeff_t int_part = abs(accum) / ((neuton_u32_t)(1) << QLVL);
    const neuton_coeff_t real_part = abs(accum) - (int_part << QLVL);

    if (int_part == 0 && real_part == 0)
    {
        return 1u << QLVLM1;
    }

    uint8_t s = accum < 0;
    uint8_t odd = 1;

    if (real_part == 0)
    {
        for (uint8_t i = 0; i < QLVL; i++)
        {
            const uint8_t bit = ((i / int_part + s) & odd);
            q_result = q_result | (bit << (QLVLM1 - i));
        }
        return q_result;
    }

    const neuton_coeff_t second_point_x = int_part + 1;
    if (int_part == 0)
    {
        first_point_y = 1u << QLVLM1;
        for (uint8_t i = 0; i < QLVL; i++)
        {
            const uint8_t bit = ((i / second_point_x) & odd);
            second_point_y = second_point_y | (bit << (QLVLM1 - i));
        }
    }
    else
    {
        if (second_point_x == 0)
        {
            for (uint8_t i = 0; i < QLVL; i++)
            {
                const uint8_t bit = ((i / int_part) & odd);
                first_point_y = first_point_y | (bit << (QLVLM1 - i));
            }
            second_point_y = 1u << QLVLM1;
        }
        else
        {
            for (uint8_t i = 0; i < QLVL; i++)
            {
                uint8_t bit = ((i / int_part) & odd);
                first_point_y = first_point_y | (bit << (QLVLM1 - i));
                bit = ((i / second_point_x) & odd);
                second_point_y = second_point_y | (bit << (QLVLM1 - i));
            }
        }
    }

    const neuton_coeff_t res = first_point_y + ((real_part * (second_point_y - first_point_y)) >> QLVL);
    if (s)
        return res == 0 ? NEUTON_NN_MODEL_INPUT_CT_MAX : NEUTON_NN_MODEL_INPUT_CT_MAX + 1 - res;

    return res;
}

#endif // (NEUTON_NN_MODEL_QTYPE != NEUTON_NN_MODEL_QTYPE_Q32)

//////////////////////////////////////////////////////////////////////////////

neuton_u32_t nn_engine_model_size(void)
{
    return (sizeof(MODEL_WEIGHTS) + 
            sizeof(MODEL_LINKS) + 
            sizeof(MODEL_INTERNAL_LINKS_BOUNDARIES) + 
            sizeof(MODEL_EXTERNAL_LINKS_BOUNDARIES) +
            sizeof(MODEL_ACTIVATION_COEFFS) + 
            sizeof(MODEL_OUTPUT_NEURONS));
}

//////////////////////////////////////////////////////////////////////////////