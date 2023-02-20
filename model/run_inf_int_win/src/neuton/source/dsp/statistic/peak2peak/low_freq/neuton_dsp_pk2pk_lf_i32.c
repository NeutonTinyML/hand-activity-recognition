#include "../../../../../../neuton/include/neuton/dsp/neuton_dsp_statistic.h"
#include "../../../../../../neuton/include/neuton/private/common/neuton_mem.h"

// ///////////////////////////////////////////////////////////////////////////

neuton_i32_t neuton_dsp_pk2pk_lf_i32(const neuton_i32_t* p_input, neuton_u16_t num,
                                     size_t window_size)
{
    neuton_u16_t loop_cnt;
    neuton_i64_t min;
    neuton_i64_t max;
    neuton_i64_t lf_movavg_sum = 0;
    const neuton_i32_t* p_input_ws = (p_input + window_size);

    for (neuton_u16_t i = 0; i < window_size; i++)
        lf_movavg_sum += p_input[i];

    min = lf_movavg_sum;
    max = lf_movavg_sum;
    num -= window_size;
    loop_cnt = num;

    while (loop_cnt > 0U)
    {
        /* Сompute the low frequency moving average sum by subtracting the current point
            and adding the point at the end of the moving window */
        lf_movavg_sum = lf_movavg_sum + *p_input_ws++ - *p_input++;

        loop_cnt--;

        if (min > lf_movavg_sum)
            min = lf_movavg_sum;
        else if (max < lf_movavg_sum)
            max = lf_movavg_sum;
    }

    return (neuton_i32_t)((max - min) / window_size);
}

// ///////////////////////////////////////////////////////////////////////////

neuton_i32_t neuton_dsp_pk2pk_lf_i32_s(const neuton_i32_t* p_input, neuton_u16_t num,
                                     size_t stride, size_t window_size)
{
    neuton_i64_t min;
    neuton_i64_t max;
    neuton_i64_t lf_movavg_sum = 0;
    const neuton_u16_t window_stride = stride * window_size;
    neuton_u16_t ixstride;

    for (size_t i = 0; i < window_size; i++)
        lf_movavg_sum += p_input[i * stride];

    min = lf_movavg_sum;
    max = lf_movavg_sum;
    num -= window_size;

    for (neuton_u16_t i = 0; i < num; i++)
    {
        /* Сompute the low frequency moving average sum by subtracting the current point within stride
            and adding the point at the end of the moving window */
        ixstride = i * stride;
        lf_movavg_sum = lf_movavg_sum + p_input[ixstride + window_stride] - p_input[ixstride];

        if (min > lf_movavg_sum)
            min = lf_movavg_sum;
        else if (max < lf_movavg_sum)
            max = lf_movavg_sum;
    }
    
    return (neuton_i32_t)((max - min) / window_size);
}