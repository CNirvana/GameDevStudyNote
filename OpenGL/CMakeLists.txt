cmake_minimum_required(VERSION 3.10.0)

set(CMAKE_C_STANTARD 11)
set(CMAKE_CXX_STANDARD 11)

project(OpenGLStudyNote)

set(LIBS opengl32.lib glfw3.lib assimp-vc140-mt.lib)
link_directories(${PROJECT_SOURCE_DIR}/lib)

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/core)

# core
file(GLOB SOURCES
    ${PROJECT_SOURCE_DIR}/core/*.h
    ${PROJECT_SOURCE_DIR}/core/renderer/*.h
    ${PROJECT_SOURCE_DIR}/core/*.cpp
    ${PROJECT_SOURCE_DIR}/core/renderer/*.cpp
    ${PROJECT_SOURCE_DIR}/core/*.c
)
add_library(Core ${SOURCES})
target_link_libraries(Core ${LIBS})

set(CHAPTERS
    FrameBuffer
    Shadow
    Lighting
)

foreach(CHAPTER ${CHAPTERS})
    file(GLOB SOURCES
        ${PROJECT_SOURCE_DIR}/sandbox/${CHAPTER}/*.h
        ${PROJECT_SOURCE_DIR}/sandbox/${CHAPTER}/*.cpp
    )
    set(NAME ${CHAPTER})
    add_executable(${NAME} ${SOURCES})
    target_link_libraries(${NAME} Core)
    set_target_properties(${NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/build/bin/${CHAPTER}")
    foreach(RESOURCE ${RESOURCES})
        add_custom_command(TARGET ${NAME} PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${RESOURCE} $<TARGET_FILE_DIR:${NAME}>)
    endforeach(RESOURCE)
    add_custom_command(TARGET ${NAME} PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/sandbox/${CHAPTER}/resources $<TARGET_FILE_DIR:${NAME}>)
    add_custom_command(TARGET ${NAME} PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}/bin/assimp-vc140-mt.dll $<TARGET_FILE_DIR:${NAME}>)
endforeach(CHAPTER)