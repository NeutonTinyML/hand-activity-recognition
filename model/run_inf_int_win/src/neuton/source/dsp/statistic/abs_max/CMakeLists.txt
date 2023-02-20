cmake_minimum_required(VERSION 3.13)

project( Neuton_DSP_Statistic_AbsMax
    VERSION 1.0
    DESCRIPTION "Neuton DSP Statistics Absolute Max Functions."
    LANGUAGES
        C
)

add_library(${PROJECT_NAME}
    neuton_dsp_absmax_f32.c
    neuton_dsp_absmax_i8.c
    neuton_dsp_absmax_i16.c
    neuton_dsp_absmax_i32.c
)

add_library(Neuton::DSP::Statistic::AbsMax ALIAS ${PROJECT_NAME})

target_include_directories (${PROJECT_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        m
)