#ifdef NEUTON_DSP_SUPPORT_FAST_BUILD

#include "../quantization/neuton_dsp_quantization.c"

#include "../scaling/min_max/neuton_dsp_scale_minmax_f32.c"
#include "../scaling/min_max/neuton_dsp_scale_minmax_i8.c"
#include "../scaling/min_max/neuton_dsp_scale_minmax_i16.c"

#include "../scaling/z_score/neuton_dsp_scale_zscore_f32.c"
#include "../scaling/z_score/neuton_dsp_scale_zscore_i8.c"
#include "../scaling/z_score/neuton_dsp_scale_zscore_i16.c"

#include "../softfloat/neuton_f24.c"

#include "../windowing/neuton_dsp_windowing.c"

#else

/** ISO C forbids an empty translation unit [-Wpedantic] */
#if defined ( __GNUC__ )
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"
#pragma GCC diagnostic pop
#endif

#endif
