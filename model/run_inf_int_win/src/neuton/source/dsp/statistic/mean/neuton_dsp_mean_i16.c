#include "../../../../../neuton/include/neuton/dsp/neuton_dsp_statistic.h"
#include "../../../../../neuton/include/neuton/private/common/neuton_mem.h"

// ///////////////////////////////////////////////////////////////////////////

neuton_i16_t neuton_dsp_mean_i16(const neuton_i16_t* p_input, neuton_u16_t num,
                                neuton_dsp_stat_ctx_i16_t* p_ctx)
{
    neuton_i32_t sum;

    if (p_ctx && p_ctx->flags.is.sum)
        sum = p_ctx->value.sum;
    else
        sum = neuton_dsp_sum_i16(p_input, num, p_ctx);

    return (neuton_i16_t)(sum / num);   
}

// ///////////////////////////////////////////////////////////////////////////

neuton_i16_t neuton_dsp_mean_i16_s(const neuton_i16_t* p_input, neuton_u16_t num, 
                                    size_t stride, neuton_dsp_stat_ctx_i16_t* p_ctx)
{
    neuton_i32_t sum;

    if (p_ctx && p_ctx->flags.is.sum)
        sum = p_ctx->value.sum;
    else
        sum = neuton_dsp_sum_i16_s(p_input, num, stride, p_ctx);

    return (neuton_i16_t)(sum / num);
}
