cmake_minimum_required(VERSION 3.13)

project( Neuton_Utils
    VERSION 1.0
    DESCRIPTION "Neuton Utils lib"
    LANGUAGES
        C
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/..)

add_subdirectory(ordered_window)
add_subdirectory(sliding_window)
add_subdirectory(ordered_sliding_window)

add_library(${PROJECT_NAME} INTERFACE)
add_library(Neuton::Utils ALIAS ${PROJECT_NAME})

target_include_directories (${PROJECT_NAME}
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${PROJECT_NAME}
    INTERFACE
        Neuton::Utils::OrderedWindow
        Neuton::Utils::SlidingWindow
        Neuton::Utils::OrderedSlidingWindow 
)