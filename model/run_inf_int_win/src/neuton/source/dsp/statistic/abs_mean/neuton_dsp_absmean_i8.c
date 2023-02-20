#include "../../../../../neuton/include/neuton/dsp/neuton_dsp_statistic.h"
#include "../../../../../neuton/include/neuton/private/common/neuton_mem.h"

// ///////////////////////////////////////////////////////////////////////////

neuton_u8_t neuton_dsp_absmean_i8(const neuton_i8_t* p_input, neuton_u16_t num,
                                neuton_dsp_stat_ctx_i8_t* p_ctx)
{
    neuton_u32_t sum;

    if (p_ctx && p_ctx->flags.is.abssum)
        sum = p_ctx->value.abssum;
    else
        sum = neuton_dsp_abssum_i8(p_input, num, p_ctx);

    return (neuton_u8_t)(sum / num);   
}

// ///////////////////////////////////////////////////////////////////////////

neuton_u8_t neuton_dsp_absmean_i8_s(const neuton_i8_t* p_input, neuton_u16_t num, 
                                size_t stride, neuton_dsp_stat_ctx_i8_t* p_ctx)
{
    neuton_u32_t sum;

    if (p_ctx && p_ctx->flags.is.abssum)
        sum = p_ctx->value.abssum;
    else
        sum = neuton_dsp_abssum_i8_s(p_input, num, stride, p_ctx);

    return (neuton_u8_t)(sum / num);
}
