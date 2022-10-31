cmake_minimum_required(VERSION 3.21)
project(GCodeGenerator)

set(CMAKE_CXX_STANDARD 17)
find_package(Boost COMPONENTS system filesystem REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})


add_executable(GCodeGenerator
        main.cpp
        source/engine/Exporting.h
        source/engine/Exporting.cpp
        source/engine/GCodeFile.h
        source/engine/GCodeFile.cpp
        source/engine/Hyrel.h
        source/engine/Hyrel.cpp
        source/engine/ValarrayOperations.h
        source/engine/ValarrayOperations.cpp
        source/engine/PatternBoundaries.cpp
        source/engine/PatternBoundaries.h
        source/engine/extrusion_configuration.cpp
        source/engine/extrusion_configuration.h
        ource/engine/printer_configuration.cpp
        source/engine/printer_configuration.h)

target_link_libraries(GCodeGenerator
        ${Boost_SYSTEM_LIBRARY}
        ${Boost_FILESYSTEM_LIBRARY} -ldl
        )