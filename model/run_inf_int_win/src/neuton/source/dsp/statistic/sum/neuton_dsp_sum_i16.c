#include "../../../../../neuton/include/neuton/dsp/neuton_dsp_statistic.h"
#include "../../../../../neuton/include/neuton/private/common/neuton_mem.h"

// ///////////////////////////////////////////////////////////////////////////

neuton_i32_t neuton_dsp_sum_i16(const neuton_i16_t* p_input, neuton_u16_t num,
                                neuton_dsp_stat_ctx_i16_t* p_ctx)
{
    neuton_u16_t loop_cnt;
    neuton_i32_t sum = 0;

#if (NEUTON_USE_LOOPUNROLL == 1)
    neuton_i32_t* p_input_i32 = (neuton_i32_t*)p_input;
    neuton_i32_t i16x2;

    /* Loop unrolling: Compute 4 outputs at a time */
    loop_cnt = num >> 2U;

    while (loop_cnt > 0U)
    {
        i16x2 = *p_input_i32++;

        sum += ((i16x2 << 16U) >> 16U);
        sum +=  (i16x2 >> 16U);

        i16x2 = *p_input_i32++;

        sum += ((i16x2 << 16U) >> 16U);
        sum +=  (i16x2 >> 16U);

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
        sum += *p_input++;
        loop_cnt--;
    }

    if (p_ctx)
    {
        p_ctx->flags.is.sum  = true;
        p_ctx->value.sum     = sum;
    }

    return sum;  
}

// ///////////////////////////////////////////////////////////////////////////

neuton_i32_t neuton_dsp_sum_i16_s(const neuton_i16_t* p_input, neuton_u16_t num,
                                size_t stride, neuton_dsp_stat_ctx_i16_t* p_ctx)
{
    neuton_u16_t loop_cnt;
    neuton_i32_t sum = 0;
    neuton_u16_t i = 0U;

#if (NEUTON_USE_LOOPUNROLL == 1)

    /* Loop unrolling: Compute 4 outputs at a time */
    loop_cnt = num >> 2;

    while (loop_cnt > 0)
    {
        sum += p_input[i * stride];
        i++;
        sum += p_input[i * stride];
        i++;
        sum += p_input[i * stride];
        i++;
        sum += p_input[i * stride];
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
        sum += p_input[i * stride];
        i++;
        loop_cnt--;
    }

    if (p_ctx)
    {
        p_ctx->flags.is.sum = true;
        p_ctx->value.sum    = sum;
    }
    
    return sum;    
}