#include "../../../../../neuton/include/neuton/dsp/neuton_dsp_statistic.h"
#include "../../../../../neuton/include/neuton/private/common/neuton_mem.h"

#include <math.h>

// ///////////////////////////////////////////////////////////////////////////

neuton_i32_t neuton_dsp_mad_i16(const neuton_i16_t* p_input, neuton_u16_t num,
                                neuton_dsp_stat_ctx_i16_t* p_ctx)
{
    neuton_u16_t loop_cnt;
    neuton_i16_t mean;
    neuton_u32_t sum = 0;

    if (p_ctx && p_ctx->flags.is.sum)
        mean = p_ctx->value.sum / num;
    else
        mean = neuton_dsp_sum_i16(p_input, num, p_ctx) / num;

#if (NEUTON_USE_LOOPUNROLL == 1)
    neuton_i32_t* p_input_i32 = (neuton_i32_t*)p_input;
    neuton_i32_t i16x2;

    /* Loop unrolling: Compute 4 outputs at a time */
    loop_cnt = num >> 2U;

    while (loop_cnt > 0U)
    {
        i16x2 = *p_input_i32++;

        sum += abs(((i16x2 << 16U) >> 16U) - mean);

        sum += abs((i16x2 >> 16U) - mean);

        i16x2 = *p_input_i32++;

        sum += abs(((i16x2 << 16U) >> 16U) - mean);

        sum += abs((i16x2 >> 16U) - mean);

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
        sum += abs(*p_input++ - mean);

        loop_cnt--;
    }

    return (neuton_i32_t)(sum / num);    
}

// ///////////////////////////////////////////////////////////////////////////

neuton_i32_t neuton_dsp_mad_i16_s(const neuton_i16_t* p_input, neuton_u16_t num, 
                                    size_t stride, neuton_dsp_stat_ctx_i16_t* p_ctx)
{
    neuton_u16_t loop_cnt;
    neuton_i16_t mean;
    neuton_u32_t sum = 0;
    neuton_u16_t i = 0;

    if (p_ctx && p_ctx->flags.is.sum)
        mean = p_ctx->value.sum / num;
    else
        mean = neuton_dsp_sum_i16_s(p_input, num, stride, p_ctx) / num;

#if (NEUTON_USE_LOOPUNROLL == 1)

    /* Loop unrolling: Compute 4 outputs at a time */
    loop_cnt = num >> 2U;

    while (loop_cnt > 0U)
    {
        sum += abs(p_input[i * stride] - mean);
        i++;

        sum += abs(p_input[i * stride] - mean);
        i++;

        sum += abs(p_input[i * stride] - mean);
        i++;

        sum += abs(p_input[i * stride] - mean);
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
        sum += abs(p_input[i * stride] - mean);
        i++;

        loop_cnt--;
    }

    return (neuton_i32_t)(sum / num);    
}