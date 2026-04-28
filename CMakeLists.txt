cmake_minimum_required(VERSION 3.16)
project(rmi C)

# Output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

option(CGLM_SHARED "Shared build" OFF)
option(CGLM_STATIC "Static build" ON)
option(SDL_SHARED "Shared build" OFF)
option(SDL_STATIC "Static build" ON)

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
add_library(rmi OBJECT # winmain not defined fix
    src/main.c
    src/tree.c
    src/node_base.c
    src/globals.c
)

# stb & self include
target_include_directories(rmi PUBLIC include stb/include PRIVATE src/ )

# Link libraries
set_target_properties(rmi PROPERTIES LINKER_LANGUAGE C)

# OpenGL
if (WIN32)
    target_link_libraries(rmi PUBLIC opengl32)
    target_link_libraries(rmi PRIVATE --static SDL3::SDL3 cglm_headers glad m)
else()
    target_link_libraries(rmi PRIVATE SDL3::SDL3 cglm_headers glad m)
endif()