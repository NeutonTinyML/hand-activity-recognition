cmake_minimum_required(VERSION 3.13)

project( Neuton_DSP_Statistic_PeakToPeak_LF
    VERSION 1.0
    DESCRIPTION "Neuton DSP Statistics Peak to Peak of Low Frequency Functions."
    LANGUAGES
        C
)

add_library(${PROJECT_NAME}
    neuton_dsp_pk2pk_lf_f32.c
    neuton_dsp_pk2pk_lf_i8.c
    neuton_dsp_pk2pk_lf_i16.c
    neuton_dsp_pk2pk_lf_i32.c
)

add_library(Neuton::DSP::Statistic::PeakToPeak::LF ALIAS ${PROJECT_NAME})

target_include_directories (${PROJECT_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)