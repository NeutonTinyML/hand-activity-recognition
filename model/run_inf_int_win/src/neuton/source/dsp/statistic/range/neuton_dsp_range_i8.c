#include "../../../../../neuton/include/neuton/dsp/neuton_dsp_statistic.h"

// ///////////////////////////////////////////////////////////////////////////

neuton_u8_t neuton_dsp_range_i8(const neuton_i8_t* p_input, neuton_u16_t num)
{
    neuton_i8_t min;
    neuton_i8_t max;

    neuton_dsp_min_max_i8(p_input, num, &min, &max);

    return (neuton_u8_t)(max - min);
}

// ///////////////////////////////////////////////////////////////////////////

neuton_u8_t neuton_dsp_range_i8_s(const neuton_i8_t* p_input, neuton_u16_t num,
                                    size_t stride)
{
    neuton_i8_t min;
    neuton_i8_t max;

    neuton_dsp_min_max_i8_s(p_input, num, stride, &min, &max);

    return (neuton_u8_t)(max - min);    
}