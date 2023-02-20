#include "../../../../../neuton/include/neuton/dsp/neuton_dsp_statistic.h"
#include "../../../../../neuton/include/neuton/dsp/neuton_dsp_fast_math.h"
#include "../../../../../neuton/include/neuton/private/common/neuton_mem.h"

// ///////////////////////////////////////////////////////////////////////////

neuton_i32_t neuton_dsp_rms_i32(const neuton_i32_t* p_input, neuton_u16_t num,
                                neuton_dsp_stat_ctx_i32_t* p_ctx)
{
    neuton_u64_t tss;

    if (p_ctx && p_ctx->flags.is.tss)
        tss = p_ctx->value.tss;
    else
        tss = neuton_dsp_tss_i32(p_input, num, p_ctx);

    return (neuton_i32_t)neuton_dsp_sqrt_u32((neuton_u32_t)(tss / num));
}

// ///////////////////////////////////////////////////////////////////////////

neuton_i32_t neuton_dsp_rms_i32_s(const neuton_i32_t* p_input, neuton_u16_t num, 
                                size_t stride, neuton_dsp_stat_ctx_i32_t* p_ctx)
{
    neuton_u64_t tss;

    if (p_ctx && p_ctx->flags.is.tss)
        tss = p_ctx->value.tss;
    else
        tss = neuton_dsp_tss_i32_s(p_input, num, stride, p_ctx);

    return (neuton_i32_t)neuton_dsp_sqrt_u32((neuton_u32_t)(tss / num));
}
