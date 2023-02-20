#include "../../../../../neuton/include/neuton/dsp/transform/neuton_dsp_rfht.h"

// ///////////////////////////////////////////////////////////////////////////

void neuton_dsp_rfht_f32(const neuton_dsp_rfht_instance_t* p_inst)
{
    neuton_f32_t* p_data                 = (neuton_f32_t*)p_inst->p_window;
    const neuton_f32_t* p_sin_table     = (const neuton_f32_t*)p_inst->p_sin_table;
    const neuton_f32_t* p_tg_table      = (const neuton_f32_t*)p_inst->p_tg_table;
    const neuton_u16_t* p_rev_bit_index = (const neuton_u16_t*)p_inst->p_rev_bit_index;
    const neuton_u16_t log_n = p_inst->log_n;
    const neuton_u16_t window_size = p_inst->window_size;
    
    for (neuton_u16_t i = 0; i < window_size; ++i)
    {
        if (i < p_rev_bit_index[i])
        {
            neuton_f32_t tmp_value = p_data[i];
            p_data[i] = p_data[p_rev_bit_index[i]];
            p_data[p_rev_bit_index[i]] = tmp_value;
        }
    }

    for (neuton_u16_t iteration = 1; iteration <= log_n; ++iteration)
    {
        neuton_u16_t b_size = (neuton_u16_t)1U << iteration;
        neuton_u16_t b_amount = window_size >> iteration;
        if (b_size > 4)
        {
            for (neuton_u16_t b_start = 0; b_start < window_size; b_start += b_size)
            {
                neuton_u16_t pos1 = b_start + (b_size >> 1) + 1;
                neuton_u16_t pos2 = b_start + b_size - 1;
                for (neuton_u16_t index = b_amount; pos1 != pos2; ++pos1, --pos2, index += b_amount)
                {
                    float tmp_value = p_data[pos2] - p_data[pos1] * p_tg_table[index];
                    p_data[pos1] = p_data[pos1] + tmp_value * p_sin_table[index];
                    p_data[pos2] = p_data[pos1] * p_tg_table[index] - tmp_value;
                }
            }
        }

        for (neuton_u16_t b_start = 0; b_start < window_size; b_start += b_size)
        {
            neuton_u16_t pos1 = b_start;
            neuton_u16_t pos2 = b_start + (b_size >> 1);
            for (; pos2 < b_start + b_size; ++pos1, ++pos2)
            {
                float tmp_value = p_data[pos1];
                p_data[pos1] = tmp_value + p_data[pos2];
                p_data[pos2] = tmp_value - p_data[pos2];
            }
        }
    }

    p_data[0] = p_data[0] * p_data[0];
    for (neuton_u16_t i = 1; i < (window_size >> 1); ++i)
    {
        p_data[i] = (p_data[i] * p_data[i] + p_data[window_size - i] * p_data[window_size - i]) / 2;
    }
}