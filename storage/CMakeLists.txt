set(LIB_NAME storage)
set(MOD_NAME Storage)

file(GLOB SOURCES "src/*.cpp")
file(GLOB BINDINGS "bindings/*.cpp")

include(${CFD_HOME}/config/GetBlaze.cmake)

add_library(${LIB_NAME} SHARED ${SOURCES})
target_include_directories(${LIB_NAME} PRIVATE include ${CFD_HOME}/numeric/include)

pybind11_add_module(${MOD_NAME} ${BINDINGS})
target_link_libraries(${MOD_NAME} PRIVATE ${LIB_NAME})
set_target_properties(${MOD_NAME} PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${MODULE_FOLDER})
target_include_directories(${MOD_NAME} PRIVATE include ${CFD_HOME}/numeric/include)

enable_testing()
add_subdirectory(src/test)