cmake_minimum_required(VERSION 3.13)

project( Neuton_DSP_Support_Float24
    VERSION 1.0
    DESCRIPTION "Neuton DSP Support Float24 library."
    LANGUAGES
        C
)

add_library(${PROJECT_NAME}
    neuton_f24.c
)

add_library(Neuton::DSP::Support::Float24 ALIAS ${PROJECT_NAME})

target_include_directories (${PROJECT_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        m
)