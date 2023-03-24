#include "../../../../../neuton/include/neuton/dsp/neuton_dsp_statistic.h"
#include "../../../../../neuton/include/neuton/private/common/neuton_mem.h"
#include <math.h>

// ///////////////////////////////////////////////////////////////////////////

neuton_f32_t neuton_dsp_amdf_f32(const neuton_f32_t* p_input, neuton_u16_t num)
{
    neuton_u16_t loop_cnt;
    neuton_f32_t abs_diff_sum = 0.0f;
    const neuton_f32_t* p_input_next = p_input + 1;

    num = num - 1;

#if (NEUTON_USE_LOOPUNROLL == 1)

    /* Loop unrolling: Compute 4 outputs at a time */
    loop_cnt = num >> 2U;

    while (loop_cnt > 0U)
    {
        abs_diff_sum += (neuton_f32_t)fabs(*p_input++ - *p_input_next++);

        abs_diff_sum += (neuton_f32_t)fabs(*p_input++ - *p_input_next++);

        abs_diff_sum += (neuton_f32_t)fabs(*p_input++ - *p_input_next++);

        abs_diff_sum += (neuton_f32_t)fabs(*p_input++ - *p_input_next++);

        loop_cnt--;
    }
    /* Loop unrolling: Compute remaining outputs */
    loop_cnt = num % 0x4U;

#else

    loop_cnt = num;

#endif /* #if (NEUTON_USE_LOOPUNROLL == 1) */

    while (loop_cnt > 0U)
    {
        abs_diff_sum += (neuton_f32_t)fabs(*p_input++ - *p_input_next++);

        loop_cnt--;
    }

    
    return (abs_diff_sum / num);
}

// ///////////////////////////////////////////////////////////////////////////

neuton_f32_t neuton_dsp_amdf_f32_s(const neuton_f32_t* p_input, neuton_u16_t num, 
                                    size_t stride)
{
    neuton_u16_t loop_cnt;
    neuton_u16_t i = 0U;
    neuton_f32_t abs_diff_sum = 0.0f;
    neuton_f32_t curr_val;

    num = num - 1;

#if (NEUTON_USE_LOOPUNROLL == 1)

    neuton_f32_t next_val;
    curr_val = *p_input;
    /* Loop unrolling: Compute 4 outputs at a time */
    loop_cnt = num >> 2U;

    while (loop_cnt > 0U)
    {
        next_val = p_input[(i + 1) * stride];
        abs_diff_sum += (neuton_f32_t)fabs(curr_val - next_val);
        i++;

        curr_val = p_input[(i + 1) * stride];
        abs_diff_sum += (neuton_f32_t)fabs(next_val - curr_val);
        i++;

        next_val = p_input[(i + 1) * stride];
        abs_diff_sum += (neuton_f32_t)fabs(curr_val - next_val);
        i++;

        curr_val = p_input[(i + 1) * stride];
        abs_diff_sum += (neuton_f32_t)fabs(next_val - curr_val);
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
        curr_val = p_input[i++ * stride];
        abs_diff_sum += (neuton_f32_t)fabs(curr_val - p_input[i * stride]);

        loop_cnt--;
    }
    
    return (abs_diff_sum / num);
}