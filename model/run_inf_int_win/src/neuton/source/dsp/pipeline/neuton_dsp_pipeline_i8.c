#include "../../../../neuton/include/neuton/dsp/neuton_dsp_pipeline.h"
#include "../../../../neuton/include/neuton/dsp/pipeline/neuton_dsp_pipeline_stat.h"
#include "../../../../neuton/include/neuton/dsp/pipeline/neuton_dsp_pipeline_spectr.h"
#include "../../../../neuton/include/neuton/dsp/pipeline/config/neuton_dsp_pipeline_config_i8.h"
#include "../../../../neuton/include/neuton/dsp/pipeline/config/neuton_dsp_pipeline_config_resolver.h"

// ///////////////////////////////////////////////////////////////////////////

neuton_u16_t neuton_dsp_pipeline_compute_i8(const neuton_i8_t* p_input, neuton_u16_t num,
                                            const neuton_dsp_features_mask_t mask,
                                            neuton_dsp_get_feature_arg_cb_t get_argument,
                                            neuton_i16_t* p_features)
{
    neuton_i16_t* p_features_begin = p_features;

#if NEUTON_DSP_USE_STAT_PIPELINE

    if (mask.features.stat.all)
    {
        p_features += neuton_dsp_pipeline_stat_compute_i8(p_input, num, mask.features.stat,
                                                            get_argument, p_features);
    }
#endif

#if NEUTON_DSP_USE_SPECTR_PIPELINE

    if (mask.features.spectr.all)
    {
        p_features += neuton_dsp_pipeline_spectr_compute_i8(p_input, num, mask.features.spectr,
                                                            get_argument, p_features);
    }
#endif

    return (neuton_u16_t)(p_features - p_features_begin);
}