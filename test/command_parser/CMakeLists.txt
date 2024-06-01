
file(GLOB_RECURSE SOURCE ${PROJECT_SOURCE_DIR}/src/command_parser/*.cpp)

file(GLOB TEST_SOURCE
    ${PROJECT_SOURCE_DIR}/test/command_parser/test_command_parser.cpp
    ${PROJECT_SOURCE_DIR}/test/command_parser/test_command_parser_main.cpp
)

file(GLOB MOCK_SOURCE 
    ${PROJECT_SOURCE_DIR}/test/i2c_bus/mock_i2c_bus.cpp
)


add_executable(test-command-parser
    ${SOURCE}
    ${TEST_SOURCE}
    ${MOCK_SOURCE}
)


target_include_directories(test-command-parser PRIVATE
    ${PROJECT_SOURCE_DIR}/src/command_parser
    ${PROJECT_SOURCE_DIR}/src/common
    ${PROJECT_SOURCE_DIR}/src/i2c_bus
)

target_link_libraries(test-command-parser
    CppUTest::CppUTest
    CppUTest::CppUTestExt
)

# Add the test to CTest
if(ON_TARGET)
    target_link_libraries(test-command-parser
        pico_stdlib
    )

    target_compile_definitions(test-command-parser PRIVATE
        ON_TARGET=1
        PICO_CXX_DISABLE_ALLOCATION_OVERRIDES
    )

else()

    target_compile_definitions(test-command-parser PRIVATE ON_TARGET=0)

endif()

add_test(NAME TestCommandParser COMMAND test-command-parser)