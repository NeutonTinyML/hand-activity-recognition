#include "../../../../../neuton/include/neuton/dsp/neuton_dsp_statistic.h"
#include "../../../../../neuton/include/neuton/private/common/neuton_mem.h"

// ///////////////////////////////////////////////////////////////////////////

#ifndef EXCESS_KURTOSIS_F32
#define EXCESS_KURTOSIS_F32(kur)     ((kur) - 3.0f)
#endif     

// ///////////////////////////////////////////////////////////////////////////

static neuton_f32_t kurtosis_variance_f32_(const neuton_f32_t* p_input, neuton_u16_t num,
                                neuton_dsp_stat_ctx_f32_t* p_ctx, const neuton_f32_t mean)
{
    neuton_u16_t loop_cnt;
    neuton_f32_t diff;
    neuton_f32_t xdiff;
    neuton_f32_t m2 = 0;
    neuton_f32_t m4 = 0;

    loop_cnt = num;

    while (loop_cnt > 0U)
    {
        diff = *p_input++ - mean;

        xdiff = diff * diff;
        m2 += xdiff;

        m4 += xdiff * xdiff;

        loop_cnt--;
    }

    m2 = m2 / num;
    m4 = m4 / num;

    NEUTON_DSP_RETURN_IF(m2 == 0, NEUTON_DSP_ZERO_DIV_FLAG);

    if (p_ctx)
    {
        p_ctx->flags.is.var = true;
        p_ctx->value.var = m2;
    }

    return (m4 / (m2 * m2));
}

// ///////////////////////////////////////////////////////////////////////////

static neuton_f32_t kurtosis_variance_f32_s_(const neuton_f32_t* p_input, neuton_u16_t num,
                                    size_t stride, neuton_dsp_stat_ctx_f32_t* p_ctx,
                                     const neuton_f32_t mean)
{
    neuton_f32_t diff;
    neuton_f32_t xdiff;
    neuton_f32_t m2 = 0;
    neuton_f32_t m4 = 0;

    for (neuton_u16_t i = 0; i < num; i++)
    {
        diff = p_input[i * stride] - mean;

        xdiff = diff * diff;
        m2 += xdiff;

        m4 += xdiff * xdiff;
    }

    m2 = m2 / num;
    m4 = m4 / num;

    NEUTON_DSP_RETURN_IF(m2 == 0, NEUTON_DSP_ZERO_DIV_FLAG);

    if (p_ctx)
    {
        p_ctx->flags.is.var = true;
        p_ctx->value.var = m2;
    }

    return (m4 / (m2 * m2));
}

// ///////////////////////////////////////////////////////////////////////////

static neuton_f32_t kurtosis_f32_(const neuton_f32_t* p_input, neuton_u16_t num,
                        const neuton_f32_t mean, const neuton_f32_t var)
{
    NEUTON_DSP_RETURN_IF(var == 0, NEUTON_DSP_ZERO_DIV_FLAG);

    neuton_u16_t loop_cnt;
    neuton_f32_t diff;
    neuton_f32_t m4 = 0;

#if (NEUTON_USE_LOOPUNROLL == 1)

    /* Loop unrolling: Compute 4 outputs at a time */
    loop_cnt = num >> 2U;

    while (loop_cnt > 0U)
    {
        diff = *p_input++ - mean;
        m4 += (diff * diff * diff * diff);

        diff = *p_input++ - mean;
        m4 += (diff * diff * diff * diff);

        diff = *p_input++ - mean;
        m4 += (diff * diff * diff * diff);

        diff = *p_input++ - mean;
        m4 += (diff * diff * diff * diff);

        loop_cnt--;
    }
    /* Loop unrolling: Compute remaining outputs */
    loop_cnt = num % 0x4U;

#else

    loop_cnt = num;

#endif /* #if (NEUTON_USE_LOOPUNROLL == 1) */

    while (loop_cnt > 0U)
    {
        diff = *p_input++ - mean;
        m4 += (diff * diff * diff * diff);

        loop_cnt--;
    }

    m4 = m4 / num;

    return (m4 / (var * var));
}

// ///////////////////////////////////////////////////////////////////////////

static neuton_f32_t kurtosis_f32_s_(const neuton_f32_t* p_input, neuton_u16_t num,
                            size_t stride, const neuton_f32_t mean, 
                            const neuton_f32_t var)
{
    NEUTON_DSP_RETURN_IF(var == 0, NEUTON_DSP_ZERO_DIV_FLAG);

    neuton_f32_t diff;
    neuton_f32_t m4 = 0;

    for (neuton_u16_t i = 0; i < num; i++)
    {
        diff = p_input[i * stride] - mean;
        m4 += (diff * diff * diff * diff);
    }

    m4 = m4 / num;

    return (m4 / (var * var));
}

// ///////////////////////////////////////////////////////////////////////////

neuton_f32_t neuton_dsp_kur_f32(const neuton_f32_t* p_input, neuton_u16_t num,
                                neuton_dsp_stat_ctx_f32_t* p_ctx)
{
    neuton_f32_t mean;
    neuton_f32_t kur;
    neuton_u8_t f;

    f = (p_ctx == NULL) ? NEUTON_DSP_STAT_CTX_EMPTY : (p_ctx->flags.all & NEUTON_DSP_STAT_CTX_SUM_VAR_FLAGS);

    switch (f)
    {
    case NEUTON_DSP_STAT_CTX_EMPTY:
        mean = neuton_dsp_sum_f32(p_input, num, p_ctx) / num;
        kur = kurtosis_variance_f32_(p_input, num, p_ctx, mean);
        break;
    case NEUTON_DSP_STAT_CTX_SUM_VAR_FLAGS:
        mean = p_ctx->value.sum / num;
        kur = kurtosis_f32_(p_input, num, mean, p_ctx->value.var);
        break;
    case NEUTON_DSP_STAT_CTX_SUM_FLAG:
        mean = p_ctx->value.sum / num;
        kur = kurtosis_variance_f32_(p_input, num, p_ctx, mean);
        break;
    case NEUTON_DSP_STAT_CTX_VAR_FLAG:
        mean = neuton_dsp_sum_f32(p_input, num, p_ctx) / num;
        kur = kurtosis_f32_(p_input, num, mean, p_ctx->value.var);
        break;
    default:
        kur = NEUTON_F32_MIN; // should never get here
        break;
    }

    return EXCESS_KURTOSIS_F32(kur);   
}

// ///////////////////////////////////////////////////////////////////////////

neuton_f32_t neuton_dsp_kur_f32_s(const neuton_f32_t* p_input, neuton_u16_t num, 
                                    size_t stride, neuton_dsp_stat_ctx_f32_t* p_ctx)
{
    neuton_f32_t mean;
    neuton_f32_t kur;
    neuton_u8_t f;

    f = (p_ctx == NULL) ? NEUTON_DSP_STAT_CTX_EMPTY : (p_ctx->flags.all & NEUTON_DSP_STAT_CTX_SUM_VAR_FLAGS);

    switch (f)
    {
    case NEUTON_DSP_STAT_CTX_EMPTY:
        mean = neuton_dsp_sum_f32_s(p_input, num, stride, p_ctx) / num;
        kur = kurtosis_variance_f32_s_(p_input, num, stride, p_ctx, mean);
        break;
    case NEUTON_DSP_STAT_CTX_SUM_VAR_FLAGS:
        mean = p_ctx->value.sum / num;
        kur = kurtosis_f32_s_(p_input, num, stride, mean, p_ctx->value.var);
        break;
    case NEUTON_DSP_STAT_CTX_SUM_FLAG:
        mean = p_ctx->value.sum / num;
        kur = kurtosis_variance_f32_s_(p_input, num, stride, p_ctx, mean);
        break;
    case NEUTON_DSP_STAT_CTX_VAR_FLAG:
        mean = neuton_dsp_sum_f32_s(p_input, num, stride, p_ctx) / num;
        kur = kurtosis_f32_s_(p_input, num, stride, mean, p_ctx->value.var);
        break;
    default:
        kur = NEUTON_F32_MIN; // should never get here
        break;
    }

    return EXCESS_KURTOSIS_F32(kur);
}