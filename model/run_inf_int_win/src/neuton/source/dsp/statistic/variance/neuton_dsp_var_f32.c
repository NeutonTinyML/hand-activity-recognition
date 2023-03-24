#include "../../../../../neuton/include/neuton/dsp/neuton_dsp_statistic.h"
#include "../../../../../neuton/include/neuton/private/common/neuton_mem.h"

// ///////////////////////////////////////////////////////////////////////////

neuton_f32_t neuton_dsp_var_f32(const neuton_f32_t* p_input, neuton_u16_t num,
                                neuton_dsp_stat_ctx_f32_t* p_ctx)
{
    neuton_u16_t loop_cnt;
    neuton_f32_t diff;
    neuton_f32_t mean;
    neuton_f32_t sum_squared_diffs = 0.0f;

    // Because of Catastrophic cancellation issue, we calculate variance using mean
    // instead of calculating mean of the square minus the square of the mean.
    if (p_ctx && p_ctx->flags.is.sum)
        mean = p_ctx->value.sum / num;
    else
        mean = neuton_dsp_sum_f32(p_input, num, p_ctx) / num;

#if (NEUTON_USE_LOOPUNROLL == 1)

    /* Loop unrolling: Compute 4 outputs at a time */
    loop_cnt = num >> 2U;

    while (loop_cnt > 0U)
    {
        diff = *p_input++ - mean;
        sum_squared_diffs += diff * diff;

        diff = *p_input++ - mean;
        sum_squared_diffs += diff * diff;

        diff = *p_input++ - mean;
        sum_squared_diffs += diff * diff;

        diff = *p_input++ - mean;
        sum_squared_diffs += diff * diff;

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
        sum_squared_diffs += diff * diff;

        loop_cnt--;
    }

    // Use sum_squared_diffs to store the result of the variance calculation
    sum_squared_diffs = sum_squared_diffs / num;

    if (p_ctx)
    {
        p_ctx->flags.is.var = true;
        p_ctx->value.var    = sum_squared_diffs;
    }

    return sum_squared_diffs;
}

// ///////////////////////////////////////////////////////////////////////////

neuton_f32_t neuton_dsp_var_f32_s(const neuton_f32_t* p_input, neuton_u16_t num,
                                size_t stride, neuton_dsp_stat_ctx_f32_t* p_ctx)
{
    neuton_u16_t loop_cnt;
    neuton_f32_t diff;
    neuton_f32_t mean;
    neuton_f32_t sum_squared_diffs = 0.0f;
    neuton_u16_t i = 0U;

    // Because of Catastrophic cancellation issue, we calculate variance using mean
    // instead of calculating mean of the square minus the square of the mean.
    if (p_ctx && p_ctx->flags.is.sum)
        mean = p_ctx->value.sum / num;
    else
        mean = neuton_dsp_sum_f32_s(p_input, num, stride, p_ctx) / num;

#if (NEUTON_USE_LOOPUNROLL == 1)

    /* Loop unrolling: Compute 4 outputs at a time */
    loop_cnt = num >> 2U;

    while (loop_cnt > 0U)
    {
        diff = p_input[i * stride] - mean;
        sum_squared_diffs += diff * diff;
        i++;

        diff = p_input[i * stride] - mean;
        sum_squared_diffs += diff * diff;
        i++;

        diff = p_input[i * stride] - mean;
        sum_squared_diffs += diff * diff;
        i++;

        diff = p_input[i * stride] - mean;
        sum_squared_diffs += diff * diff;
        i++;

        loop_cnt--;
    }

    /* Loop unrolling: Compute remaining outputs */
    loop_cnt = num % 0x4U;

#else

    loop_cnt = num;

#endif /* #if (NEUTON_USE_LOOPUNROLL == 1) */  

    while (loop_cnt > 0)
    {
        diff = p_input[i * stride] - mean;
        sum_squared_diffs += diff * diff;
        i++;

        loop_cnt--;
    }

    // Use sum_squared_diffs to store the result of the variance calculation
    sum_squared_diffs = sum_squared_diffs / num;

    if (p_ctx)
    {
        p_ctx->flags.is.var = true;
        p_ctx->value.var    = sum_squared_diffs;
    }

    return sum_squared_diffs;
}