#include "../../../../../neuton/include/neuton/dsp/neuton_dsp_statistic.h"
#include "../../../../../neuton/include/neuton/private/common/neuton_mem.h"

// ///////////////////////////////////////////////////////////////////////////

void neuton_dsp_tss_sum_f32(const neuton_f32_t* p_input, neuton_u16_t num,
                            neuton_dsp_stat_ctx_f32_t* p_ctx)
{
    if (p_ctx == NULL)
        return;

    neuton_u16_t loop_cnt;
    neuton_f32_t new_val;
    neuton_f32_t tss = 0;
    neuton_f32_t sum = 0;

#if (NEUTON_USE_LOOPUNROLL == 1)

    /* Loop unrolling: Compute 4 outputs at a time */
    loop_cnt = num >> 2U;

    while (loop_cnt > 0U)
    {
        new_val = *p_input++;
        tss += (new_val * new_val);
        sum += new_val;

        new_val = *p_input++;
        tss += (new_val * new_val);
        sum += new_val;

        new_val = *p_input++;
        tss += (new_val * new_val);;
        sum += new_val;

        new_val = *p_input++;
        tss += (new_val * new_val);
        sum += new_val;

        loop_cnt--;
    }
    
    /* Loop unrolling: Compute remaining outputs */
    loop_cnt = num % 0x4U;

#else

    loop_cnt = num;

#endif /* #if (NEUTON_USE_LOOPUNROLL == 1) */

    while (loop_cnt > 0U)
    {
        new_val = *p_input++;
        tss += (new_val * new_val);
        sum += new_val;

        loop_cnt--;
    }

    p_ctx->flags.all |= (NEUTON_DSP_STAT_CTX_TSS_FLAG | NEUTON_DSP_STAT_CTX_SUM_FLAG);
    p_ctx->value.sum = sum;
    p_ctx->value.tss = tss;
}

// ///////////////////////////////////////////////////////////////////////////

void neuton_dsp_tss_sum_f32_s(const neuton_f32_t* p_input, neuton_u16_t num,
                              size_t stride, neuton_dsp_stat_ctx_f32_t* p_ctx)
{
    if (p_ctx == NULL)
        return;

    neuton_f32_t new_val;
    neuton_f32_t tss = 0;
    neuton_f32_t sum = 0;
    neuton_u16_t loop_cnt;
    neuton_u16_t i = 0;

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