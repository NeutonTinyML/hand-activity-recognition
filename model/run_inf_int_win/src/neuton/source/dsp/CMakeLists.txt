cmake_minimum_required(VERSION 3.13)

project( Neuton_DSP
    VERSION 1.0
    DESCRIPTION "Neuton DSP library."
    LANGUAGES
        C
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/..)

add_subdirectory(statistic)
add_subdirectory(transform)
add_subdirectory(spectral)
add_subdirectory(support)
add_subdirectory(fast_math)
add_subdirectory(pipeline)

add_library(${PROJECT_NAME} INTERFACE)
add_library(Neuton::DSP ALIAS ${PROJECT_NAME})

target_include_directories (${PROJECT_NAME}
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${PROJECT_NAME}
    INTERFACE
        Neuton::DSP::Transform
        Neuton::DSP::Statistic
        Neuton::DSP::Support
        Neuton::DSP::FastMath
        Neuton::DSP::Pipeline
        Neuton::DSP::Spectral
)