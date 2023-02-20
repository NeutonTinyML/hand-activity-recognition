#include "../../../../../neuton/include/neuton/dsp/neuton_dsp_statistic.h"
#include "../../../../../neuton/include/neuton/private/common/neuton_mem.h"

// ///////////////////////////////////////////////////////////////////////////

void neuton_dsp_min_max_i8(const neuton_i8_t* p_input, neuton_u16_t num,
                            neuton_i8_t* p_min, neuton_i8_t* p_max)
{
   neuton_i8_t new_val;
   neuton_i8_t max = NEUTON_INT8_MIN;
   neuton_i8_t min = *p_input;
   neuton_u16_t loop_cnt;

#if (NEUTON_USE_LOOPUNROLL == 1)
    neuton_i32_t* p_input_i32 = (neuton_i32_t*)p_input;
    neuton_i32_t i8x4;

    /* Loop unrolling: Compute 4 outputs at a time */
    loop_cnt = num >> 2U;

    while (loop_cnt > 0U)
    {
        i8x4 = *p_input_i32++;

        new_val = ((i8x4 << 24U) >> 24U);

        if (max < new_val)
            max = new_val;
        else if (min > new_val)
            min = new_val;

        new_val = ((i8x4 << 16U) >> 24U);

        if (max < new_val)
            max = new_val;
        else if (min > new_val)
            min = new_val;

        new_val = ((i8x4 <<  8U) >> 24U);

        if (max < new_val)
            max = new_val;
        else if (min > new_val)
            min = new_val;

        new_val =  (i8x4 >> 24U);

        if (max < new_val)
            max = new_val;
        else if (min > new_val)
            min = new_val;

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

void neuton_dsp_min_max_i8_s(const neuton_i8_t* p_input, neuton_u16_t num, 
                            size_t stride,
                            neuton_i8_t* p_min, neuton_i8_t* p_max)
{
    neuton_i8_t new_val;
    neuton_i8_t max = NEUTON_INT8_MIN;
    neuton_i8_t min = NEUTON_INT8_MAX;
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