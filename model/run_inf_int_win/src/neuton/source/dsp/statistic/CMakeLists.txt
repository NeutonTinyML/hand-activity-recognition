cmake_minimum_required(VERSION 3.13)

project( Neuton_DSP_Statistic
    VERSION 1.0
    DESCRIPTION "Neuton DSP Statistics Functions library."
    LANGUAGES
        C
)

add_library(${PROJECT_NAME} INTERFACE)
add_library(Neuton::DSP::Statistic ALIAS ${PROJECT_NAME})

target_include_directories (${PROJECT_NAME}
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

if(NEUTON_FAST_BUILD)

    add_compile_definitions(NEUTON_DSP_STATISTICS_FAST_BUILD)
	add_subdirectory(all)

    target_link_libraries(${PROJECT_NAME}
    INTERFACE
        Neuton::DSP::Statistic::ALL
    )

else()

    add_subdirectory(abs_max)
    add_subdirectory(abs_min)
    add_subdirectory(abs_sum)
    add_subdirectory(abs_mean)
    add_subdirectory(min)
    add_subdirectory(max)
    add_subdirectory(min_max)
    add_subdirectory(range)
    add_subdirectory(sum)
    add_subdirectory(mean)
    add_subdirectory(tss)
    add_subdirectory(rms)
    add_subdirectory(rssq)
    add_subdirectory(tss_sum)
    add_subdirectory(variance)
    add_subdirectory(stddev)
    add_subdirectory(zero_crossing)
    add_subdirectory(threshold_crossing)
    add_subdirectory(mean_crossing)
    add_subdirectory(mean_absdev)
    add_subdirectory(skewness)
    add_subdirectory(kurtosis)
    add_subdirectory(moments)
    add_subdirectory(peak2peak)   
    
    target_link_libraries(${PROJECT_NAME}
    INTERFACE
        Neuton::DSP::Statistic::AbsMax
        Neuton::DSP::Statistic::AbsMin
        Neuton::DSP::Statistic::AbsSum
        Neuton::DSP::Statistic::AbsMean
        Neuton::DSP::Statistic::Max
        Neuton::DSP::Statistic::Min
        Neuton::DSP::Statistic::MinMax
        Neuton::DSP::Statistic::Range
        Neuton::DSP::Statistic::Sum
        Neuton::DSP::Statistic::Mean
        Neuton::DSP::Statistic::Tss
        Neuton::DSP::Statistic::Rms
        Neuton::DSP::Statistic::Rssq
        Neuton::DSP::Statistic::TssSum
        Neuton::DSP::Statistic::Variance
        Neuton::DSP::Statistic::Stddev
        Neuton::DSP::Statistic::ZeroCrossing
        Neuton::DSP::Statistic::ThresholdCrossing
        Neuton::DSP::Statistic::MeanCrossing
        Neuton::DSP::Statistic::MeanAbsDev
        Neuton::DSP::Statistic::Skewness
        Neuton::DSP::Statistic::Kurtosis
        Neuton::DSP::Statistic::Moments
        Neuton::DSP::Statistic::PeakToPeak
    )

endif()
