cmake_minimum_required(VERSION 3.13)

project( Neuton_DSP_Support_Scaling_Zscore
    VERSION 1.0
    DESCRIPTION "Neuton DSP Z-score Scaling Lib"
    LANGUAGES
        C
)

add_library(${PROJECT_NAME}
    neuton_dsp_scale_zscore_f32.c
    neuton_dsp_scale_zscore_i8.c
    neuton_dsp_scale_zscore_i16.c
)

add_library(Neuton::DSP::Support::Scaling::Zscore ALIAS ${PROJECT_NAME})

target_include_directories (${PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)