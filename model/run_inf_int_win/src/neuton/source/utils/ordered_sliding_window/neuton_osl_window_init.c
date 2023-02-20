#include "../../../../neuton/include/neuton/utils/neuton_osl_window.h"
#include "../../../../neuton/include/neuton/neuton_platform.h"

// ///////////////////////////////////////////////////////////////////////////

neuton_i8_t neuton_osl_window_init(neuton_osl_window_ctx_t* p_ctx, 
                                    void* p_window, const neuton_u16_t max_samples_num, 
                                    const size_t uniq_features_num,
                                    const neuton_u16_t window_shift)
{
    if (p_ctx == NULL)
        return -1;

    p_ctx->is_shift_pending = false;
    p_ctx->window_shift = window_shift;

   return neuton_ordered_window_init(&p_ctx->ord_win, p_window, 
                                    max_samples_num, uniq_features_num);
}
