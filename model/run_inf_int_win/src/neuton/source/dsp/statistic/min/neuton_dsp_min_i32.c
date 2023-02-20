#include "../../../../../neuton/include/neuton/dsp/neuton_dsp_statistic.h"
#include "../../../../../neuton/include/neuton/private/common/neuton_mem.h"

// ///////////////////////////////////////////////////////////////////////////

neuton_i32_t neuton_dsp_min_i32(const neuton_i32_t* p_input, neuton_u16_t num)
{
    neuton_i32_t new_val;
    neuton_u16_t loop_cnt;

    neuton_i32_t min = *p_input++;
    num--;

#if (NEUTON_USE_LOOPUNROLL == 1)
    /* Loop unrolling: Compute 4 outputs at a time */
    loop_cnt = num >> 2U;

    while (loop_cnt > 0U)
    {
        new_val = *p_input++;

        if (min > new_val)
            min = new_val;

        new_val = *p_input++;;

        if (min > new_val)
            min = new_val;

        new_val = *p_input++;

        if (min > new_val)
            min = new_val;

        new_val = *p_input++;

        if (min > new_val)
            min = new_val;

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
       loop_cnt--;

       if (min > new_val)
           min = new_val;
   }

   return min;
}

// ///////////////////////////////////////////////////////////////////////////

neuton_i32_t neuton_dsp_min_i32_s(const neuton_i32_t* p_input, neuton_u16_t num, 
                                size_t stride)
{
    neuton_u16_t loop_cnt;
    neuton_i32_t new_val;

    neuton_u16_t i = 0U;
    neuton_i32_t min = NEUTON_INT32_MAX;

#if (NEUTON_USE_LOOPUNROLL == 1)
    /* Loop unrolling: Compute 4 outputs at a time */
    loop_cnt = num >> 2U;

    while (loop_cnt > 0U)
    {
        new_val = p_input[i * stride];

        if (min > new_val)
            min = new_val;
        i++;

        new_val = p_input[i * stride];

        if (min > new_val) 
            min = new_val;
        i++;

        new_val = p_input[i * stride];

        if (min > new_val)
            min = new_val;
        i++;

        new_val = p_input[i * stride];

        if (min > new_val)
            min = new_val;
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

        if (min > new_val)
            min = new_val;
        i++;

        loop_cnt--;       
    }

    return min;
}