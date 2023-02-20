cmake_minimum_required(VERSION 3.13)

project( Neuton_DSP_Statistic_AbsMin
    VERSION 1.0
    DESCRIPTION "Neuton DSP Statistics Absolute Min Functions."
    LANGUAGES
        C
)

add_library(${PROJECT_NAME}
    neuton_dsp_absmin_f32.c
    neuton_dsp_absmin_i8.c
    neuton_dsp_absmin_i16.c
    neuton_dsp_absmin_i32.c
)

add_library(Neuton::DSP::Statistic::AbsMin ALIAS ${PROJECT_NAME})

target_include_directories (${PROJECT_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        m
)