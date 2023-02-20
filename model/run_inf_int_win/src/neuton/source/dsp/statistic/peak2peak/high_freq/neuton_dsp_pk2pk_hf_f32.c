#include "../../../../../../neuton/include/neuton/dsp/neuton_dsp_statistic.h"
#include "../../../../../../neuton/include/neuton/private/common/neuton_mem.h"

// ///////////////////////////////////////////////////////////////////////////

neuton_f32_t neuton_dsp_pk2pk_hf_f32(const neuton_f32_t* p_input, neuton_u16_t num,
                                     size_t window_size)
{
    neuton_u16_t loop_cnt;
    neuton_f32_t min;
    neuton_f32_t max;
    neuton_f32_t lf_movavg_sum = 0;
    neuton_f32_t hf_movavg_sum = 0;
    const size_t half_window_size = window_size >> 1;
    const neuton_f32_t* p_input_ws = (p_input + window_size);
    const neuton_f32_t* p_input_hws = (p_input + half_window_size + 1);

    for (neuton_u16_t i = 0; i < window_size; i++)
        lf_movavg_sum += p_input[i];

    min = p_input[half_window_size] * window_size - lf_movavg_sum;
    max = min;
    num -= window_size;
    loop_cnt = num;

    while (loop_cnt > 0U)
    {
        /* Сompute the low frequency moving average sum by subtracting the current point
            and adding the point at the end of the moving window */
        lf_movavg_sum = lf_movavg_sum + *p_input_ws++ - *p_input++;

        /* Сompute the high frequency moving average sum by subtracting low frequency
        part from signal */
        hf_movavg_sum = (*p_input_hws++ * window_size) - lf_movavg_sum;

        loop_cnt--;

        if (min > hf_movavg_sum)
            min = hf_movavg_sum;
        else if (max < hf_movavg_sum)
            max = hf_movavg_sum;
    }

    return (max - min) / window_size;
}

// ///////////////////////////////////////////////////////////////////////////

neuton_f32_t neuton_dsp_pk2pk_hf_f32_s(const neuton_f32_t* p_input, neuton_u16_t num,
                                     size_t stride, size_t window_size)
{
    neuton_f32_t min;
    neuton_f32_t max;
    neuton_f32_t lf_movavg_sum = 0;
    neuton_f32_t hf_movavg_sum = 0;
    const size_t half_window_size = window_size >> 1;
    const neuton_u16_t window_stride = stride * window_size;
    const neuton_u16_t half_window_stride = (stride * half_window_size) + stride;
    neuton_u16_t ixstride;

    for (size_t i = 0; i < window_size; i++)
        lf_movavg_sum += p_input[i * stride];

    min = p_input[half_window_size * stride] * window_size - lf_movavg_sum;
    max = min;
    num -= window_size;

    for (neuton_u16_t i = 0; i < num; i++)
    {
        /* Сompute the low frequency moving average sum by subtracting the current point within stride
            and adding the point at the end of the moving window */
        ixstride = i * stride;
        lf_movavg_sum = lf_movavg_sum + p_input[ixstride + window_stride] - p_input[ixstride];

        /* Сompute the high frequency moving average sum by subtracting low frequency
        part from signal using values ​​in increments of 'half_window_stride' */
        hf_movavg_sum = (p_input[ixstride + half_window_stride] * window_size) - lf_movavg_sum;

        if (min > hf_movavg_sum)
            min = hf_movavg_sum;
        else if (max < hf_movavg_sum)
            max = hf_movavg_sum;
    }

    return (max - min) / window_size;
}
