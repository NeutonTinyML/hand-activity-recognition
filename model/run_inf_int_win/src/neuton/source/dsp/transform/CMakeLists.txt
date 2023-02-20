cmake_minimum_required(VERSION 3.13)

project( Neuton_DSP_Transform
    VERSION 1.0
    DESCRIPTION "Neuton DSP Transform Functions library."
    LANGUAGES
        C
)

add_subdirectory(fht)
add_subdirectory(melspectrogram)

add_library(${PROJECT_NAME} INTERFACE)

add_library(Neuton::DSP::Transform ALIAS ${PROJECT_NAME})

target_include_directories (${PROJECT_NAME}
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${PROJECT_NAME}
    INTERFACE
        Neuton::DSP::Transform::FHT
        Neuton::DSP::Transform::MelSpectrogram
)