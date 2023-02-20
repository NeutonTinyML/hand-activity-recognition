#include "../../../../../neuton/include/neuton/dsp/pipeline/neuton_dsp_pipeline_spectr.h"
#include "../../../../../neuton/include/neuton/dsp/pipeline/config/neuton_dsp_pipeline_config_f32.h"
#include "../../../../../neuton/include/neuton/dsp/pipeline/config/neuton_dsp_pipeline_config_resolver.h"
#include "../../../../../neuton/include/neuton/dsp/neuton_dsp_spectral.h"
#include "../../../../../neuton/include/neuton/dsp/neuton_dsp_transform.h"
#include "../../../../../neuton/include/neuton/neuton_platform.h"
#include <string.h>

// ///////////////////////////////////////////////////////////////////////////

#define FEATURES_USED_PEAKS(mask)       (mask.is.peaks_freq || mask.is.peaks_ampl)
#define IS_PEAK_USED(usage_mask, pos)   ((1U << pos) & usage_mask)

// ///////////////////////////////////////////////////////////////////////////

neuton_u16_t neuton_dsp_pipeline_spectr_compute_f32(const neuton_f32_t* p_input, neuton_u16_t num,
                                                const neuton_dsp_spectr_features_mask_t feature_mask,
                                                neuton_dsp_get_feature_arg_cb_t get_argument,
                                                neuton_f32_t* p_features)
{
    neuton_f32_t* p_features_begin   = p_features;

    neuton_dsp_rfht_instance_t rfht;
    get_argument(NEUTON_DSP_PIPELINE_SPECTRAL, NEUTON_DSP_SPECTR_FID_SPECTRUM, 1, &rfht);

    /** Check for input buffer underflow */
    if (rfht.window_size > num)
        return 0;

    /** Null window is treated as in-place spectrum calculation */
    if (rfht.p_window == NULL)
        rfht.p_window = (void*)p_input;
    else
        memcpy(rfht.p_window, p_input, rfht.window_size * sizeof(p_input[0]));

    /** Compute frequency domain of signal */
    neuton_dsp_rfht_f32(&rfht);  
    
// ///////////////////////////////////////////////////////////////////////////
#if (NEUTON_DSP_PIPELINE_COMPUTE_SPECTR_PEAKS)

    if (FEATURES_USED_PEAKS(feature_mask))
    {
        neuton_u16_t peaks_index[NEUTON_FIND_PEAKS_MAX_NUM] = {0U};
        neuton_dsp_findpeaks_f32((neuton_f32_t*)rfht.p_window, rfht.window_size / 2, 
                                peaks_index, NULL);

#if (NEUTON_DSP_PIPELINE_COMPUTE_SPECTR_PEAKS_FREQ)
        if (feature_mask.is.peaks_freq)
        {
            neuton_f32_t usage_mask;
            get_argument(NEUTON_DSP_PIPELINE_SPECTRAL, NEUTON_DSP_SPECTR_FID_PEAKS_FREQ, 1, &usage_mask);

            for (size_t i = 0; i < NEUTON_FIND_PEAKS_MAX_NUM; i++)
            {
                if (IS_PEAK_USED((neuton_u32_t)usage_mask, i))
                    *p_features++ = peaks_index[i];
            }
        }
#endif

#if (NEUTON_DSP_PIPELINE_COMPUTE_SPECTR_PEAKS_AMPL)
        if (feature_mask.is.peaks_ampl)
        {
            neuton_f32_t usage_mask;
            const neuton_f32_t* p_spectrum = (const neuton_f32_t*)rfht.p_window;
            get_argument(NEUTON_DSP_PIPELINE_SPECTRAL, NEUTON_DSP_SPECTR_FID_PEAKS_AMPL, 1, &usage_mask);

            for (size_t i = 0; i < NEUTON_FIND_PEAKS_MAX_NUM; i++)
            {
                if (IS_PEAK_USED((neuton_u32_t)usage_mask, i))
                    *p_features++ = p_spectrum[peaks_index[i]];
            }
        }
#endif
    }
#endif // NEUTON_DSP_PIPELINE_COMPUTE_SPECTR_PEAKS
// ///////////////////////////////////////////////////////////////////////////

    /** Prevent compilation warnings */
    NEUTON_UNUSED(feature_mask);
    NEUTON_UNUSED(get_argument);

    return (neuton_u16_t)(p_features - p_features_begin);
}