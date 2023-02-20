#include "../../../neuton/include/neuton/nn/neuton_nn.h"
#include "../../../neuton/include/neuton/utils/neuton_utils.h"

#include "neuton_nn_data_prep_helper.h"
#include "neuton_nn_inference_engine.h"
#include "neuton_nn_user_config_resolver.h"

//////////////////////////////////////////////////////////////////////////////

struct neuton_inference_input_s
{
    /** Pointer to input data window */
    neuton_input_t* p_input_window;

    /** Numer of unique features in data window */
    neuton_u16_t uniq_features_num;

    /** Number of samples for one unique feature in input window */
    neuton_u16_t uniq_feature_window_size;
};

//////////////////////////////////////////////////////////////////////////////

#if NEUTON_NN_USE_INPUT_SLIDING_WINDOW
typedef neuton_osl_window_ctx_t neuton_input_data_window_ctx_t;
#else
typedef neuton_ordered_window_ctx_t neuton_input_data_window_ctx_t;
#endif

#if NEUTON_NN_USE_INPUT_WINDOW
static neuton_u8_t input_window_[NEUTON_NN_INPUTS_BUFFER_SIZE_BYTES] __NEUTON_ALIGNED;
static neuton_input_data_window_ctx_t window_ctx_;

#elif (NEUTON_NN_MODEL_INPUT_BIT_SIZE > NEUTON_NN_INPUT_BIT_SIZE)
static neuton_u8_t input_window_[NEUTON_NN_INPUTS_BUFFER_SIZE_BYTES] __NEUTON_ALIGNED;

#endif // NEUTON_NN_USE_INPUT_WINDOW

#if NEUTON_NN_USE_INPUT_WINDOW_MASKED
static const neuton_u8_t* p_input_usage_mask_ = NULL;
#endif

#if NEUTON_NN_USE_DSP_FEATURES
static neuton_u8_t extracted_features_[NEUTON_NN_DSP_FEATURES_BUFFER_SIZE_BYTES] __NEUTON_ALIGNED;
#else
static neuton_u8_t* extracted_features_ = NULL;
#endif // NEUTON_NN_USE_DSP_FEATURES

static neuton_inference_input_t input_ctx_ = {0U};

//////////////////////////////////////////////////////////////////////////////

void neuton_nn_setup(void)
{
#if NEUTON_NN_USE_INPUT_SLIDING_WINDOW
    /** Setup input features sliding window context  */
    neuton_osl_window_init(&window_ctx_, input_window_, 
                            NEUTON_NN_INPUT_FEATURE_WINDOW_SIZE, NEUTON_NN_INPUT_UNIQ_FEATURES_NUM,
                            NEUTON_NN_INPUT_FEATURE_WINDOW_SHIFT);

#elif NEUTON_NN_USE_INPUT_WINDOW
    /** Setup input features window context */
    neuton_ordered_window_init(&window_ctx_, input_window_,
             NEUTON_NN_INPUT_FEATURE_WINDOW_SIZE, NEUTON_NN_INPUT_UNIQ_FEATURES_NUM);

#endif // NEUTON_NN_USE_INPUT_SLIDING_WINDOW

#if NEUTON_NN_USE_INPUT_WINDOW_MASKED
    /** Setup inputs usage mask */
    p_input_usage_mask_ = get_usage_mask_for_inputs();
#endif
}

//////////////////////////////////////////////////////////////////////////////

neuton_inference_input_t* neuton_nn_feed_inputs(const neuton_input_t* p_input,
                                                neuton_u16_t num)
{
    if (p_input == NULL || (num < NEUTON_NN_INPUT_UNIQ_FEATURES_NUM))
        return NULL;

 /** Collect input features into a sliding window */
#if NEUTON_NN_USE_INPUT_SLIDING_WINDOW

    neuton_u16_t samples_num = num / NEUTON_NN_INPUT_UNIQ_FEATURES_NUM;
#if NEUTON_NN_USE_INPUT_SLIDING_WINDOW_MASKED
    /** Collect input features into a ordered sliding window, 
     * but not all of them are used for model inference */
    neuton_u16_t samples_left = funcwrapper_sliding_window_feed_bymask(&window_ctx_, p_input, 
                                                                    samples_num, p_input_usage_mask_);
#else

    neuton_u16_t samples_left = funcwrapper_sliding_window_feed(&window_ctx_, p_input, samples_num);
#endif // NEUTON_NN_USE_INPUT_SLIDING_WINDOW_MASKED

    if (samples_left > 0) { return NULL; }

    input_ctx_.p_input_window = (neuton_input_t*)window_ctx_.ord_win.p_window.generic;
    input_ctx_.uniq_features_num = window_ctx_.ord_win.uniq_features_collected;
    input_ctx_.uniq_feature_window_size = window_ctx_.ord_win.max_samples_num;

/** Collect input features into a data window */
#elif NEUTON_NN_USE_INPUT_WINDOW

    neuton_u16_t samples_num = num / NEUTON_NN_INPUT_UNIQ_FEATURES_NUM;
#if NEUTON_NN_USE_INPUT_WINDOW_MASKED
    /** Collect input features into a data window, 
    * but not all of them are used for model inference */
    neuton_u16_t samples_left = funcwrapper_window_feed_bymask(&window_ctx_, p_input, 
                                                                samples_num, p_input_usage_mask_);
#else

    neuton_u16_t samples_left = funcwrapper_window_feed(&window_ctx_, p_input, samples_num);
#endif

    if (samples_left > 0) { return NULL; }

    input_ctx_.p_input_window = (neuton_input_t*)window_ctx_.p_window.generic;
    input_ctx_.uniq_features_num = window_ctx_.uniq_features_collected;
    input_ctx_.uniq_feature_window_size = window_ctx_.max_samples_num;

#elif (NEUTON_NN_MODEL_INPUT_BIT_SIZE > NEUTON_NN_INPUT_BIT_SIZE)
    /** In case the model inputs bit size are larger than raw inputs bit size,
     *  we save raw inputs to a larger container for further upscaling to the model input */
    neuton_input_t* p_input_window = (neuton_input_t*)input_window_;
  
    for (neuton_u16_t i = 0; i < NEUTON_NN_INPUT_UNIQ_FEATURES_NUM; i++)
        p_input_window[i] = p_input[i];

    input_ctx_.p_input_window = p_input_window;
    input_ctx_.uniq_features_num = NEUTON_NN_INPUT_UNIQ_FEATURES_NUM;
    input_ctx_.uniq_feature_window_size = 1;

#else
    /** User input buffer is used for model inferenece */
    input_ctx_.p_input_window = (neuton_input_t*)p_input;
    input_ctx_.uniq_features_num = NEUTON_NN_INPUT_UNIQ_FEATURES_NUM;
    input_ctx_.uniq_feature_window_size = 1;
#endif // NEUTON_NN_USE_INPUT_SLIDING_WINDOW

    return &input_ctx_;
}

//////////////////////////////////////////////////////////////////////////////

neuton_i16_t neuton_nn_run_inference(neuton_inference_input_t* p_input, 
                                    neuton_u16_t* p_index, const neuton_output_t** pp_outputs)
{
    if ((p_input == NULL) || (p_input->p_input_window == NULL))
        return -1;

    neuton_feature_t* p_extracted_features = (neuton_feature_t*)extracted_features_;

#if NEUTON_NN_USE_DSP_FEATURES
    neuton_u16_t num;

    /** Extract DSP features from input window */
    num = extract_dsp_features(p_input->p_input_window, p_input->uniq_feature_window_size,
                                p_input->uniq_features_num, p_extracted_features);
    /** Scale extracted DSP features */
    scale_dsp_features(p_extracted_features, num);
#endif

#if NEUTON_NN_USE_LAG_FEATURES
    /** Scale lag features in the input window */
    scale_lag_features(p_input->p_input_window, p_input->uniq_feature_window_size,
                        p_input->uniq_features_num, NEUTON_NN_LAG_FEATURES_NUM);

#elif NEUTON_NN_USE_INPUT_FEATURES
    /** Scale original inputs features */
    scale_inputs(p_input->p_input_window, NEUTON_NN_INPUT_UNIQ_FEATURES_NUM);
#endif

    /** Model inference */
    nn_engine_make_inference(p_input->p_input_window, p_extracted_features);

    return nn_engine_get_inference_results(p_index, pp_outputs);
}

//////////////////////////////////////////////////////////////////////////////

neuton_u16_t neuton_nn_uniq_inputs_num(void)
{
    return NEUTON_NN_INPUT_UNIQ_FEATURES_NUM;
}

//////////////////////////////////////////////////////////////////////////////

neuton_u16_t neuton_nn_input_window_size(void)
{
    return NEUTON_NN_INPUT_FEATURE_WINDOW_SIZE; 
}

//////////////////////////////////////////////////////////////////////////////

neuton_u16_t neuton_nn_model_neurons_num(void)
{
    return NEUTON_NN_MODEL_NEURONS_NUM;
}

//////////////////////////////////////////////////////////////////////////////

neuton_u16_t neuton_nn_model_outputs_num(void)
{
    return NEUTON_NN_MODEL_OUTPUTS_NUM;
}

//////////////////////////////////////////////////////////////////////////////

neuton_u16_t neuton_nn_model_weights_num(void)
{
    return NEUTON_NN_MODEL_WEIGHTS_NUM; 
}

//////////////////////////////////////////////////////////////////////////////

neuton_nn_task_t neuton_nn_model_task(void)
{
    return (neuton_nn_task_t)(NEUTON_NN_MODEL_TASK_TYPE);
}

//////////////////////////////////////////////////////////////////////////////

neuton_u16_t neuton_nn_model_size(void)
{
    return nn_engine_model_size();
}

//////////////////////////////////////////////////////////////////////////////

neuton_u8_t neuton_nn_model_bitdepth(void)
{
    return NEUTON_NN_MODEL_QLVL;
}

//////////////////////////////////////////////////////////////////////////////

bool neuton_nn_model_inference_float_support(void)
{
    return (bool)NEUTON_NN_MODEL_FLOAT_SUPPORT;
}

//////////////////////////////////////////////////////////////////////////////

const char* neuton_nn_solution_id_str(void)
{
    return NEUTON_NN_MODEL_SOLUTION_ID_STR;
}

//////////////////////////////////////////////////////////////////////////////

neuton_nn_input_scaling_t neuton_nn_input_scaling(void)
{
    neuton_u16_t scaling_num = input_scalings_num();

    if (scaling_num > 1)
        return NEUTON_NN_INPUT_SCALING_UNIQUE;
    else if (scaling_num == 1)
        return NEUTON_NN_INPUT_SCALING_UNIFIED;
    else
        return NEUTON_NN_INPUT_SCALING_UNDEFINED;
}