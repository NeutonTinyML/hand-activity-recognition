#include "../../../../../neuton/include/neuton/dsp/neuton_dsp_statistic.h"
#include "../../../../../neuton/include/neuton/private/common/neuton_mem.h"

// ///////////////////////////////////////////////////////////////////////////

neuton_i16_t neuton_dsp_absmax_i16(const neuton_i16_t* p_input, neuton_u16_t num)
{
    neuton_i16_t new_val;
    neuton_u16_t loop_cnt;

    neuton_i16_t max = 0;

#if (NEUTON_USE_LOOPUNROLL == 1)
    neuton_i32_t* p_input_i32 = (neuton_i32_t*)p_input;
    neuton_i32_t i16x2;

    /* Loop unrolling: Compute 4 outputs at a time */
    loop_cnt = num >> 2U;

    while (loop_cnt > 0U)
    {
        i16x2 = *p_input_i32++;

        new_val = abs((i16x2 << 16U) >> 16U);

        if (max < new_val)
            max = new_val;

        new_val = abs(i16x2 >> 16U);

        if (max < new_val)
            max = new_val;

        i16x2 = *p_input_i32++;

        new_val = abs((i16x2 << 16U) >> 16U);

        if (max < new_val)
            max = new_val;

        new_val = abs(i16x2 >> 16U);

        if (max < new_val)
            max = new_val;

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
       new_val = abs(*p_input++);
       loop_cnt--;

       if (max < new_val)
           max = new_val;
   }

   return max;
}

// ///////////////////////////////////////////////////////////////////////////

neuton_i16_t neuton_dsp_absmax_i16_s(const neuton_i16_t* p_input, neuton_u16_t num,
                                size_t stride)
{
    neuton_u16_t loop_cnt;
    neuton_i16_t new_val;

    neuton_u16_t i = 0U;
    neuton_i16_t max = 0;

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