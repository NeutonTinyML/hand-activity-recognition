#include "../../../../../neuton/include/neuton/dsp/support/neuton_dsp_windowing.h"
#include <math.h>

#ifndef M_PI
#define M_PI       3.14159265358979323846f   // pi
#endif

//////////////////////////////////////////////////////////////////////////////

void neuton_dsp_window_hanning_f32(neuton_f32_t* p_window, neuton_u16_t window_size)
{
    for (neuton_u16_t i = 0; i < window_size; ++i)
        p_window[i] = 0.5 - (0.5 * cos(2 * M_PI * ((neuton_f32_t)i) / (window_size - 1)));
}
