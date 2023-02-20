#include "../../../../../neuton/include/neuton/dsp/neuton_dsp_statistic.h"
#include "../../../../../neuton/include/neuton/private/common/neuton_mem.h"

// ///////////////////////////////////////////////////////////////////////////

neuton_i16_t neuton_dsp_mcr_i32(const neuton_i32_t* p_input, neuton_u16_t num,
                                neuton_dsp_stat_ctx_i32_t* p_ctx)
{
    neuton_i32_t mean;

    if (p_ctx && p_ctx->flags.is.sum)
        mean = p_ctx->value.sum / num;
    else
        mean = neuton_dsp_sum_i32(p_input, num, p_ctx) / num;

    return neuton_dsp_tcr_i32(p_input, num, mean);
}

// ///////////////////////////////////////////////////////////////////////////

neuton_i16_t neuton_dsp_mcr_i32_s(const neuton_i32_t* p_input, neuton_u16_t num, 
                                    size_t stride, neuton_dsp_stat_ctx_i32_t* p_ctx)
{
    neuton_i32_t mean;

    if (p_ctx && p_ctx->flags.is.sum)
        mean = p_ctx->value.sum / num;
    else
        mean = neuton_dsp_sum_i32_s(p_input, num, stride, p_ctx) / num;

    return neuton_dsp_tcr_i32_s(p_input, num, stride, mean);
}
