#include "../../../../../neuton/include/neuton/dsp/neuton_dsp_statistic.h"
#include "../../../../../neuton/include/neuton/private/common/neuton_mem.h"

// ///////////////////////////////////////////////////////////////////////////

#ifndef TSS_AND_SUM_AVALIABLE
#define TSS_AND_SUM_AVALIABLE               (NEUTON_DSP_STAT_CTX_TSS_FLAG | NEUTON_DSP_STAT_CTX_SUM_FLAG)
#endif

#ifndef ONLY_TSS_AVALIABLE
#define ONLY_TSS_AVALIABLE                  NEUTON_DSP_STAT_CTX_TSS_FLAG
#endif

#ifndef ONLY_SUM_AVALIABLE
#define ONLY_SUM_AVALIABLE                  NEUTON_DSP_STAT_CTX_SUM_FLAG
#endif

// ///////////////////////////////////////////////////////////////////////////

static neuton_i32_t var_by_sum_n_tss_i16_(neuton_i32_t sum, neuton_u64_t sum_of_squares,
                                     neuton_u16_t num)
{
    /* Compute Mean of squares */
    neuton_i64_t mean_of_squares = (neuton_i64_t)(sum_of_squares / num);

    /* Compute Square of mean */
    neuton_i64_t square_of_mean = (neuton_i64_t)((sum * sum) / (num * num));

    return (neuton_i32_t)(mean_of_squares - square_of_mean);
}

// ///////////////////////////////////////////////////////////////////////////

static neuton_i32_t var_by_mean_i16_(const neuton_i16_t* p_input, neuton_u16_t num, 
                                const neuton_i16_t mean)
{
    neuton_u16_t loop_cnt;
    neuton_i16_t diff;
    neuton_i64_t sum  = 0;

#if (NEUTON_USE_LOOPUNROLL == 1)
    neuton_i32_t* p_input_i32 = (neuton_i32_t*)p_input;
    neuton_i32_t i16x2;
    /* Loop unrolling: Compute 4 outputs at a time */
    loop_cnt = num >> 2U;

    while (loop_cnt > 0U)
    {
        i16x2 = *p_input_i32++;

        diff = ((i16x2 << 16U) >> 16U) - mean;
        sum += diff * diff;

        diff = (i16x2 >> 16U) - mean;
        sum += diff * diff;

        i16x2 = *p_input_i32++;

        diff = ((i16x2 << 16U) >> 16U) - mean;
        sum += diff * diff;

        diff = (i16x2 >> 16U) - mean;
        sum += diff * diff;

        loop_cnt--;
    }

    /* Loop unrolling: Compute remaining outputs */
    loop_cnt = num % 0x4U;
    p_input  = (neuton_i16_t*)p_input_i32;

#else

    loop_cnt = num;

#endif /* #if (NEUTON_USE_LOOPUNROLL == 1) */

    while (loop_cnt > 0U)
    {
        diff = *p_input++ - mean;
        sum += diff * diff;

        loop_cnt--;
    }

    return (neuton_i32_t)(sum / num);
}

// ///////////////////////////////////////////////////////////////////////////

static neuton_i32_t var_by_mean_i16_s_(const neuton_i16_t* p_input, neuton_u16_t num, 
                                    size_t stride, const neuton_i16_t mean)
{
    neuton_u16_t loop_cnt;
    neuton_u16_t i = 0;
    neuton_i16_t diff;
    neuton_i64_t sum  = 0;

#if (NEUTON_USE_LOOPUNROLL == 1)

    /* Loop unrolling: Compute 4 outputs at a time */
    loop_cnt = num >> 2U;

    while (loop_cnt > 0U)
    {
        diff = p_input[i * stride] - mean;
        sum += diff * diff;
        i++;

        diff = p_input[i * stride] - mean;
        sum += diff * diff;
        i++;

        diff = p_input[i * stride] - mean;
        sum += diff * diff;
        i++;

        diff = p_input[i * stride] - mean;
        sum += diff * diff;
        i++;

        loop_cnt--;
    }

    /* Loop unrolling: Compute remaining outputs */
    loop_cnt = num % 0x4U;

#else

    loop_cnt = num;

#endif /* #if (NEUTON_USE_LOOPUNROLL == 1) */

    while (loop_cnt > 0U)
    {
        diff = p_input[i * stride] - mean;
        sum += diff * diff;
        i++;

        loop_cnt--;
    }

    return (neuton_i32_t)(sum / num);
}

// ///////////////////////////////////////////////////////////////////////////

neuton_i32_t neuton_dsp_var_i16(const neuton_i16_t* p_input, neuton_u16_t num,
                                neuton_dsp_stat_ctx_i16_t* p_ctx)
{
    neuton_i32_t var;

    if (p_ctx)
    {
        // Clear other irrelevant flags
        uint8_t flags = p_ctx->flags.all & TSS_AND_SUM_AVALIABLE;

        switch (flags)
        {
        case TSS_AND_SUM_AVALIABLE:
            var = var_by_sum_n_tss_i16_(p_ctx->value.sum, p_ctx->value.tss, num);
            break;
        case ONLY_TSS_AVALIABLE:
            var = var_by_sum_n_tss_i16_(neuton_dsp_sum_i16(p_input, num, p_ctx), p_ctx->value.tss, num);
            break;
        case ONLY_SUM_AVALIABLE:
            var = var_by_mean_i16_(p_input, num, p_ctx->value.sum / num);
            break;
        default:
            neuton_dsp_tss_sum_i16(p_input, num, p_ctx);
            var = var_by_sum_n_tss_i16_(p_ctx->value.sum, p_ctx->value.tss, num);
            break;
        }

        p_ctx->flags.is.var = true;
        p_ctx->value.var    = var;
    }
    else
    {
        neuton_dsp_stat_ctx_i16_t ctx;

        neuton_dsp_tss_sum_i16(p_input, num, &ctx);
        var = var_by_sum_n_tss_i16_(ctx.value.sum, ctx.value.tss, num);
    }

    return var;
}

// ///////////////////////////////////////////////////////////////////////////

neuton_i32_t neuton_dsp_var_i16_s(const neuton_i16_t* p_input, neuton_u16_t num,
                                size_t stride, neuton_dsp_stat_ctx_i16_t* p_ctx)
{
    neuton_i32_t var;

    if (p_ctx)
    {
        // Clear other irrelevant flags
        uint8_t flags = p_ctx->flags.all & TSS_AND_SUM_AVALIABLE;

        switch (flags)
        {
        case TSS_AND_SUM_AVALIABLE:
            var = var_by_sum_n_tss_i16_(p_ctx->value.sum, p_ctx->value.tss, num);
            break;
        case ONLY_TSS_AVALIABLE:
            var = var_by_sum_n_tss_i16_(neuton_dsp_sum_i16_s(p_input, num, stride, p_ctx), p_ctx->value.tss, num);
            break;
        case ONLY_SUM_AVALIABLE:
            var = var_by_mean_i16_s_(p_input, num, stride, p_ctx->value.sum / num);
            break;
        default:
            neuton_dsp_tss_sum_i16_s(p_input, num, stride, p_ctx);
            var = var_by_sum_n_tss_i16_(p_ctx->value.sum, p_ctx->value.tss, num);
            break;
        }

        p_ctx->flags.is.var = true;
        p_ctx->value.var    = var;
    }
    else
    {
        neuton_dsp_stat_ctx_i16_t ctx;
        NEUTON_DSP_STAT_CTX_RESET(ctx);

        neuton_dsp_tss_sum_i16_s(p_input, num, stride, &ctx);
        var = var_by_sum_n_tss_i16_(ctx.value.sum, ctx.value.tss, num);
    }

    return var;
}