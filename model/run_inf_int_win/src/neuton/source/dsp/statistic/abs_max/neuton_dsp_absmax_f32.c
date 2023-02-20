#include "../../../../../neuton/include/neuton/dsp/neuton_dsp_statistic.h"
#include "../../../../../neuton/include/neuton/private/common/neuton_mem.h"
#include <math.h>

// ///////////////////////////////////////////////////////////////////////////

neuton_f32_t neuton_dsp_absmax_f32(const neuton_f32_t* p_input, neuton_u16_t num)
{
    neuton_f32_t new_val;
    neuton_u16_t loop_cnt;

    neuton_f32_t max = fabsf(*p_input++);
    num--;

#if (NEUTON_USE_LOOPUNROLL == 1)
    /* Loop unrolling: Compute 4 outputs at a time */
    loop_cnt = num >> 2U;

    while (loop_cnt > 0U)
    {
        new_val = fabsf(*p_input++);

        if (max < new_val)
            max = new_val;

        new_val = fabsf(*p_input++);

        if (max < new_val)
            max = new_val;

        new_val = fabsf(*p_input++);

        if (max < new_val)
            max = new_val;

        new_val = fabsf(*p_input++);

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
       new_val = fabsf(*p_input++);
       loop_cnt--;

       if (max < new_val)
           max = new_val;
   }

   return max;
}

// ///////////////////////////////////////////////////////////////////////////

neuton_f32_t neuton_dsp_absmax_f32_s(const neuton_f32_t* p_input, neuton_u16_t num, 
                                    size_t stride)
{
    neuton_u16_t loop_cnt;
    neuton_f32_t new_val;

    neuton_u16_t i = 0U;
    neuton_f32_t max = NEUTON_F32_MIN;

#if (NEUTON_USE_LOOPUNROLL == 1)
    /* Loop unrolling: Compute 4 outputs at a time */
    loop_cnt = num >> 2U;

    while (loop_cnt > 0U)
    {
        new_val = fabsf(p_input[i * stride]);

        if (max < new_val)
            max = new_val;
        i++;

        new_val = fabsf(p_input[i * stride]);

        if (max < new_val) 
            max = new_val;
        i++;

        new_val = fabsf(p_input[i * stride]);

        if (max < new_val)
            max = new_val;
        i++;

        new_val = fabsf(p_input[i * stride]);

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
        new_val = fabsf(p_input[i * stride]);

        if (max < new_val)
            max = new_val;
        i++;

        loop_cnt--;       
    }

    return max;
}