#include "../../../../../neuton/include/neuton/dsp/neuton_dsp_statistic.h"
#include "../../../../../neuton/include/neuton/dsp/neuton_dsp_fast_math.h"
#include "../../../../../neuton/include/neuton/private/common/neuton_mem.h"

// ///////////////////////////////////////////////////////////////////////////

neuton_i16_t neuton_dsp_stddev_i8(const neuton_i8_t* p_input, neuton_u16_t num,
                                    neuton_dsp_stat_ctx_i8_t* p_ctx)
{
    neuton_i16_t var;

    if (p_ctx && p_ctx->flags.is.var)
        var = p_ctx->value.var;
    else
        var = neuton_dsp_var_i8(p_input, num, p_ctx);

    return (neuton_i16_t)neuton_dsp_sqrt_u32((neuton_u32_t)var);    
}

// ///////////////////////////////////////////////////////////////////////////

neuton_i16_t neuton_dsp_stddev_i8_s(const neuton_i8_t* p_input, neuton_u16_t num,
                                    size_t stride, neuton_dsp_stat_ctx_i8_t* p_ctx)
{
    neuton_i16_t var;

    if (p_ctx && p_ctx->flags.is.var)
        var = p_ctx->value.var;
    else
        var = neuton_dsp_var_i8_s(p_input, num, stride, p_ctx);

    return (neuton_i16_t)neuton_dsp_sqrt_u32((neuton_u32_t)var);     
}