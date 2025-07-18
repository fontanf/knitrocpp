cmake_minimum_required(VERSION 3.15.0)

project(KnitroCpp LANGUAGES CXX)

# Build options.
option(PACKINGSOLVER_BUILD_EXAMPLES "Build examples" ON)
option(PACKINGSOLVER_BUILD_TEST "Build unit tests" ON)

# Require C++11.
set(CMAKE_CXX_STANDARD 11)

# Enable output of compile commands during generation.
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Add sub-directories.
add_subdirectory(extern)
add_subdirectory(src)
if(PACKINGSOLVER_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()
if(PACKINGSOLVER_BUILD_TEST)
    add_subdirectory(test)
endif()
