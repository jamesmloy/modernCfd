set(LIB_NAME discretization)
set(MOD_NAME Discretization)

file(GLOB SOURCES "src/*.cpp")
file(GLOB BINDINGS "bindings/*.cpp")

include(${CFD_HOME}/config/GetBlaze.cmake)

add_library(${LIB_NAME} SHARED ${SOURCES})

target_include_directories(${LIB_NAME} PRIVATE
                           include
                           ${CFD_HOME}/storage/include
                           ${CFD_HOME}/connectivity/include)
add_blaze(${LIB_NAME})

target_link_libraries(${LIB_NAME} PRIVATE storage connectivity)

set_property(TARGET ${LIB_NAME} PROPERTY CXX_STANDARD 14)