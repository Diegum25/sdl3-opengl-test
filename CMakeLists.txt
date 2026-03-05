cmake_minimum_required(VERSION 3.16)
project(rmi C)

# Output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

option(CGLM_SHARED "Shared build" OFF)
option(CGLM_STATIC "Static build" ON)

enable_language(CXX)

# SDL3
add_subdirectory(SDL EXCLUDE_FROM_ALL) # to build statically add {-DSDL_SHARED=False -DSDL_STATIC=True} to {cmake -S . -B build}

# cglm
add_subdirectory(cglm EXCLUDE_FROM_ALL)

# glad
add_library(glad STATIC glad/src/glad.c)
target_include_directories(glad PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/glad/include
)

# cpp stuff
add_library(rmi_cpp STATIC
    cpp/src/nodes.cpp
)

target_include_directories(rmi_cpp PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/cpp/include
)

target_compile_features(rmi_cpp PUBLIC cxx_std_17)

# stb & self include
include_directories(rmi PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/stb/include ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Executable
add_executable(rmi
    src/main.c
    src/util.c
    src/sceneMatrix.c
    src/shader.c
    src/texture.c
    src/camera.c
    src/obj.c
    src/scene.c
)

# Windows subsystem flag
if (WIN32)
    set_target_properties(rmi PROPERTIES WIN32_EXECUTABLE TRUE)
endif()

# Link libraries
set_target_properties(rmi PROPERTIES LINKER_LANGUAGE C)
target_link_libraries(rmi PRIVATE SDL3::SDL3 glad rmi_cpp m cglm_headers)

# OpenGL
if (WIN32)
    target_link_libraries(rmi PRIVATE opengl32)
endif()
