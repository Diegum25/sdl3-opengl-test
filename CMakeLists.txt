cmake_minimum_required(VERSION 3.16)
project(rmi C)

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
    glad/include
)

# Libraruy
add_library(rmi STATIC 
    src/main.c
    src/util.c
    src/sceneMatrix.c
    src/shader.c
    src/texture.c
    src/camera.c
    src/scene.c
)

# stb & self include
target_include_directories(rmi PUBLIC stb/include include)

# Link libraries
set_target_properties(rmi PROPERTIES LINKER_LANGUAGE C)
target_link_libraries(rmi PUBLIC SDL3::SDL3 glad m cglm_headers)

# OpenGL
if (WIN32)
    target_link_libraries(rmi PUBLIC opengl32)
endif()
