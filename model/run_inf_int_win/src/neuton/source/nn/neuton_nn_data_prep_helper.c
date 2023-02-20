#include "neuton_nn_data_prep_helper.h"
#include "neuton_nn_user_config_resolver.h"

#include "../../../neuton/include/neuton/neuton.h"
#include "../../../neuton_generated/neuton_user_data_prep_meta.inc.h"

//////////////////////////////////////////////////////////////////////////////

#if NEUTON_NN_DSP_FEATURES_USED_ARGS

#if NEUTON_NN_ALLOCATE_SPECTRUM_BUFFER
static neuton_input_t fht_spectrum_buffer_[DSP_FHT_WINDOW_SIZE];
#else
/** NULL buffer means "in-place" spectrum calculation */
#define fht_spectrum_buffer_     NULL
#endif

#define INIT_GET_FEATURE_ARG_CTX(get_argument, shift) \
    get_argument = get_feature_argument_; shift = 0 

static neuton_u8_t feature_args_shift_ = 0;

static void get_feature_argument_(neuton_dsp_pipeline_t ppln, neuton_u8_t feature_id,
                                neuton_u8_t args_num, void* p_args)
{
    NEUTON_UNUSED(ppln);
    NEUTON_UNUSED(feature_id);

    NEUTON_NN_LOG_DEBUG("Get %d argument for feature %d from pipeline %d:", args_num, feature_id, ppln);

#if NEUTON_NN_DSP_FEATURES_USED_SPECTRUM
    if ((ppln == NEUTON_DSP_PIPELINE_SPECTRAL) && (feature_id == NEUTON_DSP_SPECTR_FID_SPECTRUM))
    {
        NEUTON_NN_LOG_DEBUG("Initialize spectrum instance: window size %d\r\n", DSP_FHT_WINDOW_SIZE);
        neuton_dsp_rfht_init(p_args, DSP_FHT_SIN_TABLE, DSP_FHT_TANG_TABLE, DSP_FHT_REV_BIT_INDEX_TABLE, 
                            fht_spectrum_buffer_, DSP_FHT_WINDOW_SIZE, DSP_FHT_LOG_N);
        return;
    }
#endif

    neuton_input_t* p_out_args = (neuton_input_t*)p_args;

    *p_out_args = (neuton_input_t)DSP_FEATURES_CALCULATION_ARGS[feature_args_shift_];

    NEUTON_NN_LOG_DEBUG("value %zu\r\n", (size_t)*p_out_args);

    feature_args_shift_ += args_num;
}

#else

#define INIT_GET_FEATURE_ARG_CTX(get_argument, shift) \
    get_argument = NULL

#endif // NEUTON_NN_DSP_FEATURES_USED_ARGS

//////////////////////////////////////////////////////////////////////////////

#if NEUTON_NN_USE_DSP_FEATURES

neuton_u16_t extract_dsp_features(const neuton_input_t* p_input_window,
                                const neuton_u16_t uniq_feature_window_size,
                                const neuton_u16_t uniq_features_num,
                                neuton_feature_t* p_features)
{
    NEUTON_NN_LOG_DEBUG("Extract features for %d uniq inputs from window with %d samples\r\n", 
                        uniq_features_num, uniq_feature_window_size);

    neuton_dsp_get_feature_arg_cb_t get_argument_fn;
    INIT_GET_FEATURE_ARG_CTX(get_argument_fn, feature_args_shift_);

    neuton_feature_t* p_features_begin = p_features;
    neuton_u16_t extracted = 0;

    neuton_dsp_features_mask_t mask;
    mask.all = DSP_FEATURES_CALCULATION_MASK[0];

    for (neuton_u16_t i = 0; i < uniq_features_num; i++)
    {
    #if NEUTON_NN_USE_UNIQ_DSP_MASK
        mask.all = DSP_FEATURES_CALCULATION_MASK[i];
    #endif

        extracted = funcwrapper_extract_features(p_input_window, uniq_feature_window_size, 
                                                mask, get_argument_fn, p_features);
        p_features += extracted;
        p_input_window += uniq_feature_window_size;

        NEUTON_NN_LOG_DEBUG("Extracted %d features, for %d input column, last mask 0x%X\n",
                            extracted, i, mask.all);
    }
    
    return (neuton_u16_t)(p_features - p_features_begin);
}

//////////////////////////////////////////////////////////////////////////////

void scale_dsp_features(neuton_feature_t* p_features, neuton_u16_t num)
{
    neuton_feature_t feature;
    neuton_feature_t min;
    neuton_feature_t max;
    neuton_model_input_t* p_scaled = (neuton_model_input_t*)p_features;

#if (NEUTON_NN_MODEL_INPUT_BIT_SIZE > NEUTON_NN_INPUT_BIT_SIZE)
    for (neuton_i16_t i = num - 1; i >= 0; i--)
#else
    for (neuton_u16_t i = 0; i < num; i++)
#endif
    {
        min = DSP_FEATURES_SCALE_MIN[i];
        max = DSP_FEATURES_SCALE_MAX[i];
        feature = p_features[i];
    
        funcwrapper_clip_var(feature, min, max);

        p_scaled[i] = funcwrapper_scale_minmax(feature, min, max);

        NEUTON_NN_LOG_DEBUG("Scaling DSP feature %d with min %0.2f, max %0.2f\r\n", i, 
                            (neuton_f32_t)min, (neuton_f32_t)max);
    }
}

#endif // NEUTON_NN_USE_DSP_FEATURES
//////////////////////////////////////////////////////////////////////////////

#if NEUTON_NN_USE_LAG_FEATURES

#define USE_LAG_FROM_INPUT_FEATURE(index) \
   (bool)(INPUT_FEATURES_USED_FOR_LAGS_MASK[index >> 3] & (1U << (index % 8)))

void scale_lag_features(neuton_input_t* p_input_window,
                        const neuton_u16_t uniq_feature_window_size,
                        const neuton_u16_t uniq_features_num,
                        neuton_u16_t lag_features_num)
{
    neuton_input_t min = INPUT_FEATURES_SCALE_MIN[0];
    neuton_input_t max = INPUT_FEATURES_SCALE_MAX[0];

    neuton_model_input_t* p_scaled;
    neuton_input_t* p_lag_features;
    neuton_input_t feature;

#if (NEUTON_NN_MODEL_INPUT_BIT_SIZE > NEUTON_NN_INPUT_BIT_SIZE)

    const neuton_u16_t features_window_size = (uniq_features_num * uniq_feature_window_size);
    /** Set pointers to the end of the input window */
    p_scaled = ((neuton_model_input_t *)p_input_window) + features_window_size;
    p_input_window += features_window_size;

    for (neuton_i16_t i = uniq_features_num - 1; i >= 0; i--)
    {
        if (USE_LAG_FROM_INPUT_FEATURE(i))
        {
#if NEUTON_NN_USE_UNIQ_INPUT_SCALING
            min = INPUT_FEATURES_SCALE_MIN[i];
            max = INPUT_FEATURES_SCALE_MAX[i];
#endif
            p_lag_features = p_input_window;

            for (neuton_i16_t j = lag_features_num - 1; j >= 0; j--)
            {
                feature = p_lag_features[j];

                funcwrapper_clip_var(feature, min, max);

                p_scaled[j] = funcwrapper_scale_minmax(feature, min, max);
            }

            NEUTON_NN_LOG_DEBUG("Scaling of %d lag features with min %0.2f, max %0.2f\r\n",
                                lag_features_num, (neuton_f32_t)min, (neuton_f32_t)max);
        }
        p_input_window -= uniq_feature_window_size;
        p_scaled -= uniq_feature_window_size;
    }
#else
    p_scaled = (neuton_model_input_t*)p_input_window;

    for (neuton_u16_t i = 0; i < uniq_features_num; i++)
    {
        if (USE_LAG_FROM_INPUT_FEATURE(i))
        {
#if NEUTON_NN_USE_UNIQ_INPUT_SCALING
            min = INPUT_FEATURES_SCALE_MIN[i];
            max = INPUT_FEATURES_SCALE_MAX[i];
#endif
            p_lag_features = p_input_window + (uniq_feature_window_size - lag_features_num);

            for (neuton_u16_t j = 0; j < lag_features_num; j++)
            {
                feature = p_lag_features[j];

                funcwrapper_clip_var(feature, min, max);

                p_scaled[j] = funcwrapper_scale_minmax(feature, min, max);
            }

            NEUTON_NN_LOG_DEBUG("Scaling of %d lag features with min %0.2f, max %0.2f\r\n",
                                lag_features_num, (neuton_f32_t)min, (neuton_f32_t)max);
        }
        p_input_window += uniq_feature_window_size;
        p_scaled += uniq_feature_window_size;
    }
#endif // (NEUTON_NN_MODEL_INPUT_BIT_SIZE > NEUTON_NN_INPUT_BIT_SIZE)
}

#endif // NEUTON_NN_USE_LAG_FEATURES
//////////////////////////////////////////////////////////////////////////////

#if NEUTON_NN_USE_INPUT_FEATURES

void scale_inputs(neuton_input_t* p_input, neuton_u16_t num)
{
    neuton_input_t input;
    neuton_input_t min = INPUT_FEATURES_SCALE_MIN[0];
    neuton_input_t max = INPUT_FEATURES_SCALE_MAX[0];
    neuton_model_input_t* p_scaled = (neuton_model_input_t*)p_input;

#if (NEUTON_NN_MODEL_INPUT_BIT_SIZE > NEUTON_NN_INPUT_BIT_SIZE)
    for (neuton_i16_t i = num - 1; i >= 0; i--)
#else
    for (neuton_u16_t i = 0; i < num; i++)
#endif
    {
    #if NEUTON_NN_USE_UNIQ_INPUT_SCALING
        min = INPUT_FEATURES_SCALE_MIN[i];
        max = INPUT_FEATURES_SCALE_MAX[i];
    #endif

        input = p_input[i];

        funcwrapper_clip_var(input, min, max);

        p_scaled[i] = funcwrapper_scale_minmax(input, min, max);

        NEUTON_NN_LOG_DEBUG("Scaling input feature %d with min %0.2f, max %0.2f\r\n", 
                            i, (neuton_f32_t)min, (neuton_f32_t)max);
    }
}

#endif //NEUTON_NN_USE_INPUT_FEATURES
//////////////////////////////////////////////////////////////////////////////

neuton_u16_t input_scalings_num(void)
{
#if (NEUTON_NN_USE_LAG_FEATURES || NEUTON_NN_USE_INPUT_FEATURES)

    return (sizeof(INPUT_FEATURES_SCALE_MAX) / sizeof(INPUT_FEATURES_SCALE_MAX[0]));
#endif // (NEUTON_NN_USE_LAG_FEATURES || NEUTON_NN_USE_INPUT_FEATURES)

    return 0;
}

//////////////////////////////////////////////////////////////////////////////

const neuton_u8_t* get_usage_mask_for_inputs(void)
{
#if NEUTON_NN_USE_INPUT_WINDOW_MASKED
    return INPUT_FEATURES_USAGE_MASK;
#endif
    return NULL;
}
