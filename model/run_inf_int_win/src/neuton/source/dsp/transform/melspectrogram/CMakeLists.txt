cmake_minimum_required(VERSION 3.13)

project( Neuton_DSP_Transform_MelSpectrogram
    VERSION 1.0
    DESCRIPTION "Neuton DSP Mel-spectrogram library."
    LANGUAGES
        C
)

add_library(${PROJECT_NAME}
    neuton_dsp_melspectr_f32.c
)

add_library(Neuton::DSP::Transform::MelSpectrogram ALIAS ${PROJECT_NAME})

target_include_directories (${PROJECT_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        m
)