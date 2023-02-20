cmake_minimum_required(VERSION 3.13)

project( Neuton_Utils_SlidingWindow
    VERSION 1.0
    DESCRIPTION "Neuton Utils Sliding Window Lib"
    LANGUAGES
        C
)

add_library(${PROJECT_NAME}
    neuton_sliding_window.c
)

add_library(Neuton::Utils::SlidingWindow ALIAS ${PROJECT_NAME})

target_include_directories (${PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)