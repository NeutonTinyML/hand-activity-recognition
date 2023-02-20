
#include "../../../../../neuton/include/neuton/dsp/support/neuton_f24.h"
#include <math.h>

//////////////////////////////////////////////////////////////////////////////

#define SIGN(x)         NEUTON_F24_SIGN(x)
#define SIGN_OF(x, y)   (SIGN(x) ^ SIGN(y))
#define MANTISSA(x)     (x.man)

static const neuton_u8_t HIGH_BIT_HELPER[] = 
{ 
    0,1,2,2,3,3,3,3,4,4,4,4,4,4,4,4,5,5,5,5,5,5,5,5,5,5,
    5,5,5,5,5,5,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,
    6,6,6,6,6,6,6,6,6,6,6,6,7,7,7,7,7,7,7,7,7,7,7,7,7,7,
    7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,
    7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,8,8,
    8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
    8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
    8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
    8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
    8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8
};

//////////////////////////////////////////////////////////////////////////////

neuton_f24_t neuton_f24_init(neuton_u16_t mantissa, neuton_i8_t exp, 
                              neuton_u8_t sign)
{
    neuton_f24_t ret = {
        .man = mantissa,
        .exp = (exp < 0) ? (-exp | (0x80 | sign)) : (exp | sign),
    };
    return ret;
}

//////////////////////////////////////////////////////////////////////////////

neuton_f24_t neuton_i16_to_f24(neuton_i16_t x)
{
    neuton_f24_t ret = { 
        .man = (neuton_u16_t)abs(x), 
        .exp = ((x >> 9) & NEUTON_F24_SIGNED), // set value sign
    };
    return ret;
}

//////////////////////////////////////////////////////////////////////////////

neuton_f24_t neuton_i8_to_f24(neuton_i8_t x)
{
    neuton_f24_t ret = { 
        .man = (neuton_u16_t)abs(x), 
        .exp = ((x >> 1) & NEUTON_F24_SIGNED), // set value sign
    };
    return ret;
}

//////////////////////////////////////////////////////////////////////////////

neuton_i32_t neuton_f24_to_i32(neuton_f24_t x, neuton_i8_t required_exp)
{
    neuton_i8_t shift = required_exp - f24_get_exp(x);

    if (shift > 0)
    {
        if (SIGN(x))
            return -(MANTISSA(x) >> shift);
        else
            return MANTISSA(x) >> shift;
    }
    else
    {
        shift = -shift;
        if (SIGN(x))
            return -(MANTISSA(x) << shift);
        else
            return MANTISSA(x) << shift;
    }
}

//////////////////////////////////////////////////////////////////////////////

neuton_f24_t neuton_f24_mul(neuton_f24_t x, neuton_f24_t y)
{
    const neuton_u32_t mul_res = MANTISSA(x) * MANTISSA(y);

    neuton_u8_t shift = 8 + HIGH_BIT_HELPER[mul_res >> 24];
    if (shift == 8)
        shift = HIGH_BIT_HELPER[mul_res >> 16];

    return f24_init(mul_res >> shift, (f24_get_exp(x) + f24_get_exp(y) + shift), SIGN_OF(x, y));
}

//////////////////////////////////////////////////////////////////////////////

neuton_f24_t neuton_f24_div(neuton_f24_t x, neuton_f24_t y)
{
    neuton_i8_t x_shift = 7 - HIGH_BIT_HELPER[MANTISSA(x) >> 8];
    neuton_i8_t y_shift = 8 + HIGH_BIT_HELPER[MANTISSA(y) >> 8];

    if (y_shift == 8)
        y_shift = HIGH_BIT_HELPER[MANTISSA(y)];

    x_shift += y_shift;

    /** Shift the mantissa X to maintain the accuracy of the division */
    neuton_u16_t mantissa = (MANTISSA(x) << x_shift) / MANTISSA(y);

    return f24_init(mantissa, f24_get_exp(x) - f24_get_exp(y) - x_shift, SIGN_OF(x, y));
}

//////////////////////////////////////////////////////////////////////////////

neuton_f24_t neuton_f24_add(neuton_f24_t x, neuton_f24_t y)
{
    /** To perform f24 addition we should align X and Y */

    /** Align X */
    neuton_i8_t shift = 8 - HIGH_BIT_HELPER[MANTISSA(x) >> 8];
    if (shift == 8)
        shift = 16 - HIGH_BIT_HELPER[MANTISSA(x)];
    
    MANTISSA(x) = MANTISSA(x) << shift;
    neuton_i8_t x_exp = f24_get_exp(x) - shift;

    /** Align Y*/
    shift = 8 - HIGH_BIT_HELPER[MANTISSA(y) >> 8];
    if (shift == 8)
        shift = 16 - HIGH_BIT_HELPER[MANTISSA(y)];

    MANTISSA(y) = MANTISSA(y) << shift;
    neuton_i8_t y_exp = f24_get_exp(y) - shift;

    return f24_addx(MANTISSA(x), x_exp, SIGN(x), MANTISSA(y), y_exp, SIGN(y));
}

//////////////////////////////////////////////////////////////////////////////

neuton_f24_t neuton_f24_addx(neuton_u16_t x_man, neuton_i8_t x_exp, neuton_u8_t x_sign,
                            neuton_u16_t y_man, neuton_i8_t y_exp, neuton_u8_t y_sign)
{
    neuton_i8_t shift = x_exp - y_exp;
    neuton_i32_t add_res;

    if (x_sign == y_sign)
    {
        if (shift > 0)
        {
            /** Result of addition will overflow */
            if (shift > 15)
                return f24_init(x_man, x_exp, x_sign);
            
            add_res = (y_man >> shift) + x_man;
            /** Checks if result fits in 4 bytes of mantissa */
            if (!(add_res & 0xFFFF0000))
                return f24_init((neuton_u16_t)add_res, x_exp, x_sign);
            else
                return f24_init((neuton_u16_t)(add_res >> 1), x_exp + 1, x_sign);
        }
        else
        {
            /** Result of addition will overflow */
            if (shift < -15)
                return f24_init(y_man, y_exp, y_sign);

            shift = -shift;
            add_res = (x_man >> shift) + y_man;
            /** Checks if result fits in 4 bytes of mantissa */
            if (!(add_res & 0xFFFF0000))
                return f24_init((neuton_u16_t)add_res, y_exp, x_sign);
            else
                return f24_init((neuton_u16_t)(add_res >> 1), y_exp + 1, x_sign);
        }
    }
    else
    {
        if (shift >= 0)
        {
            /** Result of addition will overflow */
            if (shift > 15)
                return f24_init(x_man, x_exp, x_sign);

            add_res = x_man - (y_man >> shift);

            if (add_res > 0)
                return f24_init((neuton_u16_t)add_res, x_exp, x_sign);
            else if (add_res < 0)
                return f24_init((neuton_u16_t)(-add_res), x_exp, y_sign);
            else
                return f24_init((neuton_u16_t)add_res, x_exp, NEUTON_F24_UNSIGNED);
        }
        else
        {
            /** Result of addition will overflow */
            if (shift < -15)
                return f24_init(y_man, y_exp, y_sign);

            add_res = (x_man >> (-shift)) - y_man;

            if (add_res > 0)
                return f24_init((neuton_u16_t)add_res, y_exp, x_sign);
            else if (add_res < 0)
                return f24_init((neuton_u16_t)(-add_res), y_exp, y_sign);
            else
                return f24_init((neuton_u16_t)add_res, y_exp, NEUTON_F24_UNSIGNED);
        }
    }
}

//////////////////////////////////////////////////////////////////////////////

neuton_f24_t neuton_f24_sqrt(neuton_f24_t x)
{
    neuton_i8_t exp = f24_get_exp(x);
    neuton_u8_t shift = (exp % 2) ? 15 : 16;

    neuton_u32_t arg = MANTISSA(x) << shift;

    if (arg == 0)
        return f24_init(0, 0, 0);

    shift >>= 1;

    exp = (exp >> 1) - shift;

    neuton_u32_t div;
    neuton_u32_t result = arg;

    if (arg & 0xFFFF0000L)
        if (arg & 0xFF000000L) div = 0x3FFF;
        else div = 0x3FF;
    else
        if (arg & 0x0FF00L) div = 0x3F;
        else div = (arg > 4) ? 0x7 : arg;

    while (1)
    {
        const neuton_u32_t temp = arg / div + div;
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
            return f24_init((neuton_u16_t)result, exp, NEUTON_F24_UNSIGNED);
        }
    }
}

//////////////////////////////////////////////////////////////////////////////

const neuton_u8_t* neuton_f24_get_highbit_helper(void)
{
    return &HIGH_BIT_HELPER[0]; 
}