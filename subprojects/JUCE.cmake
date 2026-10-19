cmake_minimum_required(VERSION 3.25.0)

include (FetchContent)

FetchContent_Declare(JUCE
    GIT_REPOSITORY "https://github.com/juce-framework/JUCE.git"
    GIT_TAG "9.0.0"
    GIT_SUBMODULES ""
    GIT_SHALLOW TRUE
)

FetchContent_MakeAvailable(JUCE)

