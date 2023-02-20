#include "../../../../../neuton/include/neuton/dsp/neuton_dsp_statistic.h"
#include "../../../../../neuton/include/neuton/private/common/neuton_mem.h"

// ///////////////////////////////////////////////////////////////////////////

void neuton_dsp_tss_sum_i16(const neuton_i16_t* p_input, neuton_u16_t num,
                            neuton_dsp_stat_ctx_i16_t* p_ctx)
{
    if (p_ctx == NULL)
        return;

    neuton_u16_t loop_cnt;
    neuton_i16_t new_val;
    neuton_u64_t tss = 0;
    neuton_i32_t sum = 0;

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
        sum += new_val;

        new_val = (i16x2 >> 16U);
        tss += new_val * new_val;
        sum += new_val;

        i16x2 = *p_input_i32++;

        new_val = ((i16x2 << 16U) >> 16U);
        tss += new_val * new_val;
        sum += new_val;

        new_val = (i16x2 >> 16U);
        tss += new_val * new_val;
        sum += new_val;

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
        sum += new_val;

        loop_cnt--;
    }

    p_ctx->flags.all |= (NEUTON_DSP_STAT_CTX_TSS_FLAG | NEUTON_DSP_STAT_CTX_SUM_FLAG);
    p_ctx->value.sum = sum;
    p_ctx->value.tss = tss;
}

// ///////////////////////////////////////////////////////////////////////////

void neuton_dsp_tss_sum_i16_s(const neuton_i16_t* p_input, neuton_u16_t num,
                              size_t stride, neuton_dsp_stat_ctx_i16_t* p_ctx)
{
    if (p_ctx == NULL)
        return;

    neuton_u64_t tss = 0;
    neuton_i32_t sum = 0;
    neuton_u16_t i = 0;
    neuton_u16_t loop_cnt;
    neuton_i32_t new_val;

#if (NEUTON_USE_LOOPUNROLL == 1)

    /* Loop unrolling: Compute 4 outputs at a time */
    loop_cnt = num >> 2U;

    while (loop_cnt > 0U)
    {
        new_val = p_input[i * stride];
        tss += (new_val * new_val);
        sum += new_val;
        i++;

        new_val = p_input[i * stride];
        tss += (new_val * new_val);
        sum += new_val;
        i++;

        new_val = p_input[i * stride];
        tss += (new_val * new_val);;
        sum += new_val;
        i++;

        new_val = p_input[i * stride];
        tss += (new_val * new_val);
        sum += new_val;
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
        new_val = p_input[i * stride];
        tss += (new_val * new_val);
        sum += new_val;
        i++;

        loop_cnt--;
    }

    p_ctx->flags.all |= (NEUTON_DSP_STAT_CTX_TSS_FLAG | NEUTON_DSP_STAT_CTX_SUM_FLAG);
    p_ctx->value.sum = sum;
    p_ctx->value.tss = tss;
}