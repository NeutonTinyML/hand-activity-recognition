cmake_minimum_required(VERSION 3.13)

project( Neuton_DSP_Spectral
    VERSION 1.0
    DESCRIPTION "Neuton DSP Spectral Analysis Functions library."
    LANGUAGES
        C
)

add_subdirectory(findpeaks)

add_library(${PROJECT_NAME} INTERFACE)

add_library(Neuton::DSP::Spectral ALIAS ${PROJECT_NAME})

target_include_directories (${PROJECT_NAME}
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${PROJECT_NAME}
    INTERFACE
        Neuton::DSP::Spectral::FindPeaks

)