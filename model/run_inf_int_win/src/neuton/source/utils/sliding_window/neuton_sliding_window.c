#include "../../../../neuton/include/neuton/utils/neuton_sliding_window.h"
#include <string.h>

// ///////////////////////////////////////////////////////////////////////////

neuton_status_t neuton_sliding_window_init(neuton_sliding_window_ctx_t* p_ctx, void* p_window,
                                            neuton_u16_t window_size, neuton_u16_t sample_size,
                                            neuton_u16_t window_hop, neuton_sliding_window_cb_t cb,
                                            void* p_user_ctx)
{
    if ((p_ctx == NULL) || (p_window == NULL))
        return NEUTON_STATUS_NULL_ARGUMENT;

    if (window_hop > window_size)
        return NEUTON_STATUS_INVALID_ARGUMENT;

    p_ctx->p_window     = p_window;
    p_ctx->sample_size  = sample_size;
    p_ctx->window_size  = window_size;
    p_ctx->window_hop   = window_hop;
    p_ctx->p_user_ctx   = p_user_ctx;
    p_ctx->on_ready_cb  = cb;
    p_ctx->current_fill = 0;

    return NEUTON_STATUS_SUCCESS;
}

// ///////////////////////////////////////////////////////////////////////////

void neuton_sliding_window_feed(neuton_sliding_window_ctx_t* p_ctx, void* p_samples, 
                                neuton_u16_t samples_num)
{
    if (p_samples == NULL || samples_num == 0)
        return;
    
    const neuton_u32_t tail_size = p_ctx->window_size - p_ctx->window_hop;
    neuton_u8_t* p_from = (neuton_u8_t*)p_samples;
    neuton_u8_t* p_to = (neuton_u8_t*)p_ctx->p_window;
    neuton_u32_t offset = 0;

    while (samples_num)
    {
        neuton_u32_t n_copied = p_ctx->window_size - p_ctx->current_fill;
        if (n_copied > samples_num)
            n_copied = samples_num;

        memcpy(&p_to[p_ctx->current_fill * p_ctx->sample_size],
                &p_from[offset * p_ctx->sample_size],
                n_copied * p_ctx->sample_size);

        p_ctx->current_fill += n_copied;

        if (p_ctx->current_fill >= p_ctx->window_size)
        {
            if (p_ctx->on_ready_cb)
                p_ctx->on_ready_cb(p_ctx->p_window, p_ctx->window_size, p_ctx->p_user_ctx);

            if (tail_size)
                memmove(p_to, &p_to[p_ctx->window_hop * p_ctx->sample_size], tail_size * p_ctx->sample_size);

            p_ctx->current_fill = tail_size;
        }

        offset += n_copied;
        samples_num -= n_copied;
    }
}