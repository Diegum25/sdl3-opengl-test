cmake_minimum_required(VERSION 3.16)
project(hello)

# Output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

option(CGLM_SHARED "Shared build" OFF)
option(CGLM_STATIC "Static build" ON)

# SDL3
add_subdirectory(SDL EXCLUDE_FROM_ALL) # to build statically add {-DSDL_SHARED=False -DSDL_STATIC=True} to {cmake -S . -B build}

# cglm
add_subdirectory(cglm EXCLUDE_FROM_ALL)

# glad
add_library(glad STATIC glad/src/glad.c)
target_include_directories(glad PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/glad/include
)

# stb
include_directories(hello PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/stb/include ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Executable (always create it)
add_executable(hello src/hello.cpp src/util.cpp)

# Windows subsystem flag (optional)
if (WIN32)
    set_target_properties(hello PROPERTIES WIN32_EXECUTABLE TRUE)
endif()

# Link libraries
target_link_libraries(hello PRIVATE SDL3::SDL3 glad m cglm_headers)

# OpenGL
if (WIN32)
    target_link_libraries(hello PRIVATE opengl32)
endif()
