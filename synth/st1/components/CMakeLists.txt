cmake_minimum_required(VERSION 3.25.0)

list(APPEND SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/EnvelopeVisualizer.cpp
    ${CMAKE_CURRENT_LIST_DIR}/EnvelopeVisualizer.hpp
    ${CMAKE_CURRENT_LIST_DIR}/OscillatorEditor.cpp
    ${CMAKE_CURRENT_LIST_DIR}/OscillatorEditor.hpp
)

set(SOURCES ${SOURCES} PARENT_SCOPE)