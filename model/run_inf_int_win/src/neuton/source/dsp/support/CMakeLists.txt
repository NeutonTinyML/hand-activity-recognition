cmake_minimum_required(VERSION 3.13)

project( Neuton_DSP_Support
    VERSION 1.0
    DESCRIPTION "Neuton DSP Support library."
    LANGUAGES
        C
)

add_library(${PROJECT_NAME} INTERFACE)
add_library(Neuton::DSP::Support ALIAS ${PROJECT_NAME})

target_include_directories (${PROJECT_NAME}
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

if(NEUTON_FAST_BUILD)

    add_compile_definitions(NEUTON_DSP_SUPPORT_FAST_BUILD)

	add_subdirectory(all)
    add_subdirectory(clipping) # Clipping is C macro template based functions, build it separately

    target_link_libraries(${PROJECT_NAME}
    INTERFACE
        Neuton::DSP::Support::ALL
        Neuton::DSP::Support::Clipping
    )

else()

    add_subdirectory(clipping)
    add_subdirectory(scaling)
    add_subdirectory(quantization)
    add_subdirectory(softfloat)
    add_subdirectory(windowing)

    target_link_libraries(${PROJECT_NAME}
    INTERFACE
        Neuton::DSP::Support::Quantization
        Neuton::DSP::Support::Clipping
        Neuton::DSP::Support::Scaling
        Neuton::DSP::Support::Float24
        Neuton::DSP::Support::Windowing
    )

endif()