#include "../../../../../neuton/include/neuton/dsp/transform/neuton_dsp_melspectr.h"
#include "../../../../../neuton/include/neuton/neuton_platform.h"
#include <math.h>
#include <string.h>

// ///////////////////////////////////////////////////////////////////////////

__NEUTON_STATIC_FORCEINLINE neuton_f32_t mel_frequency_(neuton_f32_t freq)
{
    return 2595 * log10f(1 + freq / 700);
}

// ///////////////////////////////////////////////////////////////////////////

static void mel_scale_(const neuton_f32_t* p_spectrum, neuton_u16_t spectrum_cnt, 
                        neuton_u16_t sample_rate, neuton_f32_t* p_mels, neuton_u16_t n_mels)
{
    neuton_f32_t mel_freq_halfband = mel_frequency_(sample_rate / 2) / (n_mels + 1);

    for (neuton_u16_t i = 0; i < n_mels; ++i)
        p_mels[i] = 0;

    for (neuton_u16_t i = 0; i < spectrum_cnt / 2; ++i)
    {
        neuton_f32_t mel_freq = mel_frequency_(i * sample_rate / spectrum_cnt);

        int band_index = (int)(mel_freq / mel_freq_halfband);
        neuton_f32_t mel_band_start_freq = band_index * mel_freq_halfband;

        neuton_f32_t filter_r = (mel_freq - mel_band_start_freq) / mel_freq_halfband;
        neuton_f32_t filter_l = 1 - filter_r;

        if (band_index > 0)
            p_mels[band_index - 1] += p_spectrum[i] * filter_l;
        if (band_index < n_mels)
            p_mels[band_index] += p_spectrum[i] * filter_r;
    }
}

// ///////////////////////////////////////////////////////////////////////////

neuton_i8_t neuton_dsp_melspectr_make_f32(neuton_dsp_melspectr_ctx_f32_t* p_ctx, 
                                        neuton_f32_t* p_audio_input)
{
    if (p_ctx->current_fill >= p_ctx->time_bands)
        return 0;

    p_ctx->fht.p_window = p_audio_input;
    neuton_dsp_rfht_f32(&p_ctx->fht);

    neuton_f32_t* p_melspectrum = &p_ctx->p_melspectrum[p_ctx->current_fill * p_ctx->freq_bands];

    mel_scale_(p_ctx->fht.p_window, p_ctx->fht.window_size, 
                p_ctx->sample_rate, p_melspectrum, p_ctx->freq_bands);

    for (neuton_u16_t i = 0; i < p_ctx->freq_bands; ++i)
        p_melspectrum[i] = log10f((p_melspectrum[i] == 0.0f) ? NEUTON_F32_NP_MIN : p_melspectrum[i]);

    return (++p_ctx->current_fill < p_ctx->time_bands);
}

// ///////////////////////////////////////////////////////////////////////////

void neuton_dsp_melspectr_shift_f32(neuton_dsp_melspectr_ctx_f32_t* p_ctx, 
                                    neuton_u16_t shift)
{
    if ((shift >= p_ctx->time_bands) || (shift == 0))
    {
        p_ctx->current_fill = 0;
        return;
    }

    neuton_f32_t* offset = &p_ctx->p_melspectrum[shift * p_ctx->freq_bands];
    neuton_u32_t shift_bytes = (p_ctx->time_bands - shift) * p_ctx->freq_bands * sizeof(p_ctx->p_melspectrum[0]);

    memmove(p_ctx->p_melspectrum, offset, shift_bytes);

    p_ctx->current_fill = p_ctx->time_bands - shift;
}