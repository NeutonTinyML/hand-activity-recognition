#include "../../../../../neuton/include/neuton/dsp/neuton_dsp_statistic.h"
#include "../../../../../neuton/include/neuton/private/common/neuton_mem.h"

// ///////////////////////////////////////////////////////////////////////////

neuton_i16_t neuton_dsp_zcr_i32(const neuton_i32_t *p_input, neuton_u16_t num)
{
    neuton_u16_t loop_cnt;
    neuton_i16_t zcr = 0U;

    bool sign_val;
    bool sign_next_val;

#if (NEUTON_USE_LOOPUNROLL == 1)
    /* Loop unrolling: Compute 4 outputs at a time */
    loop_cnt = num >> 2U;

    /* Init with first element sign, to preserve the consistency of loop unroll, 
    despite the extra sign check */
    sign_val = NEUTON_INT32_CHECK_SIGN(*p_input);

    while (loop_cnt > 0U)
    {
        sign_next_val = NEUTON_INT32_CHECK_SIGN(*p_input++);

        if (sign_val != sign_next_val)
            zcr++;

        sign_val = NEUTON_INT32_CHECK_SIGN(*p_input++);

        if (sign_val != sign_next_val)
            zcr++;

        sign_next_val = NEUTON_INT32_CHECK_SIGN(*p_input++);

        if (sign_val != sign_next_val)
            zcr++;

        sign_val = NEUTON_INT32_CHECK_SIGN(*p_input++);

        if (sign_val != sign_next_val)
            zcr++;

        loop_cnt--;
    }

    /* Loop unrolling: Compute remaining outputs */
    loop_cnt = num % 0x4U;

#else

    loop_cnt = num - 1;
    sign_val = NEUTON_INT32_CHECK_SIGN(*p_input++);

#endif /* #if (NEUTON_USE_LOOPUNROLL == 1) */

    while (loop_cnt > 0U)
    {
        sign_next_val = NEUTON_INT32_CHECK_SIGN(*p_input++);

        if (sign_val != sign_next_val)
            zcr++;

        sign_val = sign_next_val;

        loop_cnt--;
    }

    return (neuton_i16_t)(((int32_t)zcr * NEUTON_INT_TO_F32_PRECISION_FACTOR) / (num - 1));
}

// ///////////////////////////////////////////////////////////////////////////

neuton_i16_t neuton_dsp_zcr_i32_s(const neuton_i32_t* p_input, neuton_u16_t num, 
                                size_t stride)
{
    neuton_u16_t loop_cnt;
    neuton_i16_t zcr = 0U;
    neuton_u16_t i = 0U;

    bool sign_val;
    bool sign_next_val;

#if (NEUTON_USE_LOOPUNROLL == 1)
    /* Loop unrolling: Compute 4 outputs at a time */
    loop_cnt = num >> 2U;

    sign_val = NEUTON_INT32_CHECK_SIGN(p_input[i * stride]);

    while (loop_cnt > 0U)
    {
        sign_next_val = NEUTON_INT32_CHECK_SIGN(p_input[i * stride]);

        if (sign_val != sign_next_val)
            zcr++;
        i++;

        sign_val = NEUTON_INT32_CHECK_SIGN(p_input[i * stride]);

        if (sign_val != sign_next_val)
            zcr++;
        i++;

        sign_next_val = NEUTON_INT32_CHECK_SIGN(p_input[i * stride]);

        if (sign_val != sign_next_val)
            zcr++;
        i++;

        sign_val = NEUTON_INT32_CHECK_SIGN(p_input[i * stride]);

        if (sign_val != sign_next_val)
            zcr++;
        i++;

        loop_cnt--;
    }

    /* Loop unrolling: Compute remaining outputs */
    loop_cnt = num % 0x4U;

#else

    loop_cnt = num - 1;
    sign_val = NEUTON_INT32_CHECK_SIGN(p_input[i * stride]);
    i++;

#endif /* #if (NEUTON_USE_LOOPUNROLL == 1) */

    while (loop_cnt > 0U)
    {
        sign_next_val = NEUTON_INT32_CHECK_SIGN(p_input[i * stride]);

        if (sign_val != sign_next_val)
            zcr++;
        i++;

        sign_val = sign_next_val;

        loop_cnt--;
    }

    return (neuton_i16_t)(((int32_t)zcr * NEUTON_INT_TO_F32_PRECISION_FACTOR) / (num - 1));
}