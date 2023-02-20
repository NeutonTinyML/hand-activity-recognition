#include "../../../../../../neuton/include/neuton/dsp/support/neuton_dsp_scale_zscore.h"
#include "../../../../../../neuton/include/neuton/private/common/neuton_common.h"

// ///////////////////////////////////////////////////////////////////////////

void neuton_dsp_scale_zscore_i8(const neuton_i8_t* p_input, neuton_u16_t num,
                                const neuton_i8_t mean, const neuton_i8_t stddev,
                                neuton_i8_t* p_output)
{
    if (stddev == 0)
        return;

    neuton_u16_t loop_cnt;

#if (NEUTON_USE_LOOPUNROLL == 1)
    /* Loop unrolling: Compute 4 outputs at a time */
    loop_cnt = num >> 2U;

    while (loop_cnt > 0U)
    {
        *p_output++ = ((neuton_i16_t)(*p_input++ - mean) * NEUTON_INT8_QFACTOR) / stddev;
        *p_output++ = ((neuton_i16_t)(*p_input++ - mean) * NEUTON_INT8_QFACTOR) / stddev;
        *p_output++ = ((neuton_i16_t)(*p_input++ - mean) * NEUTON_INT8_QFACTOR) / stddev;
        *p_output++ = ((neuton_i16_t)(*p_input++ - mean) * NEUTON_INT8_QFACTOR) / stddev;

        loop_cnt--;
    }    

    /* Loop unrolling: Compute remaining outputs */
    loop_cnt = num % 0x4U;
#else

    loop_cnt = num;

#endif /* #if (NEUTON_USE_LOOPUNROLL == 1) */

    while (loop_cnt > 0U)
    {
        *p_output++ = ((neuton_i16_t)(*p_input++ - mean) * NEUTON_INT8_QFACTOR) / stddev;

        loop_cnt--;
    }
}