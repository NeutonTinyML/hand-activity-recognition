cmake_minimum_required(VERSION 3.13)

project( Neuton_DSP_Support_Scaling
    VERSION 1.0
    DESCRIPTION "Neuton DSP Scaling Lib"
    LANGUAGES
        C
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(min_max)
add_subdirectory(z_score)

add_library(${PROJECT_NAME} INTERFACE)
add_library(Neuton::DSP::Support::Scaling ALIAS ${PROJECT_NAME})

target_include_directories (${PROJECT_NAME}
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${PROJECT_NAME}
    INTERFACE
        Neuton::DSP::Support::Scaling::MinMax
        Neuton::DSP::Support::Scaling::Zscore
)