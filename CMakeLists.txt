cmake_minimum_required(VERSION 3.21)
project(GCodeGenerator VERSION 0.2.1)

set(CMAKE_CXX_STANDARD 17)
find_package(Boost COMPONENTS system filesystem REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

configure_file(source/engine/config.h.in
        config.h @ONLY)
include_directories(${PROJECT_BINARY_DIR})

add_executable(GCodeGenerator
        main.cpp
        source/engine/gcode_file.h
        source/engine/gcode_file.cpp
        source/engine/hyrel.h
        source/engine/hyrel.cpp
        source/engine/valarray_operations.h
        source/engine/valarray_operations.cpp
        source/engine/pattern_boundaries.h
        source/engine/pattern_boundaries.cpp
        source/engine/extrusion_configuration.h
        source/engine/extrusion_configuration.cpp
        source/engine/printer_configuration.h
        source/engine/printer_configuration.cpp
        source/engine/auxiliary.h
        source/engine/auxiliary.cpp
        source/engine/config.h.in source/engine/importing.h source/engine/importing.cpp)

target_link_libraries(GCodeGenerator
        ${Boost_SYSTEM_LIBRARY}
        ${Boost_FILESYSTEM_LIBRARY} -ldl
        )