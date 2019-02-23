cmake_minimum_required(VERSION 2.6)
set(CMAKE_CXX_COMPILER "/usr/bin/clang++")
project(cfd_proto)

set(CFD_HOME ${CMAKE_SOURCE_DIR})
set(CFD_BUILD_DIR ${CMAKE_BINARY_DIR})
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(MODULE_FOLDER ${CFD_HOME}/modules/cfdp/libs)

add_subdirectory(pybind11)

add_subdirectory(storage)
add_subdirectory(connectivity)
add_subdirectory(discretization)
add_subdirectory(readers)
add_subdirectory(mpi)

add_subdirectory(gtest)