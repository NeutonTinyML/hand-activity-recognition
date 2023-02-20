#include "../../../../../neuton/include/neuton/dsp/neuton_dsp_statistic.h"
#include "../../../../../neuton/include/neuton/dsp/neuton_dsp_fast_math.h"
#include "../../../../../neuton/include/neuton/private/common/neuton_mem.h"

// ///////////////////////////////////////////////////////////////////////////

neuton_f32_t neuton_dsp_stddev_f32(const neuton_f32_t* p_input, neuton_u16_t num,
                                    neuton_dsp_stat_ctx_f32_t* p_ctx)
{
    neuton_f32_t var;

    if (p_ctx && p_ctx->flags.is.var)
        var = p_ctx->value.var;
    else
        var = neuton_dsp_var_f32(p_input, num, p_ctx);

    return neuton_dsp_sqrt_f32(var);
}

// ///////////////////////////////////////////////////////////////////////////

neuton_f32_t neuton_dsp_stddev_f32_s(const neuton_f32_t* p_input, neuton_u16_t num,
                                    size_t stride, neuton_dsp_stat_ctx_f32_t* p_ctx)
{
    neuton_f32_t var;

    if (p_ctx && p_ctx->flags.is.var)
        var = p_ctx->value.var;
    else
        var = neuton_dsp_var_f32_s(p_input, num, stride, p_ctx);

    return neuton_dsp_sqrt_f32(var);
}