cmake_minimum_required(VERSION 3.28)

set(CMAKE_BUILD_TYPE "Debug")
set(JUCE_MANUFACTURER "PFAC")

project(audio_effects VERSION 0.0.1)

add_subdirectory(subprojects)
# add_subdirectory(dsp)

add_subdirectory(effects)
add_subdirectory(synth)