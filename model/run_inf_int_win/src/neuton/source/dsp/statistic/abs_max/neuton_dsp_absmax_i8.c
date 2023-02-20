#include "../../../../../neuton/include/neuton/dsp/neuton_dsp_statistic.h"
#include "../../../../../neuton/include/neuton/private/common/neuton_mem.h"
#include <math.h>

// ///////////////////////////////////////////////////////////////////////////

neuton_i8_t neuton_dsp_absmax_i8(const neuton_i8_t* p_input, neuton_u16_t num)
{
    neuton_i8_t new_val;
    neuton_u16_t loop_cnt;

    neuton_i8_t max = 0;

#if (NEUTON_USE_LOOPUNROLL == 1)
    neuton_i32_t* p_input_i32 = (neuton_i32_t*)p_input;
    neuton_i32_t i8x4;

    /* Loop unrolling: Compute 4 outputs at a time */
    loop_cnt = num >> 2U;

    while (loop_cnt > 0U)
    {
        i8x4 = *p_input_i32++;

        new_val = abs((i8x4 << 24U) >> 24U);

        if (max < new_val)
            max = new_val;

        new_val = abs((i8x4 << 16U) >> 24U);

        if (max < new_val)
            max = new_val;

        new_val = abs((i8x4 <<  8U) >> 24U);

        if (max < new_val)
            max = new_val;

        new_val = abs(i8x4 >> 24U);

        if (max < new_val)
            max = new_val;

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
       new_val = abs(*p_input++);
       loop_cnt--;

       if (max < new_val)
           max = new_val;
   }

   return max;
}

// ///////////////////////////////////////////////////////////////////////////

neuton_i8_t neuton_dsp_absmax_i8_s(const neuton_i8_t* p_input, neuton_u16_t num,
                                size_t stride)
{
    neuton_u16_t loop_cnt;
    neuton_i8_t new_val;

    neuton_u16_t i = 0U;
    neuton_i8_t max = 0;

#if (NEUTON_USE_LOOPUNROLL == 1)
    /* Loop unrolling: Compute 4 outputs at a time */
    loop_cnt = num >> 2U;

    while (loop_cnt > 0U)
    {
        new_val = abs(p_input[i * stride]);

        if (max < new_val)
            max = new_val;
        i++;

        new_val = abs(p_input[i * stride]);

        if (max < new_val) 
            max = new_val;
        i++;

        new_val = abs(p_input[i * stride]);

        if (max < new_val)
            max = new_val;
        i++;

        new_val = abs(p_input[i * stride]);

        if (max < new_val)
            max = new_val;
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
        new_val = abs(p_input[i * stride]);

        if (max < new_val)
            max = new_val;
        i++;

        loop_cnt--;       
    }

    return max;    
}