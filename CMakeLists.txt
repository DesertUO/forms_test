cmake_minimum_required(VERSION 3.26)
project(FormsTest CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SDL3 CONFIG REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/src)

add_executable(Forms_test WIN32 main.cpp)

target_sources(Forms_test
PRIVATE
    main.cpp
    program.h program.cpp
    utils.h utils.cpp
    definitions_utils.h definitions_utils.cpp
    components/components.h components/components.cpp
)

target_link_libraries(Forms_test SDL3::SDL3)
