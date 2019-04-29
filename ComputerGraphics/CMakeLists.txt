cmake_minimum_required(VERSION 3.10.0)

set(CMAKE_C_STANTARD 11)
set(CMAKE_CXX_STANDARD 11)

project(ComputerGraphics)

include_directories(${PROJECT_SOURCE_DIR}/Common)
include_directories(${PROJECT_SOURCE_DIR}/Math)
include_directories(${PROJECT_SOURCE_DIR}/SDL2/include)

set(LIBS SDL2.lib)
link_directories(${PROJECT_SOURCE_DIR}/SDL2/lib/x86)

file(GLOB SOURCES
    Common/*.cpp
)
add_library(Common ${SOURCES})

file(GLOB SOURCES
    Math/*.cpp
)
add_library(Math ${SOURCES})

# Ray Tracer
file(GLOB SOURCES
    RayTracer/*.h
    RayTracer/*.cpp
)
add_executable(RayTracer ${SOURCES})
target_link_libraries(RayTracer Common Math)

# Software Renderer
file(GLOB SOURCES
    SoftwareRenderer/*.h
    SoftwareRenderer/*.cpp
)
add_executable(SoftwareRenderer ${SOURCES})
target_link_libraries(SoftwareRenderer Common Math ${LIBS})