cmake_minimum_required(VERSION 3.13)

project( Neuton_DSP_Statistic_AverageMagnitudeDiff
    VERSION 1.0
    DESCRIPTION "Neuton DSP Statistics Average Magnitude Difference Functions."
    LANGUAGES
        C
)

add_library(${PROJECT_NAME}
    neuton_dsp_amdf_f32.c
    neuton_dsp_amdf_i8.c
    neuton_dsp_amdf_i16.c
)

add_library(Neuton::DSP::Statistic::AverageMagnitudeDiff ALIAS ${PROJECT_NAME})

target_include_directories (${PROJECT_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)