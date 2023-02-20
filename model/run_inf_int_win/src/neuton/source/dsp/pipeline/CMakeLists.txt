cmake_minimum_required(VERSION 3.13)

project( Neuton_DSP_Pipeline
    VERSION 1.0
    DESCRIPTION "Neuton DSP Pipeline Lib"
    LANGUAGES
        C
)

add_subdirectory(statistic)
add_subdirectory(spectral)

add_library(${PROJECT_NAME} 
    neuton_dsp_pipeline_f32.c
    neuton_dsp_pipeline_i8.c
    neuton_dsp_pipeline_i16.c
)

add_library(Neuton::DSP::Pipeline ALIAS ${PROJECT_NAME})

target_include_directories (${PROJECT_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        Neuton::DSP::Pipeline::Statistic
        Neuton::DSP::Pipeline::Spectral
)