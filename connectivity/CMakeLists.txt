set(LIB_NAME connectivity)
set(MOD_NAME Connectivity)

file(GLOB SOURCES "src/*.cpp")
file(GLOB BINDINGS "bindings/*.cpp")

include(${CFD_HOME}/config/GetBlaze.cmake)

add_library(${LIB_NAME} SHARED ${SOURCES})

target_include_directories(${LIB_NAME} PRIVATE include)
set_property(TARGET ${LIB_NAME} PROPERTY CXX_STANDARD 14)

enable_testing()
add_subdirectory(src/test)