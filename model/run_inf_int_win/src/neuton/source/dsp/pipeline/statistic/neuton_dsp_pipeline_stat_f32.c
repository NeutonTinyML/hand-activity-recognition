#include "../../../../../neuton/include/neuton/dsp/pipeline/neuton_dsp_pipeline_stat.h"
#include "../../../../../neuton/include/neuton/dsp/pipeline/config/neuton_dsp_pipeline_config_f32.h"
#include "../../../../../neuton/include/neuton/dsp/pipeline/config/neuton_dsp_pipeline_config_resolver.h"
#include "../../../../../neuton/include/neuton/dsp/neuton_dsp_statistic.h"
#include "../../../../../neuton/include/neuton/neuton_platform.h"

#include <string.h>
// ///////////////////////////////////////////////////////////////////////////

#define FEATURES_USED_TSS_SUM(mask)    ( mask.is.rms && (mask.is.mean || mask.is.std) )

// ///////////////////////////////////////////////////////////////////////////

neuton_u8_t neuton_dsp_pipeline_stat_compute_f32(const neuton_f32_t* p_input, neuton_u16_t num,
                                                const neuton_dsp_stat_features_mask_t feature_mask,
                                                neuton_dsp_get_feature_arg_cb_t get_argument,
                                                neuton_f32_t* p_features)
{
    neuton_dsp_stat_ctx_f32_t* p_ctx = NULL;
    neuton_f32_t* p_features_begin   = p_features;

// ///////////////////////////////////////////////////////////////////////////
#if (NEUTON_DSP_PIPELINE_STAT_USED_CTX)

    /** We do not check the feature_mask to allocate the ctx, since the cost of checking
     *  is greater than the cost of allocating neuton_dsp_stat_ctx_f32_t */
    neuton_dsp_stat_ctx_f32_t ctx;
    NEUTON_DSP_STAT_CTX_RESET(ctx);
    p_ctx = &ctx;
#endif
// ///////////////////////////////////////////////////////////////////////////

#if (NEUTON_DSP_PIPELINE_COMPUTE_MIN_MAX)

    neuton_f32_t min, max;
    if (feature_mask.is.min || feature_mask.is.max)
    {
        neuton_dsp_min_max_f32(p_input, num, &min, &max);

        if (feature_mask.is.min)
            { *p_features = min; p_features++; }
        if (feature_mask.is.max)
            { *p_features = max; p_features++; }
    }
#else
#if (NEUTON_DSP_PIPELINE_COMPUTE_MIN)

    if (feature_mask.is.min)
    {
        *p_features = neuton_dsp_min_f32(p_input, num);
        p_features++;
    }
#endif

#if (NEUTON_DSP_PIPELINE_COMPUTE_MAX)

    if (feature_mask.is.max)
    {
        *p_features = neuton_dsp_max_f32(p_input, num);
        p_features++;
    }
#endif

#endif // #if (NEUTON_DSP_PIPELINE_COMPUTE_MIN_MAX)
// ///////////////////////////////////////////////////////////////////////////

// ///////////////////////////////////////////////////////////////////////////
#if (NEUTON_DSP_PIPELINE_COMPUTE_RANGE && NEUTON_DSP_PIPELINE_COMPUTE_MIN_MAX)

    if (feature_mask.is.range)
    {
        if (feature_mask.is.min || feature_mask.is.max)
            *p_features = max - min;
        else
            *p_features = neuton_dsp_range_f32(p_input, num);

        p_features++;
    }
#elif (NEUTON_DSP_PIPELINE_COMPUTE_RANGE)

    if (feature_mask.is.range)
    {
        *p_features = neuton_dsp_range_f32(p_input, num);
        p_features++;
    }
#endif
// ///////////////////////////////////////////////////////////////////////////

// ///////////////////////////////////////////////////////////////////////////
/** Calculating interim statistical value to speed-up the following calculations */
#if (NEUTON_DSP_PIPELINE_USED_TSS_AND_SUM)

    if (FEATURES_USED_TSS_SUM(feature_mask))
    {
        neuton_dsp_tss_sum_f32(p_input, num, p_ctx);
    }
#endif
// ///////////////////////////////////////////////////////////////////////////

// ///////////////////////////////////////////////////////////////////////////
#if (NEUTON_DSP_PIPELINE_COMPUTE_MEAN)

    if (feature_mask.is.mean)
    {
        *p_features = neuton_dsp_mean_f32(p_input, num, p_ctx);
        p_features++;
    }
#endif
// ///////////////////////////////////////////////////////////////////////////

// ///////////////////////////////////////////////////////////////////////////
#if (NEUTON_DSP_PIPELINE_COMPUTE_MAD)

    if (feature_mask.is.mad)
    {
        *p_features = neuton_dsp_mad_f32(p_input, num, p_ctx);
        p_features++;
    }
#endif
// ///////////////////////////////////////////////////////////////////////////

// ///////////////////////////////////////////////////////////////////////////
#if (NEUTON_DSP_PIPELINE_COMPUTE_MOMENTS)

    if (feature_mask.is.kur || feature_mask.is.skew)
    {
        neuton_dsp_moments_f32_t m;
        memset(&m, 0, sizeof(m));

        neuton_dsp_moments_f32(p_input, num, p_ctx, &m);

        if (feature_mask.is.skew)
            { *p_features = m.moment.skew; p_features++; }
        if (feature_mask.is.kur)
            { *p_features = m.moment.kur; p_features++; }
    }
#else
#if (NEUTON_DSP_PIPELINE_COMPUTE_SKEW)

    if (feature_mask.is.skew)
    {
        *p_features = neuton_dsp_skew_f32(p_input, num, p_ctx);
        p_features++;
    }
#endif

#if (NEUTON_DSP_PIPELINE_COMPUTE_KUR)

    if (feature_mask.is.kur)
    {
        *p_features = neuton_dsp_kur_f32(p_input, num, p_ctx);
        p_features++;
    }
#endif

#endif // #if (NEUTON_DSP_PIPELINE_COMPUTE_MOMENTS)
// ///////////////////////////////////////////////////////////////////////////

// ///////////////////////////////////////////////////////////////////////////
#if (NEUTON_DSP_PIPELINE_COMPUTE_STD)

    if (feature_mask.is.std)
    {
        *p_features = neuton_dsp_stddev_f32(p_input, num, p_ctx);
        p_features++;
    }
#endif
// ///////////////////////////////////////////////////////////////////////////

// ///////////////////////////////////////////////////////////////////////////
#if (NEUTON_DSP_PIPELINE_COMPUTE_RMS)

    if (feature_mask.is.rms)
    {
        *p_features = neuton_dsp_rms_f32(p_input, num, p_ctx);
        p_features++;
    }
#endif
// ///////////////////////////////////////////////////////////////////////////

// ///////////////////////////////////////////////////////////////////////////
#if (NEUTON_DSP_PIPELINE_COMPUTE_MCR)

    if (feature_mask.is.mcr)
    {
        *p_features = neuton_dsp_mcr_f32(p_input, num, p_ctx);
        p_features++;
    }
#endif
// ///////////////////////////////////////////////////////////////////////////

// ///////////////////////////////////////////////////////////////////////////
#if (NEUTON_DSP_PIPELINE_COMPUTE_ZCR)

    if (feature_mask.is.zcr)
    {
        *p_features = neuton_dsp_zcr_f32(p_input, num);
        p_features++;
    }
#endif
// ///////////////////////////////////////////////////////////////////////////

// ///////////////////////////////////////////////////////////////////////////
#if (NEUTON_DSP_PIPELINE_COMPUTE_TCR)

    if (feature_mask.is.tcr)
    {
        neuton_f32_t threshold;
        get_argument(NEUTON_DSP_PIPELINE_STAT, NEUTON_DSP_STAT_FID_TCR, 1, &threshold);

        *p_features = neuton_dsp_tcr_f32(p_input, num, threshold);
        p_features++;
    }
#endif
// ///////////////////////////////////////////////////////////////////////////

// ///////////////////////////////////////////////////////////////////////////
#if (NEUTON_DSP_PIPELINE_COMPUTE_P2P_LF_HF)

    if (feature_mask.is.p2p_lf || feature_mask.is.p2p_hf)
    {
        neuton_f32_t lf, hf;
        neuton_f32_t window;

        if (feature_mask.is.p2p_lf)
            get_argument(NEUTON_DSP_PIPELINE_STAT, NEUTON_DSP_STAT_FID_P2P_LF, 1, &window);
        /** We re-request argument only to support the behavior when we use separated APIs */
        if (feature_mask.is.p2p_hf)
            get_argument(NEUTON_DSP_PIPELINE_STAT, NEUTON_DSP_STAT_FID_P2P_HF, 1, &window);

        neuton_dsp_pk2pk_lf_hf_f32(p_input, num, (size_t)window, &lf, &hf);

        if (feature_mask.is.p2p_lf)
            { *p_features = lf; p_features++; }
        if (feature_mask.is.p2p_hf)
            { *p_features = hf; p_features++; }
    }
#else
#if (NEUTON_DSP_PIPELINE_COMPUTE_P2P_LF)

    if (feature_mask.is.p2p_lf)
    {
        neuton_f32_t window;
        get_argument(NEUTON_DSP_PIPELINE_STAT, NEUTON_DSP_STAT_FID_P2P_LF, 1, &window);

        *p_features = neuton_dsp_pk2pk_lf_f32(p_input, num, (size_t)window);
        p_features++;
    }
#endif

#if (NEUTON_DSP_PIPELINE_COMPUTE_P2P_HF)

    if (feature_mask.is.p2p_hf)
    {
        neuton_f32_t window;
        get_argument(NEUTON_DSP_PIPELINE_STAT, NEUTON_DSP_STAT_FID_P2P_HF, 1, &window);

        *p_features = neuton_dsp_pk2pk_hf_f32(p_input, num, (size_t)window);
        p_features++;
    }
#endif

#endif // #if (NEUTON_DSP_PIPELINE_COMPUTE_P2P_LF_HF)
// ///////////////////////////////////////////////////////////////////////////

    /** Prevent compilation warnings */
    NEUTON_UNUSED(feature_mask);
    NEUTON_UNUSED(get_argument);
    NEUTON_UNUSED(p_ctx);

    return (neuton_u8_t)(p_features - p_features_begin);
}