cmake_minimum_required(VERSION 3.13)

project( Neuton_DSP_Statistic_Skewness
    VERSION 1.0
    DESCRIPTION "Neuton DSP Statistics Skewness Functions."
    LANGUAGES
        C
)

add_library(${PROJECT_NAME}
    neuton_dsp_skew_f32.c
    neuton_dsp_skew_i8.c
    neuton_dsp_skew_i16.c
)

add_library(Neuton::DSP::Statistic::Skewness ALIAS ${PROJECT_NAME})

target_include_directories (${PROJECT_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        Neuton::DSP::Statistic::Sum
        Neuton::DSP::FastMath
        Neuton::DSP::Support::Float24
        m
)