cmake_minimum_required(VERSION 3.13)

project( Neuton_DSP_Support_Quantization
    VERSION 1.0
    DESCRIPTION "Neuton DSP Support Quantization library."
    LANGUAGES
        C
)


add_library(${PROJECT_NAME}
    neuton_dsp_quantization.c
)

add_library(Neuton::DSP::Support::Quantization ALIAS ${PROJECT_NAME})

target_include_directories (${PROJECT_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)