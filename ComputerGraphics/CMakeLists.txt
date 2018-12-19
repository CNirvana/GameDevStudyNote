cmake_minimum_required(VERSION 3.10.0)

set(CMAKE_C_STANTARD 11)
set(CMAKE_CXX_STANDARD 11)

project(ComputerGraphics)

include_directories(${PROJECT_SOURCE_DIR}/Math)

file(GLOB SOURCES
    RayTracer/*.h
    RayTracer/*.cpp
)
add_executable(RayTracer ${SOURCES})

file(GLOB SOURCES
    SoftwareRenderer/*.h
    SoftwareRenderer/*.cpp
)
add_executable(SoftwareRenderer ${SOURCES})