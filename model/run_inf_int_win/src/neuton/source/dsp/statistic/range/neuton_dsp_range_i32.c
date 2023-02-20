#include "../../../../../neuton/include/neuton/dsp/neuton_dsp_statistic.h"

// ///////////////////////////////////////////////////////////////////////////

neuton_u32_t neuton_dsp_range_i32(const neuton_i32_t* p_input, neuton_u16_t num)
{
    neuton_i32_t min;
    neuton_i32_t max;

    neuton_dsp_min_max_i32(p_input, num, &min, &max);

    return (neuton_u32_t)(max - min);
}

// ///////////////////////////////////////////////////////////////////////////

neuton_u32_t neuton_dsp_range_i32_s(const neuton_i32_t* p_input, neuton_u16_t num,
                                    size_t stride)
{
    neuton_i32_t min;
    neuton_i32_t max;

    neuton_dsp_min_max_i32_s(p_input, num, stride, &min, &max);

    return (neuton_u32_t)(max - min);    
}