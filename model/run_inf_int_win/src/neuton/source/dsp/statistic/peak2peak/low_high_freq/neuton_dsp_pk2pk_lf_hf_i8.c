#include "../../../../../../neuton/include/neuton/dsp/neuton_dsp_statistic.h"
#include "../../../../../../neuton/include/neuton/private/common/neuton_mem.h"

// ///////////////////////////////////////////////////////////////////////////

void neuton_dsp_pk2pk_lf_hf_i8(const neuton_i8_t* p_input, neuton_u16_t num,
                                size_t window_size, 
                                neuton_i16_t* p_pk2pk_lf, neuton_i16_t* p_pk2pk_hf)
{
    neuton_u16_t loop_cnt;
    neuton_i16_t lf_min;
    neuton_i16_t lf_max;
    neuton_i16_t hf_min;
    neuton_i16_t hf_max;
    neuton_i16_t lf_movavg_sum = 0;
    neuton_i16_t hf_movavg_sum = 0;
    const size_t half_window_size = window_size >> 1;
    const neuton_i8_t* p_input_ws = (p_input + window_size);
    const neuton_i8_t* p_input_hws = (p_input + half_window_size + 1);

    for (size_t i = 0; i < window_size; i++)
        lf_movavg_sum += p_input[i];

    lf_min = lf_movavg_sum;
    lf_max = lf_movavg_sum;
    hf_min = p_input[half_window_size] * window_size - lf_movavg_sum;
    hf_max = hf_min;
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

        if (lf_min > lf_movavg_sum)
            lf_min = lf_movavg_sum;
        else if (lf_max < lf_movavg_sum)
            lf_max = lf_movavg_sum;

        if (hf_min > hf_movavg_sum)
            hf_min = hf_movavg_sum;
        else if (hf_max < hf_movavg_sum)
            hf_max = hf_movavg_sum;
    }

    if (p_pk2pk_hf)
        *p_pk2pk_hf = (hf_max - hf_min) / window_size;

    if (p_pk2pk_lf)
        *p_pk2pk_lf = (lf_max - lf_min) / window_size;
}

// ///////////////////////////////////////////////////////////////////////////

void neuton_dsp_pk2pk_lf_hf_i8_s(const neuton_i8_t* p_input, neuton_u16_t num,
                                size_t stride, size_t window_size, 
                                neuton_i16_t* p_pk2pk_lf, neuton_i16_t* p_pk2pk_hf)
{
    neuton_i16_t lf_min;
    neuton_i16_t lf_max;
    neuton_i16_t hf_min;
    neuton_i16_t hf_max;
    neuton_i16_t lf_movavg_sum = 0;
    neuton_i16_t hf_movavg_sum = 0;
    const size_t half_window_size = window_size >> 1;
    const neuton_u16_t window_stride = stride * window_size;
    const neuton_u16_t half_window_stride = (stride * half_window_size) + stride;
    neuton_u16_t ixstride;

    for (size_t i = 0; i < window_size; i++)
        lf_movavg_sum += p_input[i * stride];

    lf_min = lf_movavg_sum;
    lf_max = lf_movavg_sum;
    hf_min = p_input[half_window_size * stride] * window_size - lf_movavg_sum;
    hf_max = hf_min;
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

        if (lf_min > lf_movavg_sum)
            lf_min = lf_movavg_sum;
        else if (lf_max < lf_movavg_sum)
            lf_max = lf_movavg_sum;

        if (hf_min > hf_movavg_sum)
            hf_min = hf_movavg_sum;
        else if (hf_max < hf_movavg_sum)
            hf_max = hf_movavg_sum;
    }
    
    if (p_pk2pk_hf)
        *p_pk2pk_hf = (hf_max - hf_min) / window_size;

    if (p_pk2pk_lf)
        *p_pk2pk_lf = (lf_max - lf_min) / window_size;
}