set(UNIT_TEST StorageTests)

add_executable(${UNIT_TEST} StorageTests.cpp)

target_include_directories(${UNIT_TEST} PRIVATE ${gtest_SOURCE_DIR}/include
                                                ${gtest_SOURCE_DIR}
                                                ../../include)

target_link_libraries(${UNIT_TEST} PRIVATE gtest gtest_main storage)

add_test(NAME ${UNIT_TEST} COMMAND ${UNIT_TEST})

add_custom_command(TARGET ${UNIT_TEST} POST_BUILD COMMAND ${UNIT_TEST})