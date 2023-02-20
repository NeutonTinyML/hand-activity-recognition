#include "../../../../../neuton/include/neuton/dsp/neuton_dsp_statistic.h"

// ///////////////////////////////////////////////////////////////////////////

neuton_u16_t neuton_dsp_range_i16(const neuton_i16_t* p_input, neuton_u16_t num)
{
    neuton_i16_t min;
    neuton_i16_t max;

    neuton_dsp_min_max_i16(p_input, num, &min, &max);

    return (neuton_u16_t)(max - min);
}

// ///////////////////////////////////////////////////////////////////////////

neuton_u16_t neuton_dsp_range_i16_s(const neuton_i16_t* p_input, neuton_u16_t num,
                                    size_t stride)
{
    neuton_i16_t min;
    neuton_i16_t max;

    neuton_dsp_min_max_i16_s(p_input, num, stride, &min, &max);

    return (neuton_u16_t)(max - min);    
}