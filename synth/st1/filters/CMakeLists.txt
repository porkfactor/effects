cmake_minimum_required(VERSION 3.25.0)

list(APPEND SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/EnvelopeGenerator.cpp
    ${CMAKE_CURRENT_LIST_DIR}/EnvelopeGenerator.hpp
)

set(SOURCES ${SOURCES} PARENT_SCOPE)
