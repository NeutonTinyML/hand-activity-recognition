cmake_minimum_required(VERSION 3.13)

project( Neuton_DSP_Pipeline_Spectral
    VERSION 1.0
    DESCRIPTION "Neuton DSP Pipeline for Spectral Features Lib"
    LANGUAGES
        C
)

add_library(${PROJECT_NAME}
    neuton_dsp_pipeline_spectr_f32.c
    neuton_dsp_pipeline_spectr_i8.c
    neuton_dsp_pipeline_spectr_i16.c
)

add_library(Neuton::DSP::Pipeline::Spectral ALIAS ${PROJECT_NAME})

target_include_directories (${PROJECT_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        Neuton::DSP::Spectral
        Neuton::DSP::Transform
)