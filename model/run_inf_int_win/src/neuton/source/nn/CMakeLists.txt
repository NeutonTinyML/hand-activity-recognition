cmake_minimum_required(VERSION 3.13)

project(Neuton_NN
    VERSION 1.0
    DESCRIPTION "Neuton Neural Network lib"
    LANGUAGES
        C
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/..)

add_library(${PROJECT_NAME}
    neuton_nn.c
    neuton_nn_data_prep_helper.c
    neuton_nn_inference_engine.c
)

add_library(Neuton::NN ALIAS ${PROJECT_NAME})

target_include_directories (${PROJECT_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        Neuton::Utils
        Neuton::DSP
)