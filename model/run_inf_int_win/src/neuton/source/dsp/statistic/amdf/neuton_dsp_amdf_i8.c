#include "../../../../../neuton/include/neuton/dsp/neuton_dsp_statistic.h"
#include "../../../../../neuton/include/neuton/private/common/neuton_mem.h"
#include <math.h>

// ///////////////////////////////////////////////////////////////////////////

neuton_i16_t neuton_dsp_amdf_i8(const neuton_i8_t* p_input, neuton_u16_t num)
{
    neuton_u16_t loop_cnt;
    neuton_u32_t abs_diff_sum = 0;
    neuton_i8_t in = *p_input;

    num = num - 1;

#if (NEUTON_USE_LOOPUNROLL == 1)

    /* Loop unrolling: Compute 4 outputs at a time */
    loop_cnt = num >> 2U;

    neuton_i32_t i8x4;
    neuton_i32_t* p_input_i32 = (neuton_i32_t *)p_input;

    while (loop_cnt > 0U)
    {
        i8x4 = *p_input_i32++;

        abs_diff_sum += abs(in - ((i8x4 << 16U) >> 24U));

        abs_diff_sum += abs(((i8x4 << 16U) >> 24U) - ((i8x4 << 8U) >> 24U));

        abs_diff_sum += abs(((i8x4 << 8U) >> 24U) - (i8x4 >> 24U));

        in = (int8_t)(((*p_input_i32) << 24U) >> 24U);

        abs_diff_sum += abs((i8x4 >> 24U) - in);

        loop_cnt--;
    }

    /* Loop unrolling: Compute remaining outputs */
    loop_cnt = num % 0x4U;
    p_input  = (neuton_i8_t*)p_input_i32;

#else

    loop_cnt = num;

#endif /* #if (NEUTON_USE_LOOPUNROLL == 1) */

    in = *p_input++;

    while (loop_cnt > 0U)
    {
        abs_diff_sum += abs(in - *p_input);
        in = *p_input++;

        loop_cnt--;
    }

    
    return (neuton_i16_t)((abs_diff_sum  * NEUTON_INT_TO_F32_PRECISION_FACTOR) / num);
}

// ///////////////////////////////////////////////////////////////////////////

neuton_i16_t neuton_dsp_amdf_i8_s(const neuton_i8_t* p_input, neuton_u16_t num, 
                                size_t stride)
{
    neuton_u16_t loop_cnt;
    neuton_u16_t i = 0U;
    neuton_u32_t abs_diff_sum = 0;
    neuton_i8_t curr_val;

    num = num - 1;

#if (NEUTON_USE_LOOPUNROLL == 1)

    neuton_i8_t next_val;
    curr_val = *p_input;
    /* Loop unrolling: Compute 4 outputs at a time */
    loop_cnt = num >> 2U;

    while (loop_cnt > 0U)
    {
        next_val = p_input[(i + 1) * stride];
        abs_diff_sum += abs(curr_val - next_val);
        i++;

        curr_val = p_input[(i + 1) * stride];
        abs_diff_sum += abs(next_val - curr_val);
        i++;

        next_val = p_input[(i + 1) * stride];
        abs_diff_sum += abs(curr_val - next_val);
        i++;

        curr_val = p_input[(i + 1) * stride];
        abs_diff_sum += abs(next_val - curr_val);
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
        abs_diff_sum += abs(curr_val - p_input[i * stride]);

        loop_cnt--;
    }
    
    return (neuton_i16_t)((abs_diff_sum  * NEUTON_INT_TO_F32_PRECISION_FACTOR) / num);
}