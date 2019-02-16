set(LIB_NAME cfdMpi)
set(MOD_NAME CfdMpi)

find_package(MPI REQUIRED)

file(GLOB SOURCES "src/*.cpp")
file(GLOB BINDINGS "bindings/*.cpp")

add_library(${LIB_NAME} SHARED ${SOURCES})
target_include_directories(${LIB_NAME} PRIVATE include ${MPI_INCLUDE_PATH})

set_target_properties(${LIB_NAME} PROPERTIES CMAKE_CXX_COMPILER "/usr/bin/mpicxx.openmpi")

pybind11_add_module(${MOD_NAME} ${BINDINGS})
set_target_properties(${MOD_NAME} PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${MODULE_FOLDER})
set_target_properties(${MOD_NAME} PROPERTIES CMAKE_CXX_COMPILER "/usr/bin/mpicxx.openmpi")
set_target_properties(${MOD_NAME} PROPERTIES CMAKE_CXX_FLAGS "-vv")
target_include_directories(${MOD_NAME} PRIVATE include ${MPI_INCLUDE_PATH})
target_link_libraries(${MOD_NAME} PRIVATE ${MPI_CXX_LIBRARIES})