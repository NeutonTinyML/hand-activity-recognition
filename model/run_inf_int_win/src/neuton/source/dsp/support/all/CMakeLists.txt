cmake_minimum_required(VERSION 3.13)

project( Neuton_DSP_Support_ALL
    VERSION 1.0
    DESCRIPTION "Neuton DSP Support ALL Functions."
    LANGUAGES
        C
)

add_library(${PROJECT_NAME}
    neuton_dsp_support_all.c
)

add_library(Neuton::DSP::Support::ALL ALIAS ${PROJECT_NAME})

target_include_directories (${PROJECT_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        m
)