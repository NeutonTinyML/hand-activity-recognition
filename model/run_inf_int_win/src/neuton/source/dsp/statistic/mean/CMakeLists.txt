cmake_minimum_required(VERSION 3.13)

project( Neuton_DSP_Statistic_Mean
    VERSION 1.0
    DESCRIPTION "Neuton DSP Statistics Mean Functions."
    LANGUAGES
        C
)

add_library(${PROJECT_NAME}
    neuton_dsp_mean_f32.c
    neuton_dsp_mean_i8.c
    neuton_dsp_mean_i16.c
    neuton_dsp_mean_i32.c
)

add_library(Neuton::DSP::Statistic::Mean ALIAS ${PROJECT_NAME})

target_include_directories (${PROJECT_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        Neuton::DSP::Statistic::Sum
)