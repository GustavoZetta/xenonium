cmake_minimum_required(VERSION 3.14.0)
project("game" VERSION 0.0.0 LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "src/*.cpp" "src/*.hpp" "src/*.c" "src/*.h")
add_executable("game" ${SOURCES})

target_link_libraries("game" 
    "xenonium-engine"
)