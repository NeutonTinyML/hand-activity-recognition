cmake_minimum_required(VERSION 3.13)

project( Neuton_DSP_Statistic_PeakToPeak
    VERSION 1.0
    DESCRIPTION "Neuton DSP Statistics Peak to Peak Functions library."
    LANGUAGES
        C
)

add_subdirectory(high_freq)
add_subdirectory(low_freq)
add_subdirectory(low_high_freq)

add_library(${PROJECT_NAME} INTERFACE)

add_library(Neuton::DSP::Statistic::PeakToPeak ALIAS ${PROJECT_NAME})

target_include_directories (${PROJECT_NAME}
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${PROJECT_NAME}
    INTERFACE
        Neuton::DSP::Statistic::PeakToPeak::HF
        Neuton::DSP::Statistic::PeakToPeak::LF
        Neuton::DSP::Statistic::PeakToPeak::LFHF
)