cmake_minimum_required(VERSION 2.6)
set(CMAKE_CXX_COMPILER "/usr/bin/clang++")
project(cfd_proto)

set(CFD_HOME ${CMAKE_SOURCE_DIR})
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(MODULE_FOLDER ${CFD_HOME}/modules)

add_subdirectory(pybind11)

add_subdirectory(storage)

add_subdirectory(gtest)