#include "../../../../../neuton/include/neuton/dsp/neuton_dsp_statistic.h"

// ///////////////////////////////////////////////////////////////////////////

neuton_f32_t neuton_dsp_range_f32(const neuton_f32_t* p_input, neuton_u16_t num)
{
    neuton_f32_t min;
    neuton_f32_t max;

    neuton_dsp_min_max_f32(p_input, num, &min, &max);

    return max - min;
}

// ///////////////////////////////////////////////////////////////////////////

neuton_f32_t neuton_dsp_range_f32_s(const neuton_f32_t* p_input, neuton_u16_t num,
                                    size_t stride)
{
    neuton_f32_t min;
    neuton_f32_t max;

    neuton_dsp_min_max_f32_s(p_input, num, stride, &min, &max);

    return max - min;    
}