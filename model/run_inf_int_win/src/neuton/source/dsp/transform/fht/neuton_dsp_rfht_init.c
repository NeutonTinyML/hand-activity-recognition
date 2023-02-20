#include "../../../../../neuton/include/neuton/dsp/transform/neuton_dsp_rfht.h"

// ///////////////////////////////////////////////////////////////////////////

neuton_status_t neuton_dsp_rfht_init(neuton_dsp_rfht_instance_t* p_inst, 
                                    const void* p_sin_table, 
                                    const void* p_tg_table,
                                    const neuton_u16_t* p_rev_bit_index,
                                    void* p_window,
                                    const neuton_u16_t window_size,
                                    const neuton_u16_t log_n)
{
    if (p_inst == NULL)
        return NEUTON_STATUS_NULL_ARGUMENT;

    p_inst->p_sin_table = p_sin_table;
    p_inst->p_tg_table = p_tg_table;
    p_inst->p_rev_bit_index = p_rev_bit_index;
    p_inst->p_window = p_window;
    p_inst->window_size = window_size;
    p_inst->log_n = log_n;

    return NEUTON_STATUS_SUCCESS;
}