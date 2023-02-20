#ifndef _NEUTON_NN_USER_CONFIG_RESOLVER_H_
#define _NEUTON_NN_USER_CONFIG_RESOLVER_H_

#include "../../../neuton_generated/neuton_user_config.h"

#include "../../../neuton/include/neuton/neuton_platform.h"
#include <math.h>

/** Model neuron input */
typedef neuton_coeff_t neuton_model_input_t;

// ////////////////////// Data configuration resolver start //////////////////

/** Determines whether input data should be collected into a window for further preprocessing */
#define NEUTON_NN_USE_INPUT_WINDOW              (NEUTON_NN_INPUT_FEATURE_WINDOW_SIZE > 1)

/** Determines whether input data should be collected into a sliding window */
#define NEUTON_NN_USE_INPUT_SLIDING_WINDOW      ((NEUTON_NN_INPUT_FEATURE_WINDOW_SHIFT > 0) && \
                                                (NEUTON_NN_INPUT_FEATURE_WINDOW_SHIFT != NEUTON_NN_INPUT_FEATURE_WINDOW_SIZE))

/** Input feature buffer element size, 
 * if quantization of model is bigger than input features size in bits, 
 * the size of input buffer should aligned to neuton_model_input_t */
#define NEUTON_NN_INPUT_TYPE_SIZE               ((sizeof(neuton_input_t) > sizeof(neuton_model_input_t)) ? sizeof(neuton_input_t) : sizeof(neuton_model_input_t))

/** Determines whether input data should be collected into a window based on the specific "usage mask" */
#define NEUTON_NN_USE_INPUT_WINDOW_MASKED       (NEUTON_NN_USE_INPUT_WINDOW && \
                                                (NEUTON_NN_INPUT_UNIQ_FEATURES_USED_NUM < NEUTON_NN_INPUT_UNIQ_FEATURES_NUM))

#define NEUTON_NN_USE_INPUT_SLIDING_WINDOW_MASKED   (NEUTON_NN_USE_INPUT_SLIDING_WINDOW && NEUTON_NN_USE_INPUT_WINDOW_MASKED)

/** Determines whether neural network uses LAG features for inference  */
#define NEUTON_NN_USE_LAG_FEATURES              (NEUTON_NN_LAG_FEATURES_NUM > 0)

/** Determines whether neural network use extracted DSP features for inference */
#define NEUTON_NN_USE_DSP_FEATURES              (NEUTON_NN_DSP_FEATURES_NUM > 0)

/** DSP feature buffer element size, 
 * if quantization of model is bigger than DSP features size in bits, 
 * the size of extracted DSP features buffer should aligned to neuton_model_input_t */
#define NEUTON_NN_DSP_FEATURE_SIZE              ((sizeof(neuton_feature_t) > sizeof(neuton_model_input_t)) ? sizeof(neuton_feature_t) : sizeof(neuton_model_input_t))

/** Size of DSP features buffer in bytes */
#define NEUTON_NN_DSP_FEATURES_BUFFER_SIZE_BYTES (NEUTON_NN_DSP_FEATURES_NUM * NEUTON_NN_DSP_FEATURE_SIZE)

/** Determines whether there is a need of arguments while feature extraction */
#define NEUTON_NN_DSP_FEATURES_USED_ARGS        (NEUTON_DSP_PIPELINE_COMPUTE_TCR || NEUTON_DSP_PIPELINE_COMPUTE_P2P_LF_HF || \
                                                NEUTON_DSP_PIPELINE_COMPUTE_P2P_LF || NEUTON_DSP_PIPELINE_COMPUTE_P2P_HF || \
                                                NEUTON_NN_FEATURES_DSP_USED_SPECTRUM)

/** Determines whether there is a need of spectrum instance initialization */
#define NEUTON_NN_DSP_FEATURES_USED_SPECTRUM    (NEUTON_DSP_PIPELINE_COMPUTE_SPECTR_PEAKS_FREQ || NEUTON_DSP_PIPELINE_COMPUTE_SPECTR_PEAKS_AMPL)

/** Input features window size */
#define NEUTON_NN_INPUTS_WINDOW_SIZE            (NEUTON_NN_INPUT_UNIQ_FEATURES_USED_NUM * NEUTON_NN_INPUT_FEATURE_WINDOW_SIZE)

/** Size of input features buffer in bytes */
#define NEUTON_NN_INPUTS_BUFFER_SIZE_BYTES      (NEUTON_NN_INPUTS_WINDOW_SIZE * NEUTON_NN_INPUT_TYPE_SIZE)

#define NEUTON_NN_INPUT_TYPE_F32                0
#define NEUTON_NN_INPUT_TYPE_INT8               1
#define NEUTON_NN_INPUT_TYPE_INT16              2

/** If LAG features are used alongside with spectral features for NN inference,
 *  we cannot calculate spectrum "in-place" and should allocate external buffer for this
 */
#define NEUTON_NN_ALLOCATE_SPECTRUM_BUFFER      (NEUTON_NN_DSP_FEATURES_USED_SPECTRUM && NEUTON_NN_USE_LAG_FEATURES)

//////////////////////////////////////////////////////////////////////////////

#if (NEUTON_NN_INPUT_TYPE == NEUTON_NN_INPUT_TYPE_INT8)

#define NEUTON_NN_INPUT_BIT_SIZE                    8
#define funcwrapper_window_feed_bymask              neuton_ordered_window_feed_bymask_i8
#define funcwrapper_window_feed                     neuton_ordered_window_feed_i8
#define funcwrapper_sliding_window_feed_bymask      neuton_osl_window_feed_bymask_i8
#define funcwrapper_sliding_window_feed             neuton_osl_window_feed_i8
#define funcwrapper_extract_features                neuton_dsp_pipeline_compute_i8

#elif (NEUTON_NN_INPUT_TYPE == NEUTON_NN_INPUT_TYPE_INT16)

#define NEUTON_NN_INPUT_BIT_SIZE                    16
#define funcwrapper_window_feed_bymask              neuton_ordered_window_feed_bymask_i16
#define funcwrapper_window_feed                     neuton_ordered_window_feed_i16
#define funcwrapper_sliding_window_feed_bymask      neuton_osl_window_feed_bymask_i16
#define funcwrapper_sliding_window_feed             neuton_osl_window_feed_i16
#define funcwrapper_extract_features                neuton_dsp_pipeline_compute_i16

#elif (NEUTON_NN_INPUT_TYPE == NEUTON_NN_INPUT_TYPE_F32)

#define NEUTON_NN_INPUT_BIT_SIZE                    32
#define funcwrapper_window_feed_bymask              neuton_ordered_window_feed_bymask_f32
#define funcwrapper_window_feed                     neuton_ordered_window_feed_f32
#define funcwrapper_sliding_window_feed_bymask      neuton_osl_window_feed_bymask_f32
#define funcwrapper_sliding_window_feed             neuton_osl_window_feed_f32
#define funcwrapper_extract_features                neuton_dsp_pipeline_compute_f32   

#else
#error "NEUTON_NN_INPUT_TYPE undefined value!"
#endif

/** Is input type is integer value */
#define NEUTON_NN_INPUT_TYPE_INT                    ((NEUTON_NN_INPUT_TYPE == NEUTON_NN_INPUT_TYPE_INT8) || \
                                                    (NEUTON_NN_INPUT_TYPE == NEUTON_NN_INPUT_TYPE_INT16))

// ////////////////////// Data configuration resolver end ////////////////////

// ////////////////////// Model configuration resolver start ////////////////////

#define NEUTON_NN_MODEL_QTYPE_Q8                0
#define NEUTON_NN_MODEL_QTYPE_Q16               1
#define NEUTON_NN_MODEL_QTYPE_Q32               2

#define NEUTON_NN_MODEL_TASK_MULT_CLASS         0
#define NEUTON_NN_MODEL_TASK_BIN_CLASS          1
#define NEUTON_NN_MODEL_TASK_REGRESSION         2

#define NEUTON_MAX_INPUT_F32                    0.9999999f

//////////////////////////////////////////////////////////////////////////////

#define NEUTON_NN_PREPARE_QCOEFF(c,acc)             (-(((neuton_accum_t)c * acc) >> (NEUTON_NN_MODEL_QLVL + NEUTON_NN_MODEL_KSHIFT - 1)))

#if NEUTON_NN_USE_FEATURE_CLIPPING
#define funcwrapper_clip_var                    neuton_dsp_clip_var
#else
#define funcwrapper_clip_var(var, min, max);              
#endif

/** Model-type depended wrappers */
#if (NEUTON_NN_MODEL_QTYPE == NEUTON_NN_MODEL_QTYPE_Q32)

#define NEUTON_NN_MODEL_QLVL                        32
#define NEUTON_NN_MODEL_KSHIFT                      0
#define NEUTON_NN_NEURON_BIAS                       1.0f

#define funcwrapper_activation(c, accum)         nn_activation_exp_f32(c, accum)
#define funcwrapper_scale_minmax(var, min, max)  neuton_dsp_scale_minmax_fvar((neuton_f32_t)(var), (min), (max))
#define funcwrapper_dequantize_outputs(x)        (x)

#elif (NEUTON_NN_MODEL_QTYPE == NEUTON_NN_MODEL_QTYPE_Q8)

#define NEUTON_NN_MODEL_INPUT_CT_MAX             (((neuton_u16_t)1 << 8) - 1)
#define NEUTON_NN_MODEL_QLVL                     8
#define NEUTON_NN_MODEL_KSHIFT                   2
#define NEUTON_NN_NEURON_BIAS                    ((1U << NEUTON_NN_MODEL_QLVL) - 1)
#define funcwrapper_dequantize_outputs(x)        ((neuton_f32_t)(x) / (neuton_f32_t)((uint32_t)(1U) << NEUTON_NN_MODEL_QLVL))

#if NEUTON_NN_INPUT_TYPE_INT
#define funcwrapper_scale_minmax(var, min, max)  neuton_dsp_scale_minmax_ivar((var), NEUTON_NN_MODEL_INPUT_CT_MAX, (min), (max))
#else
#define funcwrapper_scale_minmax(var, min, max)  neuton_dsp_scale_minmax_qfvar((neuton_f32_t)(var), NEUTON_NN_MODEL_INPUT_CT_MAX, (min), (max))
#endif //NEUTON_NN_INPUT_TYPE_INT

#if NEUTON_NN_MODEL_FLOAT_SUPPORT
#define funcwrapper_activation(c, accum)         nn_activation_exp_q(c, accum)
#else
#define funcwrapper_activation(c, accum)         nn_activation_sigmoid_q(NEUTON_NN_PREPARE_QCOEFF(c, accum))
#endif // NEUTON_NN_MODEL_FLOAT_SUPPORT

#elif (NEUTON_NN_MODEL_QTYPE == NEUTON_NN_MODEL_QTYPE_Q16)

#define NEUTON_NN_MODEL_INPUT_CT_MAX             (((neuton_u32_t)1 << 16) - 1)
#define NEUTON_NN_MODEL_QLVL                     16
#define NEUTON_NN_MODEL_KSHIFT                   10
#define NEUTON_NN_NEURON_BIAS                    ((1U << NEUTON_NN_MODEL_QLVL) - 1)
#define funcwrapper_dequantize_outputs(x)        ((neuton_f32_t)(x) / (neuton_f32_t)((uint32_t)(1U) << NEUTON_NN_MODEL_QLVL))

#if NEUTON_NN_INPUT_TYPE_INT
#define funcwrapper_scale_minmax(var, min, max)  neuton_dsp_scale_minmax_ivar((var), NEUTON_NN_MODEL_INPUT_CT_MAX, (min), (max))
#else
#define funcwrapper_scale_minmax(var, min, max)  neuton_dsp_scale_minmax_qfvar((neuton_f32_t)(var), NEUTON_NN_MODEL_INPUT_CT_MAX, (min), (max))
#endif //NEUTON_NN_INPUT_TYPE_INT

#if NEUTON_NN_MODEL_FLOAT_SUPPORT
#define funcwrapper_activation(c, accum)         nn_activation_exp_q(c, accum)
#else
#define funcwrapper_activation(c, accum)         nn_activation_sigmoid_q(NEUTON_NN_PREPARE_QCOEFF(c, accum))
#endif // NEUTON_NN_MODEL_FLOAT_SUPPORT

#endif // NEUTON_NN_MODEL_TYPE

//////////////////////////////////////////////////////////////////////////////

#define NEUTON_NN_MODEL_INPUT_BIT_SIZE          NEUTON_NN_MODEL_QLVL
#define NEUTON_NN_QEXP_SHIFT                    (neuton_u8_t)(NEUTON_NN_MODEL_QLVL + NEUTON_NN_MODEL_KSHIFT - 1)

// ////////////////////// Model configuration resolver end ///////////////////

//////////////////////////////////////////////////////////////////////////////

#if NEUTON_USE_USER_LOG
#define NEUTON_NN_LOG_DEBUG     NEUTON_USER_LOG_DEBUG
#else
#define NEUTON_NN_LOG_DEBUG(...); 
#endif

//////////////////////////////////////////////////////////////////////////////

/**
 * @brief 
 * 
 * @param[in] acoeff           Activation coefficient
 * @param[in] acc              Accumulator 
 * @return neuton_coeff_t      Activated coefficient 
 */
__NEUTON_STATIC_FORCEINLINE 
neuton_coeff_t nn_activation_exp_f32(neuton_coeff_t acoeff, neuton_accum_t acc)
{
    return (neuton_coeff_t)(1.0f / (1.0f + expf((neuton_accum_t) ((neuton_accum_t) -(acoeff)) * acc)));
}

//////////////////////////////////////////////////////////////////////////////

#if (NEUTON_NN_MODEL_QTYPE != NEUTON_NN_MODEL_QTYPE_Q32)

/**
 * @brief 
 * 
 * @param[in] acoeff       Activation coefficient
 * @param[in] acc          Accumulator 
 * @return neuton_coeff_t  Activated coefficient 
 */
__NEUTON_STATIC_FORCEINLINE 
neuton_coeff_t nn_activation_exp_q(neuton_coeff_t acoeff, neuton_accum_t acc)
{
    const neuton_f32_t qs = 
    (neuton_f32_t)((((neuton_accum_t)acoeff) * acc) >> NEUTON_NN_QEXP_SHIFT) / (neuton_f32_t)((neuton_u32_t)1 << NEUTON_NN_MODEL_QLVL);

    const neuton_f32_t res = 1.0f / (1.0f + expf(-qs));

    return (neuton_coeff_t)((res > NEUTON_MAX_INPUT_F32 ? NEUTON_MAX_INPUT_F32 : res) * ((neuton_u32_t)1 << NEUTON_NN_MODEL_QLVL));
}

#endif // (NEUTON_NN_MODEL_QTYPE != NEUTON_NN_MODEL_QTYPE_Q32)

#endif /* _NEUTON_NN_USER_CONFIG_RESOLVER_H_ */