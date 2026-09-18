cmake_minimum_required(VERSION 3.14.0)
project("xenonium" VERSION 0.0.0 LANGUAGES CXX C)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory("xenonium-engine")
add_subdirectory("game")

message(STATUS "-------------------------------------------------")
message(STATUS "CMake Version: ${CMAKE_VERSION}")
message(STATUS "Min Version Required: ${CMAKE_MINIMUM_REQUIRED_VERSION}")
message(STATUS "Compiler: ${CMAKE_CXX_COMPILER}")
message(STATUS "Version: ${CMAKE_CXX_COMPILER_VERSION}")
message(STATUS "ID: ${CMAKE_CXX_COMPILER_ID}")
message(STATUS "C++ Version: ${CMAKE_CXX_STANDARD}")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "-------------------------------------------------")