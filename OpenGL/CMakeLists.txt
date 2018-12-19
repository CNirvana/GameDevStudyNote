cmake_minimum_required(VERSION 3.10.0)

set(CMAKE_C_STANTARD 11)
set(CMAKE_CXX_STANDARD 11)

project(OpenGLStudyNote)

set(LIBS opengl32.lib glfw3.lib assimp-vc140-mt.lib)
link_directories(${PROJECT_SOURCE_DIR}/lib)

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/core)

file(GLOB SOURCES
    ${PROJECT_SOURCE_DIR}/core/*.h
    ${PROJECT_SOURCE_DIR}/core/*.cpp
)
add_library(Core ${SOURCES})
target_link_libraries(Core ${LIBS})

file(GLOB SOURCES
    ${PROJECT_SOURCE_DIR}/sandbox/test/*.h
    ${PROJECT_SOURCE_DIR}/sandbox/test/*.cpp
    ${PROJECT_SOURCE_DIR}/sandbox/test/*.c
)
add_executable(Test ${SOURCES})
target_link_libraries(Test Core)