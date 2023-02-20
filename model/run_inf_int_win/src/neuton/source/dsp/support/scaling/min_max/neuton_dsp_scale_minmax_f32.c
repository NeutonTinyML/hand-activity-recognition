#include "../../../../../../neuton/include/neuton/dsp/support/neuton_dsp_scale_minmax.h"
#include "../../../../../../neuton/include/neuton/private/common/neuton_common.h"

// ///////////////////////////////////////////////////////////////////////////

void neuton_dsp_scale_minmax_f32(const neuton_f32_t* p_input, neuton_u16_t num,
                                const neuton_f32_t min, const neuton_f32_t max,
                                neuton_f32_t* p_output)
{
    /** Range is not appropriate*/
    if (min >= max)
        return;

    neuton_u16_t loop_cnt;
    const neuton_f32_t range = max - min;

#if (NEUTON_USE_LOOPUNROLL == 1)
    /* Loop unrolling: Compute 4 outputs at a time */
    loop_cnt = num >> 2U;

    while (loop_cnt > 0U)
    {
        *p_output++ = (*p_input++ - min) / range;
        *p_output++ = (*p_input++ - min) / range;
        *p_output++ = (*p_input++ - min) / range;
        *p_output++ = (*p_input++ - min) / range;

        loop_cnt--;
    }

    /* Loop unrolling: Compute remaining outputs */
    loop_cnt = num % 0x4U;
#else

    loop_cnt = num;

#endif /* #if (NEUTON_USE_LOOPUNROLL == 1) */

    while (loop_cnt > 0U)
    {
        *p_output++ = (*p_input++ - min) / range;

        loop_cnt--;
    }
}