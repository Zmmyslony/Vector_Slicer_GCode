cmake_minimum_required(VERSION 3.21)
project(GCodeGenerator)

set(CMAKE_CXX_STANDARD 17)

add_executable(GCodeGenerator main.cpp source/engine/Exporting.h source/engine/Exporting.cpp source/engine/GCodeFile.h source/engine/GCodeFile.cpp source/engine/Hyrel.h source/engine/Hyrel.cpp source/engine/ValarrayOperations.h source/engine/ValarrayOperations.cpp)
