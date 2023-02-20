#include "../../../../../neuton/include/neuton/dsp/neuton_dsp_statistic.h"
#include "../../../../../neuton/include/neuton/private/common/neuton_mem.h"

// ///////////////////////////////////////////////////////////////////////////

static neuton_i16_t var_by_sum_n_tss_i8_(neuton_i32_t sum,
                                        neuton_u32_t sum_of_squares,
                                        neuton_u16_t num)
{
    /* Compute Mean of squares */
    neuton_i32_t mean_of_squares = (neuton_i32_t)(sum_of_squares / (num - 1U));

    /* Compute Square of mean */
    neuton_i32_t square_of_mean = (neuton_i32_t)((sum * sum) / (neuton_i32_t)(num * (num - 1U)));

    return (neuton_i16_t)(mean_of_squares - square_of_mean);
}

// ///////////////////////////////////////////////////////////////////////////

static neuton_i16_t var_by_mean_i8_(const neuton_i8_t* p_input,
                                    neuton_u16_t num, 
                                    const neuton_i8_t mean)
{
    neuton_u16_t loop_cnt;
    neuton_i16_t diff;
    neuton_i32_t sum  = 0;

#if (NEUTON_USE_LOOPUNROLL == 1)
    neuton_i32_t* p_input_i32 = (neuton_i32_t*)p_input;
    neuton_i32_t i8x4;
    /* Loop unrolling: Compute 4 outputs at a time */
    loop_cnt = num >> 2U;

    while (loop_cnt > 0U)
    {
        i8x4 = *p_input_i32++;

        diff = ((i8x4 << 24U) >> 24U) - mean;
        sum += diff * diff;

        diff = ((i8x4 << 16U) >> 24U) - mean;
        sum += diff * diff;

        diff = ((i8x4 <<  8U) >> 24U) - mean;
        sum += diff * diff;

        diff = (i8x4 >> 24U) - mean;
        sum += diff * diff;

        loop_cnt--;
    }

    /* Loop unrolling: Compute remaining outputs */
    loop_cnt = num % 0x4U;
    p_input  = (neuton_i8_t*)p_input_i32;

#else

    loop_cnt = num;

#endif /* #if (NEUTON_USE_LOOPUNROLL == 1) */

    while (loop_cnt > 0U)
    {
        diff = *p_input++ - mean;
        sum += diff * diff;

        loop_cnt--;
    }

    return (sum / (num - 1));
}

// ///////////////////////////////////////////////////////////////////////////

static neuton_i16_t var_by_mean_i8_s_(const neuton_i8_t* p_input,
                                    neuton_u16_t num, size_t stride,
                                    const neuton_i8_t mean)
{
    neuton_u16_t loop_cnt;
    neuton_u16_t i = 0;
    neuton_i16_t diff;
    neuton_i32_t sum  = 0;

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

    return (sum / (num - 1));
}

// ///////////////////////////////////////////////////////////////////////////

neuton_i16_t neuton_dsp_var_i8(const neuton_i8_t* p_input, neuton_u16_t num,
                                neuton_dsp_stat_ctx_i8_t* p_ctx)
{
    neuton_i16_t var;

    if (p_ctx)
    {
        // Clear other irrelevant flags
        uint8_t flags = p_ctx->flags.all & NEUTON_DSP_STAT_CTX_SUM_TSS_FLAGS;

        switch (flags)
        {
        case NEUTON_DSP_STAT_CTX_SUM_TSS_FLAGS:
            var = var_by_sum_n_tss_i8_(p_ctx->value.sum, p_ctx->value.tss, num);
            break;
        case NEUTON_DSP_STAT_CTX_TSS_FLAG:
            var = var_by_sum_n_tss_i8_(neuton_dsp_sum_i8(p_input, num, p_ctx), p_ctx->value.tss, num);
            break;
        case NEUTON_DSP_STAT_CTX_SUM_FLAG:
            var = var_by_mean_i8_(p_input, num, p_ctx->value.sum / num);
            break;
        default:
            neuton_dsp_tss_sum_i8(p_input, num, p_ctx);
            var = var_by_sum_n_tss_i8_(p_ctx->value.sum, p_ctx->value.tss, num);
            break;
        }

        p_ctx->flags.is.var = true;
        p_ctx->value.var    = var;
    }
    else
    {
        neuton_dsp_stat_ctx_i8_t ctx;
        NEUTON_DSP_STAT_CTX_RESET(ctx);

        neuton_dsp_tss_sum_i8(p_input, num, &ctx);
        var = var_by_sum_n_tss_i8_(ctx.value.sum, ctx.value.tss, num);
    }

    return var;
}

// ///////////////////////////////////////////////////////////////////////////

neuton_i16_t neuton_dsp_var_i8_s(const neuton_i8_t* p_input, neuton_u16_t num,
                                size_t stride, neuton_dsp_stat_ctx_i8_t* p_ctx)
{
    neuton_i16_t var;

    if (p_ctx)
    {
        // Clear other irrelevant flags
        uint8_t flags = p_ctx->flags.all & NEUTON_DSP_STAT_CTX_SUM_TSS_FLAGS;

        switch (flags)
        {
        case NEUTON_DSP_STAT_CTX_SUM_TSS_FLAGS:
            var = var_by_sum_n_tss_i8_(p_ctx->value.sum, p_ctx->value.tss, num);
            break;
        case NEUTON_DSP_STAT_CTX_TSS_FLAG:
            var = var_by_sum_n_tss_i8_(neuton_dsp_sum_i8_s(p_input, num, stride, p_ctx), p_ctx->value.tss, num);
            break;
        case NEUTON_DSP_STAT_CTX_SUM_FLAG:
            var = var_by_mean_i8_s_(p_input, num, stride, p_ctx->value.sum / num);
            break;
        default:
            neuton_dsp_tss_sum_i8_s(p_input, num, stride, p_ctx);
            var = var_by_sum_n_tss_i8_(p_ctx->value.sum, p_ctx->value.tss, num);
            break;
        }

        p_ctx->flags.is.var = true;
        p_ctx->value.var    = var;
    }
    else
    {
        neuton_dsp_stat_ctx_i8_t ctx;
        NEUTON_DSP_STAT_CTX_RESET(ctx);

        neuton_dsp_tss_sum_i8_s(p_input, num, stride, &ctx);
        var = var_by_sum_n_tss_i8_(ctx.value.sum, ctx.value.tss, num);
    }

    return var;
}