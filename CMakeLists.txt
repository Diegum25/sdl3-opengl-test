cmake_minimum_required(VERSION 3.16)
project(hello)

# set the output directory for built objects.
# This makes sure that the dynamic library goes into the build directory automatically.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

# This assumes the SDL source is available in vendored/SDL
add_subdirectory(vendored/SDL EXCLUDE_FROM_ALL)

if (WIN32)
	# Create your game executable target as usual
	add_executable(hello WIN32 hello.c)
endif (WIN32)
if (UNIX)
	add_executable(hello hello.c)
endif (UNIX)

add_library(glad STATIC glad/src/glad.c)

target_include_directories(glad PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/glad/include)

# Link to the actual SDL3 library.
target_link_libraries(hello PRIVATE SDL3::SDL3 glad)
