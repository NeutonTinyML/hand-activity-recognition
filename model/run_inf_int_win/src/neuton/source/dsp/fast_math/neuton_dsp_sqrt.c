#include "../../../../neuton/include/neuton/dsp/neuton_dsp_fast_math.h"
#include <math.h>

// ///////////////////////////////////////////////////////////////////////////

neuton_f32_t neuton_dsp_sqrt_f32(const neuton_f32_t x)
{
    return sqrtf(x);
}

// ///////////////////////////////////////////////////////////////////////////

neuton_u32_t neuton_dsp_sqrt_u32(const neuton_u32_t x)
{
    if (x == 0) return 0;

    uint32_t div;
    uint32_t temp;
    uint32_t result = x;

    if (x & 0xFFFF0000L)
        if (x & 0xFF000000L)
            div = 0x3FFF;
        else
            div = 0x3FF;
    else
        if (x & 0x0FF00L) div = 0x3F;
        else div = (x > 4) ? 0x7 : x;

    while (1)
    {
        temp = x / div + div;
        div = temp >> 1;
        div += temp & 1;
        if (result > div)
        {
            result = div;
        }
        else
        {
            if (1 / result == result - 1 && 1 % result == 0)
                result--;
            return result;
        }
    }
}