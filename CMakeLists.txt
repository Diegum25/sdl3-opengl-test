cmake_minimum_required(VERSION 3.16)
project(hello C)

# Output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

# SDL3
add_subdirectory(vendored/SDL EXCLUDE_FROM_ALL)

# glad
add_library(glad STATIC glad/src/glad.c)
target_include_directories(glad PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/glad/include
)

#stb
#target_include_directories(hello PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/stb/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/stb/include) #idk

# Executable (always create it)
add_executable(hello hello.c)

# Windows subsystem flag (optional)
if (WIN32)
    set_target_properties(hello PROPERTIES WIN32_EXECUTABLE TRUE)
endif()

# Link libraries
target_link_libraries(hello PRIVATE SDL3::SDL3 glad m)

# OpenGL
if (WIN32)
    target_link_libraries(hello PRIVATE opengl32)
endif()
