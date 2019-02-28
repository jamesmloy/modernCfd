set(UNIT_TEST ConnectivityTests)

include(${CFD_HOME}/config/GetBlaze.cmake)

file(GLOB SOURCES "*.cpp")

add_executable(${UNIT_TEST} ${SOURCES})
set_property(TARGET ${UNIT_TEST} PROPERTY CXX_STANDARD 14)

target_include_directories(${UNIT_TEST} PRIVATE ${gtest_SOURCE_DIR}/include
                                                ${gtest_SOURCE_DIR}
                                                ../../include)
add_blaze(${UNIT_TEST})

target_link_libraries(${UNIT_TEST} PRIVATE gtest gtest_main connectivity)

add_test(NAME ${UNIT_TEST} COMMAND ${UNIT_TEST})

add_custom_command(TARGET ${UNIT_TEST} POST_BUILD COMMAND ${UNIT_TEST})