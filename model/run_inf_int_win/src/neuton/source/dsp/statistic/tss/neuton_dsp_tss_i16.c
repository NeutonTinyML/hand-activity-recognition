#include "../../../../../neuton/include/neuton/dsp/neuton_dsp_statistic.h"
#include "../../../../../neuton/include/neuton/private/common/neuton_mem.h"

// ///////////////////////////////////////////////////////////////////////////

neuton_u64_t neuton_dsp_tss_i16(const neuton_i16_t* p_input, neuton_u16_t num,
                                neuton_dsp_stat_ctx_i16_t* p_ctx)
{
    neuton_u16_t loop_cnt;
    neuton_i32_t new_val;
    neuton_u64_t tss = 0;

#if (NEUTON_USE_LOOPUNROLL == 1)
    neuton_i32_t* p_input_i32 = (neuton_i32_t*)p_input;
    neuton_i32_t i16x2;

    /* Loop unrolling: Compute 4 outputs at a time */
    loop_cnt = num >> 2U;

    while (loop_cnt > 0U)
    {
        i16x2 = *p_input_i32++;

        new_val = ((i16x2 << 16U) >> 16U);
        tss += new_val * new_val;

        new_val = (i16x2 >> 16U);
        tss += new_val * new_val;

        i16x2 = *p_input_i32++;

        new_val = ((i16x2 << 16U) >> 16U);
        tss += new_val * new_val;

        new_val = (i16x2 >> 16U);
        tss += new_val * new_val;

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
        new_val = *p_input++;
        tss += new_val * new_val;

        loop_cnt--;
    }

    if (p_ctx)
    {
        p_ctx->flags.is.tss = true;
        p_ctx->value.tss    = tss;
    }
    
    return tss;
}

// ///////////////////////////////////////////////////////////////////////////

neuton_u64_t neuton_dsp_tss_i16_s(const neuton_i16_t* p_input, neuton_u16_t num, 
                                size_t stride, neuton_dsp_stat_ctx_i16_t* p_ctx)
{
    neuton_u16_t loop_cnt;
    neuton_i32_t new_val;
    neuton_u64_t tss = 0;
    neuton_u16_t i = 0U;

#if (NEUTON_USE_LOOPUNROLL == 1)

    /* Loop unrolling: Compute 4 outputs at a time */
    loop_cnt = num >> 2;

    while (loop_cnt > 0)
    {
        new_val = p_input[i * stride];
        tss += new_val * new_val;
        i++;

        new_val = p_input[i * stride];
        tss += new_val * new_val;
        i++;

        new_val = p_input[i * stride];
        tss += new_val * new_val;
        i++;

        new_val = p_input[i * stride];
        tss += new_val * new_val;
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
        new_val = p_input[i * stride];
        tss += new_val * new_val;
        i++;

        loop_cnt--;
    }

    if (p_ctx)
    {
        p_ctx->flags.is.tss = true;
        p_ctx->value.tss    = tss;
    }
    
    return tss;
}
