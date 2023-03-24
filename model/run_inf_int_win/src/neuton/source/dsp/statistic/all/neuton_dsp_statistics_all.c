#ifdef NEUTON_DSP_STATISTICS_FAST_BUILD

#include "../abs_max/neuton_dsp_absmax_f32.c"
#include "../abs_max/neuton_dsp_absmax_i8.c"
#include "../abs_max/neuton_dsp_absmax_i16.c"
#include "../abs_max/neuton_dsp_absmax_i32.c"

#include "../abs_mean/neuton_dsp_absmean_f32.c"
#include "../abs_mean/neuton_dsp_absmean_i8.c"
#include "../abs_mean/neuton_dsp_absmean_i16.c"

#include "../abs_min/neuton_dsp_absmin_f32.c"
#include "../abs_min/neuton_dsp_absmin_i8.c"
#include "../abs_min/neuton_dsp_absmin_i16.c"
#include "../abs_min/neuton_dsp_absmin_i32.c"

#include "../abs_sum/neuton_dsp_abssum_f32.c"
#include "../abs_sum/neuton_dsp_abssum_i8.c"
#include "../abs_sum/neuton_dsp_abssum_i16.c"
#include "../abs_sum/neuton_dsp_abssum_i32.c"

#include "../kurtosis/neuton_dsp_kur_f32.c"
#include "../kurtosis/neuton_dsp_kur_i8.c"
#include "../kurtosis/neuton_dsp_kur_i16.c"

#include "../max/neuton_dsp_max_f32.c"
#include "../max/neuton_dsp_max_i8.c"
#include "../max/neuton_dsp_max_i16.c"
#include "../max/neuton_dsp_max_i32.c"

#include "../mean/neuton_dsp_mean_f32.c"
#include "../mean/neuton_dsp_mean_i8.c"
#include "../mean/neuton_dsp_mean_i16.c"
#include "../mean/neuton_dsp_mean_i32.c"

#include "../mean_absdev/neuton_dsp_mad_f32.c"
#include "../mean_absdev/neuton_dsp_mad_i8.c"
#include "../mean_absdev/neuton_dsp_mad_i16.c"
#include "../mean_absdev/neuton_dsp_mad_i32.c"

#include "../mean_crossing/neuton_dsp_mcr_f32.c"
#include "../mean_crossing/neuton_dsp_mcr_i8.c"
#include "../mean_crossing/neuton_dsp_mcr_i16.c"
#include "../mean_crossing/neuton_dsp_mcr_i32.c"

#include "../min/neuton_dsp_min_f32.c"
#include "../min/neuton_dsp_min_i8.c"
#include "../min/neuton_dsp_min_i16.c"
#include "../min/neuton_dsp_min_i32.c"

#include "../min_max/neuton_dsp_min_max_f32.c"
#include "../min_max/neuton_dsp_min_max_i8.c"
#include "../min_max/neuton_dsp_min_max_i16.c"
#include "../min_max/neuton_dsp_min_max_i32.c"

#include "../moments/neuton_dsp_moments_f32.c"
#include "../moments/neuton_dsp_moments_i8.c"
#include "../moments/neuton_dsp_moments_i16.c"

#include "../peak2peak/high_freq/neuton_dsp_pk2pk_hf_f32.c"
#include "../peak2peak/high_freq/neuton_dsp_pk2pk_hf_i8.c"
#include "../peak2peak/high_freq/neuton_dsp_pk2pk_hf_i16.c"
#include "../peak2peak/high_freq/neuton_dsp_pk2pk_hf_i32.c"

#include "../peak2peak/low_freq/neuton_dsp_pk2pk_lf_f32.c"
#include "../peak2peak/low_freq/neuton_dsp_pk2pk_lf_i8.c"
#include "../peak2peak/low_freq/neuton_dsp_pk2pk_lf_i16.c"
#include "../peak2peak/low_freq/neuton_dsp_pk2pk_lf_i32.c"

#include "../peak2peak/low_high_freq/neuton_dsp_pk2pk_lf_hf_f32.c"
#include "../peak2peak/low_high_freq/neuton_dsp_pk2pk_lf_hf_i8.c"
#include "../peak2peak/low_high_freq/neuton_dsp_pk2pk_lf_hf_i16.c"
#include "../peak2peak/low_high_freq/neuton_dsp_pk2pk_lf_hf_i32.c"

#include "../range/neuton_dsp_range_f32.c"
#include "../range/neuton_dsp_range_i8.c"
#include "../range/neuton_dsp_range_i16.c"
#include "../range/neuton_dsp_range_i32.c"

#include "../rms/neuton_dsp_rms_f32.c"
#include "../rms/neuton_dsp_rms_i8.c"
#include "../rms/neuton_dsp_rms_i16.c"
#include "../rms/neuton_dsp_rms_i32.c"

#include "../rssq/neuton_dsp_rssq_f32.c"
#include "../rssq/neuton_dsp_rssq_i8.c"
#include "../rssq/neuton_dsp_rssq_i16.c"

#include "../skewness/neuton_dsp_skew_f32.c"
#include "../skewness/neuton_dsp_skew_i8.c"
#include "../skewness/neuton_dsp_skew_i16.c"

#include "../stddev/neuton_dsp_stddev_f32.c"
#include "../stddev/neuton_dsp_stddev_i8.c"
#include "../stddev/neuton_dsp_stddev_i16.c"

#include "../sum/neuton_dsp_sum_f32.c"
#include "../sum/neuton_dsp_sum_i8.c"
#include "../sum/neuton_dsp_sum_i16.c"
#include "../sum/neuton_dsp_sum_i32.c"

#include "../threshold_crossing/neuton_dsp_tcr_f32.c"
#include "../threshold_crossing/neuton_dsp_tcr_i8.c"
#include "../threshold_crossing/neuton_dsp_tcr_i16.c"
#include "../threshold_crossing/neuton_dsp_tcr_i32.c"

#include "../tss/neuton_dsp_tss_f32.c"
#include "../tss/neuton_dsp_tss_i8.c"
#include "../tss/neuton_dsp_tss_i16.c"
#include "../tss/neuton_dsp_tss_i32.c"

#include "../tss_sum/neuton_dsp_tss_sum_f32.c"
#include "../tss_sum/neuton_dsp_tss_sum_i8.c"
#include "../tss_sum/neuton_dsp_tss_sum_i16.c"
#include "../tss_sum/neuton_dsp_tss_sum_i32.c"

#include "../variance/neuton_dsp_var_f32.c"
#include "../variance/neuton_dsp_var_i8.c"
#include "../variance/neuton_dsp_var_i16.c"

#include "../zero_crossing/neuton_dsp_zcr_f32.c"
#include "../zero_crossing/neuton_dsp_zcr_i8.c"
#include "../zero_crossing/neuton_dsp_zcr_i16.c"
#include "../zero_crossing/neuton_dsp_zcr_i32.c"

#include "../amdf/neuton_dsp_amdf_f32.c"
#include "../amdf/neuton_dsp_amdf_i8.c"
#include "../amdf/neuton_dsp_amdf_i16.c"

#else

/** ISO C forbids an empty translation unit [-Wpedantic] */
#if defined ( __GNUC__ )
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"
#pragma GCC diagnostic pop
#endif

#endif