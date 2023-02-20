cmake_minimum_required(VERSION 3.13)

project( Neuton_DSP_Support_Windowing
    VERSION 1.0
    DESCRIPTION "Neuton DSP Support Windowing library."
    LANGUAGES
        C
)

add_library(${PROJECT_NAME}
    neuton_dsp_windowing.c
)

add_library(Neuton::DSP::Support::Windowing ALIAS ${PROJECT_NAME})

target_include_directories (${PROJECT_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        m
)