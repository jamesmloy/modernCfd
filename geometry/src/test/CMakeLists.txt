set(UNIT_TEST GeometryTests)

include(${CFD_HOME}/config/GetBlaze.cmake)

file(GLOB SOURCES "*.cpp")
add_executable(${UNIT_TEST} ${SOURCES})

target_compile_definitions(${UNIT_TEST} PRIVATE UNIT_TEST=${UNIT_TEST})

target_include_directories(${UNIT_TEST} PRIVATE ${gtest_SOURCE_DIR}/include
                                                ${gtest_SOURCE_DIR}
                                                ../../include
                                                ${CFD_HOME}/utils/include)
add_blaze(${UNIT_TEST})

target_link_libraries(${UNIT_TEST} PRIVATE gtest gtest_main)

add_test(NAME ${UNIT_TEST} COMMAND ${UNIT_TEST})

add_custom_command(TARGET ${UNIT_TEST} POST_BUILD COMMAND ${UNIT_TEST})