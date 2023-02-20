cmake_minimum_required(VERSION 3.13)

project( Neuton_DSP_Support_Clipping
    VERSION 1.0
    DESCRIPTION "Neuton DSP Support Clipping Lib"
    LANGUAGES
        C
)

add_library(${PROJECT_NAME}
    neuton_dsp_clipping_f32.c
    neuton_dsp_clipping_i8.c
    neuton_dsp_clipping_i16.c
)

add_library(Neuton::DSP::Support::Clipping ALIAS ${PROJECT_NAME})

target_include_directories (${PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)