#include "../../../../../neuton/include/neuton/dsp/neuton_dsp_statistic.h"
#include "../../../../../neuton/include/neuton/dsp/neuton_dsp_fast_math.h"
#include "../../../../../neuton/include/neuton/private/common/neuton_mem.h"

// ///////////////////////////////////////////////////////////////////////////

#ifndef EXCESS_KURTOSIS_F32
#define EXCESS_KURTOSIS_F32(kur)     ((kur) - 3.0f)
#endif

// ///////////////////////////////////////////////////////////////////////////

static void var_skew_kur_f32_(const neuton_f32_t* p_input, neuton_u16_t num,
                        neuton_dsp_stat_ctx_f32_t* p_ctx, neuton_f32_t mean,
                        neuton_dsp_moments_f32_t* p_m)
{
    neuton_u16_t loop_cnt;
    neuton_f32_t diff;
    neuton_f32_t xdiff;
    neuton_f32_t m2 = 0;
    neuton_f32_t m3 = 0;
    neuton_f32_t m4 = 0;

    loop_cnt = num;

    while (loop_cnt > 0U)
    {
        diff = *p_input++ - mean;

        xdiff = diff * diff;
        m2 += xdiff;

        xdiff = xdiff * diff;
        m3 += xdiff;

        xdiff = xdiff * diff;
        m4 += xdiff;

        loop_cnt--;
    }

    m2 = m2 / num;
    m3 = m3 / num;
    m4 = m4 / num;

    NEUTON_DSP_RETURN_IF(m2 == 0, NEUTON_VOID_VALUE);

    p_m->moment.var  = m2;
    p_m->moment.skew = m3 / neuton_dsp_sqrt_f32(m2 * m2 * m2);
    p_m->moment.kur  = EXCESS_KURTOSIS_F32(m4 / (m2 * m2));

    if (p_ctx)
    {
        p_ctx->flags.is.var = true;
        p_ctx->value.var = m2;
    }
}

// ///////////////////////////////////////////////////////////////////////////

static void var_skew_kur_f32_s_(const neuton_f32_t* p_input, neuton_u16_t num, size_t stride,
                        neuton_dsp_stat_ctx_f32_t* p_ctx, neuton_f32_t mean,
                        neuton_dsp_moments_f32_t* p_m)
{
    neuton_f32_t diff;
    neuton_f32_t xdiff;
    neuton_f32_t m2 = 0;
    neuton_f32_t m3 = 0;
    neuton_f32_t m4 = 0;

    for (neuton_u16_t i = 0; i < num; i++)
    {
        diff = p_input[i * stride] - mean;

        xdiff = diff * diff;
        m2 += xdiff;

        xdiff = xdiff * diff;
        m3 += xdiff;

        xdiff = xdiff * diff;
        m4 += xdiff;
    }

    m2 = m2 / num;
    m3 = m3 / num;
    m4 = m4 / num;

    NEUTON_DSP_RETURN_IF(m2 == 0, NEUTON_VOID_VALUE);

    p_m->moment.var  = m2;
    p_m->moment.skew = m3 / neuton_dsp_sqrt_f32(m2 * m2 * m2);
    p_m->moment.kur  = EXCESS_KURTOSIS_F32(m4 / (m2 * m2));

    if (p_ctx)
    {
        p_ctx->flags.is.var = true;
        p_ctx->value.var = m2;
    }
}

// ///////////////////////////////////////////////////////////////////////////

static void skew_kur_f32_(const neuton_f32_t* p_input, neuton_u16_t num,
                        neuton_f32_t mean, neuton_f32_t var,
                        neuton_dsp_moments_f32_t* p_m)
{
    NEUTON_DSP_RETURN_IF(var == 0, NEUTON_VOID_VALUE);

    neuton_u16_t loop_cnt;
    neuton_f32_t diff;
    neuton_f32_t xdiff;
    neuton_f32_t m3 = 0;
    neuton_f32_t m4 = 0;

    loop_cnt = num;

    while (loop_cnt > 0U)
    {
        diff = *p_input++ - mean;

        xdiff = diff * diff * diff;
        m3 += xdiff;

        xdiff = xdiff * diff;
        m4 += xdiff;

        loop_cnt--;
    }

    m3 = m3 / num;
    m4 = m4 / num;

    p_m->moment.var = var;
    p_m->moment.skew = m3 / neuton_dsp_sqrt_f32(var * var * var);
    p_m->moment.kur  = EXCESS_KURTOSIS_F32(m4 / (var * var));
}

// ///////////////////////////////////////////////////////////////////////////

static void skew_kur_f32_s_(const neuton_f32_t* p_input, neuton_u16_t num, size_t stride,
                        neuton_f32_t mean, neuton_f32_t var,
                        neuton_dsp_moments_f32_t* p_m)
{
    NEUTON_DSP_RETURN_IF(var == 0, NEUTON_VOID_VALUE);

    neuton_f32_t diff;
    neuton_f32_t xdiff;
    neuton_f32_t m3 = 0;
    neuton_f32_t m4 = 0;

    for (neuton_u16_t i = 0; i < num; i++)
    {
        diff = p_input[i * stride] - mean;

        xdiff = diff * diff * diff;
        m3 += xdiff;

        xdiff = xdiff * diff;
        m4 += xdiff;
    }

    m3 = m3 / num;
    m4 = m4 / num;

    p_m->moment.var = var;
    p_m->moment.skew = m3 / neuton_dsp_sqrt_f32(var * var * var);
    p_m->moment.kur  = EXCESS_KURTOSIS_F32(m4 / (var * var));
}

// ///////////////////////////////////////////////////////////////////////////

void neuton_dsp_moments_f32(const neuton_f32_t* p_input, neuton_u16_t num,
                            neuton_dsp_stat_ctx_f32_t* p_ctx, neuton_dsp_moments_f32_t* p_m)
{
    if (p_m == NULL)
        return;

    neuton_f32_t mean;
    neuton_u8_t f;

    f = (p_ctx == NULL) ? NEUTON_DSP_STAT_CTX_EMPTY : (p_ctx->flags.all & NEUTON_DSP_STAT_CTX_SUM_VAR_FLAGS);

    switch (f)
    {
    case NEUTON_DSP_STAT_CTX_EMPTY:
        mean = neuton_dsp_sum_f32(p_input, num, p_ctx) / num;
        var_skew_kur_f32_(p_input, num, p_ctx, mean, p_m);
        break;
    case NEUTON_DSP_STAT_CTX_SUM_VAR_FLAGS:
        mean = p_ctx->value.sum / num;
        skew_kur_f32_(p_input, num, mean, p_ctx->value.var, p_m);
        break;
    case NEUTON_DSP_STAT_CTX_SUM_FLAG:
        mean = p_ctx->value.sum / num;
        var_skew_kur_f32_(p_input, num, p_ctx, mean, p_m);
        break;
    case NEUTON_DSP_STAT_CTX_VAR_FLAG:
        mean = neuton_dsp_sum_f32(p_input, num, p_ctx) / num;
        skew_kur_f32_(p_input, num, mean, p_ctx->value.var, p_m);
        break;
    default:
        break;
    }  
}

// ///////////////////////////////////////////////////////////////////////////

void neuton_dsp_moments_f32_s(const neuton_f32_t* p_input, neuton_u16_t num, size_t stride,
                            neuton_dsp_stat_ctx_f32_t* p_ctx, neuton_dsp_moments_f32_t* p_m)
{
    if (p_m == NULL)
        return;

    neuton_f32_t mean;
    neuton_u8_t f;

    f = (p_ctx == NULL) ? NEUTON_DSP_STAT_CTX_EMPTY : (p_ctx->flags.all & NEUTON_DSP_STAT_CTX_SUM_VAR_FLAGS);

    switch (f)
    {
    case NEUTON_DSP_STAT_CTX_EMPTY:
        mean = neuton_dsp_sum_f32_s(p_input, num, stride, p_ctx) / num;
        var_skew_kur_f32_s_(p_input, num, stride, p_ctx, mean, p_m);
        break;
    case NEUTON_DSP_STAT_CTX_SUM_VAR_FLAGS:
        mean = p_ctx->value.sum / num;
        skew_kur_f32_s_(p_input, num, stride, mean, p_ctx->value.var, p_m);
        break;
    case NEUTON_DSP_STAT_CTX_SUM_FLAG:
        mean = p_ctx->value.sum / num;
        var_skew_kur_f32_s_(p_input, num, stride, p_ctx, mean, p_m);
        break;
    case NEUTON_DSP_STAT_CTX_VAR_FLAG:
        mean = neuton_dsp_sum_f32_s(p_input, num, stride, p_ctx) / num;
        skew_kur_f32_s_(p_input, num, stride, mean, p_ctx->value.var, p_m);
        break;
    default:
        break;
    }   
}