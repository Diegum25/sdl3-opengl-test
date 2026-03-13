cmake_minimum_required(VERSION 3.16)
project(test C)

# i dont even know what this does
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

# RMI
add_subdirectory(.. rmi EXCLUDE_FROM_ALL)

add_executable(test
    main.c
)

set_target_properties(test PROPERTIES LINKER_LANGUAGE C)
target_link_libraries(test PUBLIC rmi)

if (WIN32)
    set_target_properties(test PROPERTIES WIN32_EXECUTABLE TRUE)
endif()