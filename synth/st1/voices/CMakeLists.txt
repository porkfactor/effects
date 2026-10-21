cmake_minimum_required(VERSION 3.25.0)

list(APPEND SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/OscillatorVoice.hpp
    ${CMAKE_CURRENT_LIST_DIR}/OscillatorVoice.cpp
    ${CMAKE_CURRENT_LIST_DIR}/SawtoothVoice.hpp
    ${CMAKE_CURRENT_LIST_DIR}/SawtoothVoice.cpp
    ${CMAKE_CURRENT_LIST_DIR}/SinusoidalVoice.hpp
    ${CMAKE_CURRENT_LIST_DIR}/SinusoidalVoice.cpp
    ${CMAKE_CURRENT_LIST_DIR}/SquareVoice.hpp
    ${CMAKE_CURRENT_LIST_DIR}/SquareVoice.cpp
    ${CMAKE_CURRENT_LIST_DIR}/TriangleVoice.cpp
    ${CMAKE_CURRENT_LIST_DIR}/TriangleVoice.hpp
    ${CMAKE_CURRENT_LIST_DIR}/WavetableSound.cpp
    ${CMAKE_CURRENT_LIST_DIR}/WavetableSound.hpp
    ${CMAKE_CURRENT_LIST_DIR}/WavetableVoice.cpp
    ${CMAKE_CURRENT_LIST_DIR}/WavetableVoice.hpp
)

set(SOURCES ${SOURCES} PARENT_SCOPE)