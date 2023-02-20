cmake_minimum_required(VERSION 3.13)

project( Neuton_Utils_OrderedSlidingdWindow
    VERSION 1.0
    DESCRIPTION "Neuton Utils Ordered Window lib"
    LANGUAGES
        C
)

add_library(${PROJECT_NAME}
    neuton_osl_window_init.c
    neuton_osl_window_feed_f32.c
    neuton_osl_window_feed_i8.c
    neuton_osl_window_feed_i16.c
)

add_library(Neuton::Utils::OrderedSlidingWindow ALIAS ${PROJECT_NAME})

target_include_directories (${PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        Neuton::Utils::OrderedWindow
)