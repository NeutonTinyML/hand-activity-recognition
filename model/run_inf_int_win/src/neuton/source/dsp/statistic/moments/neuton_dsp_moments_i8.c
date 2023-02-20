#include "../../../../../neuton/include/neuton/dsp/neuton_dsp_statistic.h"
#include "../../../../../neuton/include/neuton/dsp/neuton_dsp_fast_math.h"
#include "../../../../../neuton/include/neuton/dsp/support/neuton_f24.h"
#include "../../../../../neuton/include/neuton/private/common/neuton_mem.h"

// ///////////////////////////////////////////////////////////////////////////

#ifndef SKEW_I8_REQUIRED_EXP
#define SKEW_I8_REQUIRED_EXP        (-12)
#endif

#ifndef KURTOSIS_I8_REQUIRED_EXP
#define KURTOSIS_I8_REQUIRED_EXP    (-12)
#endif

// ///////////////////////////////////////////////////////////////////////////

static void skew_and_kur_i8_(const neuton_i8_t* p_input, neuton_u16_t num,
                        neuton_dsp_moments_i8_t* p_m, const neuton_i8_t mean, 
                        const neuton_i16_t var)
{
    NEUTON_DSP_RETURN_IF(var == 0, NEUTON_VOID_VALUE);

    neuton_u8_t sign;
    neuton_i8_t shift;
    neuton_i8_t result_exp;
    neuton_i8_t hbit_mult;
    neuton_i16_t diff;
    neuton_u16_t loop_cnt;
    neuton_u32_t pow_diff;

    neuton_f24_t m2 = f24_init(var, 0, 0);
    neuton_f24_t m3 = f24_init(0, 0, 0);
    neuton_f24_t m4 = f24_init(0, 0, 0);
    neuton_f24_t n_inputs = f24_init(num, 0, 0);
    const neuton_u8_t* HIGH_BIT_HELPER = neuton_f24_get_highbit_helper();

    loop_cnt = num;

    while (loop_cnt > 0U)
    {
        diff = *p_input++ - mean;

        sign = ((diff >> 9) & NEUTON_F24_SIGNED);
        diff = abs(diff);
        shift = HIGH_BIT_HELPER[diff];
        hbit_mult = 16 - shift;
        pow_diff = diff << hbit_mult;
        result_exp = -hbit_mult;

        pow_diff *= diff;
        pow_diff >>= shift;

        pow_diff *= diff;
        pow_diff >>= shift;
        result_exp += (2 * shift);

        m3 = f24_addx(pow_diff, result_exp, sign, m3.man, f24_get_exp(m3), NEUTON_F24_SIGN(m3));

        pow_diff *= diff;
        pow_diff >>= shift;
        result_exp += shift;

        m4 = f24_addx(pow_diff, result_exp, 0, m4.man, f24_get_exp(m4), NEUTON_F24_SIGN(m4));

        loop_cnt--;
    }

    m3 = f24_div(m3, n_inputs);
    m4 = f24_div(m4, n_inputs);

    /** Calculate STD */
    neuton_f24_t std = f24_init(neuton_dsp_sqrt_u32(var), 0, 0);
    /** Calculate Skewness */
    m3 = f24_div(m3, f24_mul(m2, std));
    /** Calculate Kurtosis */
    m4 = f24_div(m4, f24_mul(m2, m2));

    p_m->moment.skew = (neuton_i16_t)f24_to_i32(m3, SKEW_I8_REQUIRED_EXP);
    p_m->moment.kur = (neuton_i16_t)f24_to_i32(m4, KURTOSIS_I8_REQUIRED_EXP);
    p_m->moment.var = var;
}

// ///////////////////////////////////////////////////////////////////////////

void neuton_dsp_moments_i8(const neuton_i8_t* p_input, neuton_u16_t num,
                            neuton_dsp_stat_ctx_i8_t* p_ctx, neuton_dsp_moments_i8_t* p_m)
{
    neuton_u8_t f;
    neuton_i8_t mean;
    neuton_i16_t var;

    f = (p_ctx == NULL) ? NEUTON_DSP_STAT_CTX_EMPTY : (p_ctx->flags.all & NEUTON_DSP_STAT_CTX_SUM_VAR_FLAGS);

    switch (f)
    {
    case NEUTON_DSP_STAT_CTX_EMPTY:
    {
        neuton_dsp_stat_ctx_i8_t ctx;
        NEUTON_DSP_STAT_CTX_RESET(ctx);
        var = neuton_dsp_var_i8(p_input, num, &ctx);
        mean = ctx.value.sum / num;
        skew_and_kur_i8_(p_input, num, p_m, mean, var);
    }
        break;
    case NEUTON_DSP_STAT_CTX_SUM_VAR_FLAGS:
        mean = p_ctx->value.sum / num;
        var =  p_ctx->value.var;
        skew_and_kur_i8_(p_input, num, p_m, mean, var);
        break;
    case NEUTON_DSP_STAT_CTX_SUM_FLAG:
        mean = p_ctx->value.sum / num;
        var = neuton_dsp_var_i8(p_input, num, p_ctx);
        skew_and_kur_i8_(p_input, num, p_m, mean, var);
        break;
    case NEUTON_DSP_STAT_CTX_VAR_FLAG:
        mean = neuton_dsp_sum_i8(p_input, num, p_ctx) / num;
        var =  p_ctx->value.var;
        skew_and_kur_i8_(p_input, num, p_m, mean, var);
        break;
    default: // should never get here
        break;
    }
}