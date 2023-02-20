#include "../../../../neuton/include/neuton/utils/neuton_ordered_window.h"

// ///////////////////////////////////////////////////////////////////////////

neuton_i8_t neuton_ordered_window_init(neuton_ordered_window_ctx_t* p_ctx, 
                                        void* p_window, const neuton_u16_t max_samples_num, 
                                        const size_t uniq_features_num)
{
    if ((p_ctx == NULL) || (p_window == NULL) || (max_samples_num < 2) || (uniq_features_num == 0))
        return -1;

    p_ctx->p_window.generic        = p_window;
    p_ctx->max_samples_num         = max_samples_num;
    p_ctx->current_sample          = 0;
    p_ctx->uniq_features_num       = uniq_features_num;
    p_ctx->uniq_features_collected = uniq_features_num;

    return 0;
}
