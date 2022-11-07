cmake_minimum_required(VERSION 3.21)
project(GCodeGenerator)

set(CMAKE_CXX_STANDARD 17)
find_package(Boost COMPONENTS system filesystem REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})


add_executable(GCodeGenerator
        main.cpp
        source/engine/exporting.h
        source/engine/exporting.cpp
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
        source/engine/printer_configuration.cpp source/engine/auxiliary.h source/engine/auxiliary.cpp)

target_link_libraries(GCodeGenerator
        ${Boost_SYSTEM_LIBRARY}
        ${Boost_FILESYSTEM_LIBRARY} -ldl
        )