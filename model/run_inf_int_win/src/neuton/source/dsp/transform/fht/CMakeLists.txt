cmake_minimum_required(VERSION 3.13)

project( Neuton_DSP_Transform_FHT
    VERSION 1.0
    DESCRIPTION "Neuton DSP Fast Hartley Transform Functions library."
    LANGUAGES
        C
)

add_library(${PROJECT_NAME}
    neuton_dsp_rfht_init.c
    neuton_dsp_rfht_f32.c
    neuton_dsp_rfht_i8.c
    neuton_dsp_rfht_i16.c
)

add_library(Neuton::DSP::Transform::FHT ALIAS ${PROJECT_NAME})

target_include_directories (${PROJECT_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)