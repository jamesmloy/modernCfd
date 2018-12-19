set(LIB_NAME readers)
set(MOD_NAME Readers)

file(GLOB SOURCES "src/*.cpp")
file(GLOB BINDINGS "bindings/*.cpp")

include(${CFD_HOME}/config/GetBlaze.cmake)

add_library(${LIB_NAME} SHARED ${SOURCES})

target_include_directories(${LIB_NAME} PRIVATE include
                                               ${CFD_HOME}/discretization/include
                                               ${CFD_HOME}/storage/include
                                               ${CFD_HOME}/connectivity/include
                                               ${CFD_HOME}/utils/include)

set_property(TARGET ${LIB_NAME} PROPERTY CXX_STANDARD 14)

pybind11_add_module(${MOD_NAME} ${BINDINGS})
target_link_libraries(${MOD_NAME} PRIVATE ${LIB_NAME})
set_target_properties(${MOD_NAME} PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${MODULE_FOLDER})
target_include_directories(${MOD_NAME} PRIVATE include
                                               ${CFD_HOME}/discretization/include
                                               ${CFD_HOME}/storage/include
                                               ${CFD_HOME}/connectivity/include
                                               ${CFD_HOME}/utils/include)

# enable_testing()
# add_subdirectory(src/test)