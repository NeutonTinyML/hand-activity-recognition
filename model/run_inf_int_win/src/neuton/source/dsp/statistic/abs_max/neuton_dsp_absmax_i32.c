#include "../../../../../neuton/include/neuton/dsp/neuton_dsp_statistic.h"
#include "../../../../../neuton/include/neuton/private/common/neuton_mem.h"

// ///////////////////////////////////////////////////////////////////////////

neuton_i32_t neuton_dsp_absmax_i32(const neuton_i32_t* p_input, neuton_u16_t num)
{
    neuton_i32_t new_val;
    neuton_u16_t loop_cnt;

    neuton_i32_t max = 0;

#if (NEUTON_USE_LOOPUNROLL == 1)
    /* Loop unrolling: Compute 4 outputs at a time */
    loop_cnt = num >> 2U;

    while (loop_cnt > 0U)
    {
        new_val = abs(*p_input++);

        if (max < new_val)
            max = new_val;

        new_val = abs(*p_input++);

        if (max < new_val)
            max = new_val;

        new_val = abs(*p_input++);

        if (max < new_val)
            max = new_val;

        new_val = abs(*p_input++);

        if (max < new_val)
            max = new_val;

        loop_cnt--;
    }
    /* Loop unrolling: Compute remaining outputs */
    loop_cnt = num % 0x4U;

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

neuton_i32_t neuton_dsp_absmax_i32_s(const neuton_i32_t* p_input, neuton_u16_t num,
                                    size_t stride)
{
    neuton_u16_t loop_cnt;
    neuton_i32_t new_val;

    neuton_u16_t i = 0U;
    neuton_i32_t max = NEUTON_INT32_MIN;

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