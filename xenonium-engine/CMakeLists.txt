cmake_minimum_required(VERSION 3.14.0)
project("xenonium-engine" VERSION 0.0.0 LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenGL REQUIRED)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "src/*.cpp" "src/*.hpp" "src/*.c" "src/*.h")
add_library("xenonium-engine" SHARED ${SOURCES})

set_target_properties("xenonium-engine" PROPERTIES
    OUTPUT_NAME "xenonium-engine"
    PREFIX ""
)

target_include_directories("xenonium-engine" PUBLIC src)

target_link_libraries("xenonium-engine" PUBLIC
	OpenGL::GL
)
