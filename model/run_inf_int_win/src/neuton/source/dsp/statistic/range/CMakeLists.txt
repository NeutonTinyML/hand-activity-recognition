cmake_minimum_required(VERSION 3.13)

project( Neuton_DSP_Statistic_Range
    VERSION 1.0
    DESCRIPTION "Neuton DSP Statistics Range Functions."
    LANGUAGES
        C
)

add_library(${PROJECT_NAME}
    neuton_dsp_range_f32.c
    neuton_dsp_range_i8.c
    neuton_dsp_range_i16.c
    neuton_dsp_range_i32.c
)

add_library(Neuton::DSP::Statistic::Range ALIAS ${PROJECT_NAME})

target_include_directories (${PROJECT_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        Neuton::DSP::Statistic::MinMax
)