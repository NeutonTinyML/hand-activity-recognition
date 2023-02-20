cmake_minimum_required(VERSION 3.13)

project( Neuton_DSP_Pipeline_Statistic
    VERSION 1.0
    DESCRIPTION "Neuton DSP Pipeline for Statistical Feature Lib"
    LANGUAGES
        C
)

add_library(${PROJECT_NAME}
    neuton_dsp_pipeline_stat_f32.c
    neuton_dsp_pipeline_stat_i8.c
    neuton_dsp_pipeline_stat_i16.c
)

add_library(Neuton::DSP::Pipeline::Statistic ALIAS ${PROJECT_NAME})

target_include_directories (${PROJECT_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        Neuton::DSP::Statistic
)