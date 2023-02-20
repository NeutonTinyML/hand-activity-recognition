#include "../../../../../neuton/include/neuton/dsp/neuton_dsp_statistic.h"
#include "../../../../../neuton/include/neuton/private/common/neuton_mem.h"

// ///////////////////////////////////////////////////////////////////////////

void neuton_dsp_min_max_f32(const neuton_f32_t* p_input, neuton_u16_t num,
                            neuton_f32_t* p_min, neuton_f32_t* p_max)
{
    neuton_f32_t new_val;
    neuton_f32_t max = NEUTON_F32_MIN;
    neuton_f32_t min = *p_input;
    neuton_u16_t loop_cnt;

#if (NEUTON_USE_LOOPUNROLL == 1)
    /* Loop unrolling: Compute 4 outputs at a time */
    loop_cnt = num  >> 2U;

    while (loop_cnt > 0U)
    {
        new_val = *p_input++;

        if (max < new_val)
            max = new_val;
        else if (min > new_val)
            min = new_val;

        new_val = *p_input++;

        if (max < new_val)
            max = new_val;
        else if (min > new_val)
            min = new_val;

        new_val = *p_input++;

        if (max < new_val)
            max = new_val;
        else if (min > new_val)
            min = new_val;

        new_val = *p_input++;

        if (max < new_val)
            max = new_val;
        else if (min > new_val)
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

        if (max < new_val)
            max = new_val;
        else if (min > new_val)
            min = new_val;
   }

   *p_min = min;
   *p_max = max;  
}

// ///////////////////////////////////////////////////////////////////////////

void neuton_dsp_min_max_f32_s(const neuton_f32_t* p_input, neuton_u16_t num, 
                            size_t stride,
                            neuton_f32_t* p_min, neuton_f32_t* p_max)
{
    neuton_f32_t new_val;
    neuton_f32_t max = NEUTON_F32_MIN;
    neuton_f32_t min = NEUTON_F32_MAX;
    neuton_u16_t i = 0U;
    neuton_u16_t loop_cnt;

#if (NEUTON_USE_LOOPUNROLL == 1)
    /* Loop unrolling: Compute 4 outputs at a time */
    loop_cnt = num >> 2U;

    while (loop_cnt > 0U)
    {
        new_val = p_input[i * stride];

        if (max < new_val)
            max = new_val;
        else if (min > new_val)
            min = new_val;
        i++;

        new_val = p_input[i * stride];

        if (max < new_val)
            max = new_val;
        else if (min > new_val)
            min = new_val;
        i++;

        new_val = p_input[i * stride];

        if (max < new_val)
            max = new_val;
        else if (min > new_val)
            min = new_val;
        i++;

        new_val = p_input[i * stride];

        if (max < new_val)
            max = new_val;
        else if (min > new_val)
            min = new_val;;
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

        if (max < new_val)
            max = new_val;
        else if (min > new_val)
            min = new_val;
        i++;

        loop_cnt--;       
    }

   *p_min = min;
   *p_max = max;
}