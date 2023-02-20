#include "../../../../../neuton/include/neuton/dsp/transform/neuton_dsp_rfht.h"
#include "../../../../../neuton/include/neuton/neuton_platform.h"

// ///////////////////////////////////////////////////////////////////////////

typedef neuton_i16_t fft_fixed_t;
typedef neuton_i32_t fft_fixed2_t;
typedef neuton_u16_t fft_count_t;

#define FIXED_MULT(x, y) (((fft_fixed2_t)(x) * (y)) >> NEUTON_FRACT_BITS_15)
#define FIXED_DIV(x, y) (((fft_fixed2_t)(x) << NEUTON_FRACT_BITS_15) / (y))
#define GET_OVERFLOW_MARKER(x) (x > NEUTON_INT16_MAX || x < NEUTON_INT16_MIN)

// ///////////////////////////////////////////////////////////////////////////

neuton_u16_t neuton_dsp_rfht_i16(const neuton_dsp_rfht_instance_t* p_inst)
{
    neuton_i16_t* p_data = (neuton_i16_t *)p_inst->p_window;
    const neuton_i16_t* p_sin_table = (const neuton_i16_t*)p_inst->p_sin_table;
    const neuton_i16_t* p_tg_table = (const neuton_i16_t*)p_inst->p_tg_table;
    const neuton_u16_t* p_rev_bit_index = (const neuton_u16_t*)p_inst->p_rev_bit_index;
    const neuton_u16_t log_n = p_inst->log_n;
    const neuton_u16_t window_size = p_inst->window_size;

    for (fft_count_t i = 0; i < window_size; ++i)
    {
        if (i < p_rev_bit_index[i])
        {
            fft_fixed_t tmp_value = p_data[i];
            p_data[i] = p_data[p_rev_bit_index[i]];
            p_data[p_rev_bit_index[i]] = tmp_value;
        }
    }

    neuton_u16_t ex = 0;

    for (uint8_t iteration = 1; iteration <= log_n; ++iteration)
    {
        fft_count_t b_size = (fft_count_t)1U << iteration;
        fft_count_t b_amount = window_size >> iteration;
        fft_fixed2_t inc = 0;

        if (b_size > 4)
        {
            for (fft_count_t b_start = 0; b_start < window_size; b_start += b_size)
            {
                fft_count_t pos1 = b_start + (b_size >> 1) + 1;
                fft_count_t pos2 = b_start + b_size - 1;
                for (fft_count_t index = b_amount; pos1 != pos2; ++pos1, --pos2, index += b_amount)
                {
                    fft_fixed2_t pos1_value = p_data[pos1];
                    fft_fixed2_t pos2_value = p_data[pos2];
                    fft_fixed2_t sin_value = p_sin_table[index];
                    fft_fixed2_t tg_value = p_tg_table[index];

                    fft_fixed2_t tmp_value = pos2_value - FIXED_MULT(pos1_value, tg_value);
                    pos1_value = pos1_value + FIXED_MULT(tmp_value, sin_value);
                    pos2_value = FIXED_MULT(pos1_value, tg_value) - tmp_value;

                    if (inc == 0 && (GET_OVERFLOW_MARKER(pos1_value) || GET_OVERFLOW_MARKER(pos2_value)))
                    {
                        inc = 1;
                        ++ex;
                        fft_count_t pos1r = b_start + (b_size >> 1) + 1;
                        fft_count_t pos2r = b_start + b_size - 1;
                        for (; pos1r < pos1; ++pos1r, --pos2r)
                        {
                            p_data[pos1r] >>= inc;
                            p_data[pos2r] >>= inc;
                        }
                    }

                    p_data[pos1] = (fft_fixed_t)(pos1_value >> inc);
                    p_data[pos2] = (fft_fixed_t)(pos2_value >> inc);
                }

                if (inc == 1)
                {
                    fft_count_t pos1r = b_start + (b_size >> 1) + 1;
                    fft_count_t pos2r = b_start + b_size - 1;
                    p_data[(pos1r + pos2r) / 2] >>= inc;
                    for (pos1r = b_start; pos1r < b_start + (b_size >> 1) + 1; ++pos1r)
                    {
                        p_data[pos1r] >>= inc;
                    }
                }
            }
            inc = 0;
        }

        for (fft_count_t b_start = 0; b_start < window_size; b_start += b_size)
        {
            fft_count_t pos1 = b_start;
            fft_count_t pos2 = b_start + (b_size >> 1);
            for (; pos2 < b_start + b_size; ++pos1, ++pos2)
            {
                fft_fixed2_t pos1_value = p_data[pos1];
                fft_fixed2_t pos2_value = p_data[pos2];

                fft_fixed2_t tmp_value = pos1_value;
                pos1_value = tmp_value + pos2_value;
                pos2_value = tmp_value - pos2_value;

                if (inc == 0 && (GET_OVERFLOW_MARKER(pos1_value) || GET_OVERFLOW_MARKER(pos2_value)))
                {
                    inc = 1;
                    ++ex;
                    fft_count_t pos1r = b_start;
                    fft_count_t pos2r = b_start + (b_size >> 1);
                    for (; pos1r < pos1; ++pos1r, ++pos2r)
                    {
                        p_data[pos1r] >>= inc;
                        p_data[pos2r] >>= inc;
                    }
                    for (pos1r = 0; pos1r < b_start; ++pos1r)
                    {
                        p_data[pos1r] >>= inc;
                    }
                }

                p_data[pos1] = (fft_fixed_t)(pos1_value >> inc);
                p_data[pos2] = (fft_fixed_t)(pos2_value >> inc);
            }
        }
    }

    p_data[0] = FIXED_MULT(p_data[0], p_data[0]);
    fft_fixed2_t inc = 0;
    if (p_data[0] & ((fft_fixed_t)1U << (NEUTON_FRACT_BITS_15 - 1)))
    {
        inc = 1;
        ++ex;
    }
    else
    {
        p_data[0] <<= 1;
    }

    for (fft_count_t i = 1, ri = window_size - 1; i < (window_size >> 1); ++i, --ri)
    {
        fft_fixed2_t power_value = FIXED_MULT(p_data[i], p_data[i]) + FIXED_MULT(p_data[ri], p_data[ri]);
        if (inc == 0 && GET_OVERFLOW_MARKER(power_value))
        {
            inc = 1;
            ++ex;
            for (fft_count_t j = 0; j < i; ++j)
                p_data[j] >>= 1;
        }
        p_data[i] = (fft_fixed_t)(power_value >> inc);
    }
    ex = NEUTON_FRACT_BITS_15 - ex;
    return ex;
}