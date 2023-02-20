cmake_minimum_required(VERSION 3.13)

project( Neuton_DSP_Statistic_PeakToPeak_HF
    VERSION 1.0
    DESCRIPTION "Neuton DSP Statistics Peak to Peak of High Frequency Functions."
    LANGUAGES
        C
)

add_library(${PROJECT_NAME}
    neuton_dsp_pk2pk_hf_f32.c
    neuton_dsp_pk2pk_hf_i8.c
    neuton_dsp_pk2pk_hf_i16.c
    neuton_dsp_pk2pk_hf_i32.c
)

add_library(Neuton::DSP::Statistic::PeakToPeak::HF ALIAS ${PROJECT_NAME})

target_include_directories (${PROJECT_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)