#include "../../../../../neuton/include/neuton/dsp/neuton_dsp_support.h"
#include "../../../../../neuton/include/neuton/private/common/neuton_common.h"

// ///////////////////////////////////////////////////////////////////////////

#define INT8_SSAT_BITS          8
#define INT16_SSAT_BITS         16

// ///////////////////////////////////////////////////////////////////////////

void neuton_dsp_quantize_f32_to_i8(const neuton_f32_t* p_input,
                                    neuton_i8_t* p_out,
                                    neuton_u16_t num)
{
    neuton_u16_t loop_cnt;

#if (NEUTON_USE_MATH_ROUNDING == 1)
    neuton_f32_t in;
#endif /* #ifdef NEUTON_USE_MATH_ROUNDING */

#if (NEUTON_USE_LOOPUNROLL == 1)

    /* Loop unrolling: Compute 4 outputs at a time */
    loop_cnt = num >> 2U;

    while (loop_cnt > 0U)
    {
        /* Quantize from float to i8 and store result in destination buffer */
#if (NEUTON_USE_MATH_ROUNDING == 1)

        in = (*p_input++ * NEUTON_INT8_QFACTOR);
        in += in > 0.0f ? 0.5f : -0.5f;
        *p_out++ = (neuton_i8_t) (__NEUTON_SSAT((neuton_i16_t) (in), INT8_SSAT_BITS));

        in = (*p_input++ * NEUTON_INT8_QFACTOR);
        in += in > 0.0f ? 0.5f : -0.5f;
        *p_out++ = (neuton_i8_t) (__NEUTON_SSAT((neuton_i16_t) (in), INT8_SSAT_BITS));

        in = (*p_input++ * NEUTON_INT8_QFACTOR);
        in += in > 0.0f ? 0.5f : -0.5f;
        *p_out++ = (neuton_i8_t) (__NEUTON_SSAT((neuton_i16_t) (in), INT8_SSAT_BITS));

        in = (*p_input++ * NEUTON_INT8_QFACTOR);
        in += in > 0.0f ? 0.5f : -0.5f;
        *p_out++ = (neuton_i8_t) (__NEUTON_SSAT((neuton_i16_t) (in), INT8_SSAT_BITS));

#else

        *p_out++ = __NEUTON_SSAT((neuton_i32_t) (*p_input++ * NEUTON_INT8_QFACTOR), INT8_SSAT_BITS);
        *p_out++ = __NEUTON_SSAT((neuton_i32_t) (*p_input++ * NEUTON_INT8_QFACTOR), INT8_SSAT_BITS);
        *p_out++ = __NEUTON_SSAT((neuton_i32_t) (*p_input++ * NEUTON_INT8_QFACTOR), INT8_SSAT_BITS);
        *p_out++ = __NEUTON_SSAT((neuton_i32_t) (*p_input++ * NEUTON_INT8_QFACTOR), INT8_SSAT_BITS);

#endif /* #ifdef NEUTON_USE_MATH_ROUNDING */

        loop_cnt--;
    }

    /* Loop unrolling: Compute remaining outputs */
    loop_cnt = num % 0x4U;

#else

    /* Initialize loop_cnt with number of samples */
    loop_cnt = num;

#endif /* #if defined (NEUTON_USE_LOOPUNROLL) */

    while (loop_cnt > 0U)
    {
        /* Quantize from float to i8 and store result in destination buffer */
#if (NEUTON_USE_MATH_ROUNDING == 1)

        in = (*p_input++ * NEUTON_INT8_QFACTOR);
        in += in > 0.0f ? 0.5f : -0.5f;
        *p_out++ = (neuton_i8_t) (__NEUTON_SSAT((neuton_i16_t) (in), INT8_SSAT_BITS));

#else

        *p_out++ = (neuton_i8_t) __NEUTON_SSAT((neuton_i32_t) (*p_input++ * NEUTON_INT8_QFACTOR), INT8_SSAT_BITS);

#endif /* #ifdef NEUTON_USE_MATH_ROUNDING */

        loop_cnt--;
    }
}

// ///////////////////////////////////////////////////////////////////////////

void neuton_dsp_quantize_f32_to_i16(const neuton_f32_t* p_input,
                                    neuton_i16_t* p_out,
                                    neuton_u16_t num)
{
    neuton_u16_t loop_cnt;

#if (NEUTON_USE_MATH_ROUNDING == 1)
    neuton_f32_t in;
#endif /* #if (NEUTON_USE_MATH_ROUNDING == 1) */

#if (NEUTON_USE_LOOPUNROLL == 1)

    /* Loop unrolling: Compute 4 outputs at a time */
    loop_cnt = num >> 2U;

    while (loop_cnt > 0U)
    {
        /* Quantize from float to INT16 and store result in destination buffer */
#if (NEUTON_USE_MATH_ROUNDING == 1)

        in = (*p_input++ * NEUTON_INT16_QFACTOR);
        in += in > 0.0f ? 0.5f : -0.5f;
        *p_out++ = (neuton_i16_t) (__NEUTON_SSAT((neuton_i32_t) (in), INT16_SSAT_BITS));

        in = (*p_input++ * NEUTON_INT16_QFACTOR);
        in += in > 0.0f ? 0.5f : -0.5f;
        *p_out++ = (neuton_i16_t) (__NEUTON_SSAT((neuton_i32_t) (in), INT16_SSAT_BITS));

        in = (*p_input++ * NEUTON_INT16_QFACTOR);
        in += in > 0.0f ? 0.5f : -0.5f;
        *p_out++ = (neuton_i16_t) (__NEUTON_SSAT((neuton_i32_t) (in), INT16_SSAT_BITS));

        in = (*p_input++ * NEUTON_INT16_QFACTOR);
        in += in > 0.0f ? 0.5f : -0.5f;
        *p_out++ = (neuton_i16_t) (__NEUTON_SSAT((neuton_i32_t) (in), INT16_SSAT_BITS));

#else

        *p_out++ = (neuton_i16_t) __NEUTON_SSAT((neuton_i32_t) (*p_input++ * NEUTON_INT16_QFACTOR), INT16_SSAT_BITS);
        *p_out++ = (neuton_i16_t) __NEUTON_SSAT((neuton_i32_t) (*p_input++ * NEUTON_INT16_QFACTOR), INT16_SSAT_BITS);
        *p_out++ = (neuton_i16_t) __NEUTON_SSAT((neuton_i32_t) (*p_input++ * NEUTON_INT16_QFACTOR), INT16_SSAT_BITS);
        *p_out++ = (neuton_i16_t) __NEUTON_SSAT((neuton_i32_t) (*p_input++ * NEUTON_INT16_QFACTOR), INT16_SSAT_BITS);

#endif /* #if (NEUTON_USE_MATH_ROUNDING == 1) */

        loop_cnt--;
    }

    /* Loop unrolling: Compute remaining outputs */
    loop_cnt = num % 0x4U;

#else

    /* Initialize loop_cnt with number of samples */
    loop_cnt = num;

#endif /* #if (NEUTON_USE_MATH_ROUNDING == 1)*/

    while (loop_cnt > 0U)
    {
        /* Quantize from float to INT16 and store result in destination buffer */
#if (NEUTON_USE_MATH_ROUNDING == 1)

        in = (*p_input++ * NEUTON_INT16_QFACTOR);
        in += in > 0.0f ? 0.5f : -0.5f;
        *p_out++ = (neuton_i16_t) (__NEUTON_SSAT((neuton_i32_t) (in), INT16_SSAT_BITS));

#else

        /* Quantize from float to i16 and then store the results in the destination buffer */
        *p_out++ = (neuton_i16_t) __NEUTON_SSAT((neuton_i32_t) (*p_input++ * NEUTON_INT16_QFACTOR), INT16_SSAT_BITS);

#endif /* #if (NEUTON_USE_MATH_ROUNDING == 1) */

        loop_cnt--;
    }
}

// ///////////////////////////////////////////////////////////////////////////

void neuton_dsp_quantize_f32_to_i32(const neuton_f32_t* p_input,
                                    neuton_i32_t* p_out,
                                    neuton_u16_t num)
{
    neuton_u16_t loop_cnt;

#if (NEUTON_USE_MATH_ROUNDING == 1)
    neuton_f32_t in;
#endif /* #if (NEUTON_USE_MATH_ROUNDING == 1) */

#if (NEUTON_USE_LOOPUNROLL == 1)

    /* Loop unrolling: Compute 4 outputs at a time */
    loop_cnt = num >> 2U;

    while (loop_cnt > 0U)
    {
        /* Quantize from float to INT32 and then store the results in the destination buffer */
#if (NEUTON_USE_MATH_ROUNDING == 1)

        in = (*p_input++ * NEUTON_INT32_QFACTOR);
        in += in > 0.0f ? 0.5f : -0.5f;
        *p_out++ = clip_i64_to_i32((neuton_i64_t) (in));

        in = (*p_input++ * NEUTON_INT32_QFACTOR);
        in += in > 0.0f ? 0.5f : -0.5f;
        *p_out++ = clip_i64_to_i32((neuton_i64_t) (in));

        in = (*p_input++ * NEUTON_INT32_QFACTOR);
        in += in > 0.0f ? 0.5f : -0.5f;
        *p_out++ = clip_i64_to_i32((neuton_i64_t) (in));

        in = (*p_input++ * NEUTON_INT32_QFACTOR);
        in += in > 0.0f ? 0.5f : -0.5f;
        *p_out++ = clip_i64_to_i32((neuton_i64_t) (in));

#else

        /* Quantize from float to INT32 and then store the results in the destination buffer */
        *p_out++ = clip_i64_to_i32((neuton_i64_t) (*p_input++ * NEUTON_INT32_QFACTOR));
        *p_out++ = clip_i64_to_i32((neuton_i64_t) (*p_input++ * NEUTON_INT32_QFACTOR));
        *p_out++ = clip_i64_to_i32((neuton_i64_t) (*p_input++ * NEUTON_INT32_QFACTOR));
        *p_out++ = clip_i64_to_i32((neuton_i64_t) (*p_input++ * NEUTON_INT32_QFACTOR));

#endif /* #if (NEUTON_USE_MATH_ROUNDING == 1) */

        loop_cnt--;
    }

    /* Loop unrolling: Compute remaining outputs */
    loop_cnt = num % 0x4U;

#else

    /* Initialize loop_cnt with number of samples */
    loop_cnt = num;

#endif /* #if (NEUTON_USE_LOOPUNROLL == 1) */

    while (loop_cnt > 0U)
    {
        /* convert from float to INT32 and store result in destination buffer */
#if (NEUTON_USE_MATH_ROUNDING == 1)

        in = (*p_input++ * NEUTON_INT32_QFACTOR);
        in += in > 0.0f ? 0.5f : -0.5f;
        *p_out++ = clip_i64_to_i32((neuton_i64_t) (in));

#else

        /* Quantize from float to INT32 and then store the results in the destination buffer */
        *p_out++ = clip_i64_to_i32((neuton_i64_t) (*p_input++ * NEUTON_INT32_QFACTOR));

#endif /* #if (NEUTON_USE_MATH_ROUNDING == 1) */

        loop_cnt--;
    }
}