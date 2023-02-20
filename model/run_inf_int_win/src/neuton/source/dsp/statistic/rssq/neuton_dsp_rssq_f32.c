#include "../../../../../neuton/include/neuton/dsp/neuton_dsp_statistic.h"
#include "../../../../../neuton/include/neuton/dsp/neuton_dsp_fast_math.h"
#include "../../../../../neuton/include/neuton/private/common/neuton_mem.h"

// ///////////////////////////////////////////////////////////////////////////

neuton_f32_t neuton_dsp_rssq_f32(const neuton_f32_t* p_input, neuton_u16_t num,
                                neuton_dsp_stat_ctx_f32_t* p_ctx)
{
    neuton_f32_t tss;

    if (p_ctx && p_ctx->flags.is.tss)
        tss = p_ctx->value.tss;
    else
        tss = neuton_dsp_tss_f32(p_input, num, p_ctx);

    return neuton_dsp_sqrt_f32(tss);
}

// ///////////////////////////////////////////////////////////////////////////

neuton_f32_t neuton_dsp_rssq_f32_s(const neuton_f32_t* p_input, neuton_u16_t num, 
                                size_t stride, neuton_dsp_stat_ctx_f32_t* p_ctx)
{
    neuton_f32_t tss;

    if (p_ctx && p_ctx->flags.is.tss)
        tss = p_ctx->value.tss;
    else
        tss = neuton_dsp_tss_f32_s(p_input, num, stride, p_ctx);

    return neuton_dsp_sqrt_f32(tss);
}
