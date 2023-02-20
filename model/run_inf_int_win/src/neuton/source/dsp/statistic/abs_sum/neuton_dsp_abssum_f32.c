#include "../../../../../neuton/include/neuton/dsp/neuton_dsp_statistic.h"
#include "../../../../../neuton/include/neuton/private/common/neuton_mem.h"
#include <math.h>

// ///////////////////////////////////////////////////////////////////////////

neuton_f32_t neuton_dsp_abssum_f32(const neuton_f32_t* p_input, neuton_u16_t num,
                                    neuton_dsp_stat_ctx_f32_t* p_ctx)
{
    neuton_u16_t loop_cnt;
    neuton_f32_t sum = 0.0f;

#if (NEUTON_USE_LOOPUNROLL == 1)

    /* Loop unrolling: Compute 4 outputs at a time */
    loop_cnt = num >> 2U;

    while (loop_cnt > 0U)
    {
        sum += fabsf(*p_input++);
        sum += fabsf(*p_input++);
        sum += fabsf(*p_input++);
        sum += fabsf(*p_input++);

        loop_cnt--;
    }
    /* Loop unrolling: Compute remaining outputs */
    loop_cnt = num % 0x4U;

#else

    loop_cnt = num;

#endif /* #if (NEUTON_USE_LOOPUNROLL == 1) */

    while (loop_cnt > 0U)
    {
        sum += fabsf(*p_input++);
        loop_cnt--;
    }

    if (p_ctx)
    {
        p_ctx->flags.is.abssum = true;
        p_ctx->value.abssum    = sum;
    }
    
    return sum;
}

// ///////////////////////////////////////////////////////////////////////////

neuton_f32_t neuton_dsp_abssum_f32_s(const neuton_f32_t* p_input, neuton_u16_t num, 
                                size_t stride, neuton_dsp_stat_ctx_f32_t* p_ctx)
{
    neuton_u16_t loop_cnt;
    neuton_f32_t sum = 0;
    neuton_u16_t i = 0U;

#if (NEUTON_USE_LOOPUNROLL == 1)

    /* Loop unrolling: Compute 4 outputs at a time */
    loop_cnt = num >> 2;

    while (loop_cnt > 0)
    {
        sum += fabsf(p_input[i * stride]);
        i++;
        sum += fabsf(p_input[i * stride]);
        i++;
        sum += fabsf(p_input[i * stride]);
        i++;
        sum += fabsf(p_input[i * stride]);
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
        sum += fabsf(p_input[i * stride]);
        i++;
        loop_cnt--;
    }

    if (p_ctx)
    {
        p_ctx->flags.is.abssum = true;
        p_ctx->value.abssum    = sum;
    }
    
    return sum;
}
