cmake_minimum_required(VERSION 3.13)

project( Neuton_DSP_Support_Scaling_MinMax
    VERSION 1.0
    DESCRIPTION "Neuton DSP MinMax Scaling Lib"
    LANGUAGES
        C
)

add_library(${PROJECT_NAME}
    neuton_dsp_scale_minmax_f32.c
    neuton_dsp_scale_minmax_i8.c
    neuton_dsp_scale_minmax_i16.c
)

add_library(Neuton::DSP::Support::Scaling::MinMax ALIAS ${PROJECT_NAME})

target_include_directories (${PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)