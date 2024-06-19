if(ON_TARGET)
    # target_compile_definitions(test-repl PRIVATE ON_TARGET=1 PICO_CXX_DISABLE_ALLOCATION_OVERRIDES)

    # target_link_libraries(test-repl
    #     pico_stdlib
    # )
else()

file(GLOB TEST_SOURCE 
    ${PROJECT_SOURCE_DIR}/test/repl/test_repl_main.cpp
    ${PROJECT_SOURCE_DIR}/test/repl/test_repl.cpp
)

file(GLOB SOURCE 
    ${PROJECT_SOURCE_DIR}/src/repl/repl.cpp
    ${PROJECT_SOURCE_DIR}/src/command_parser/command_parser.cpp
)

file(GLOB MOCK_SOURCE
    ${PROJECT_SOURCE_DIR}/test/mocks/hardware_mocks/hardware/uart.cpp
    ${PROJECT_SOURCE_DIR}/test/mocks/pico_mocks/pico/stdlib.cpp
)


add_executable(test-repl
    ${SOURCE}
    ${TEST_SOURCE}
    ${MOCK_SOURCE}
)

    
target_include_directories(test-repl PRIVATE
    ${PROJECT_SOURCE_DIR}/src/repl
    ${PROJECT_SOURCE_DIR}/src/common
    ${PROJECT_SOURCE_DIR}/src/command_parser
    ${PROJECT_SOURCE_DIR}/test/mocks/hardware_mocks
    ${PROJECT_SOURCE_DIR}/test/mocks/pico_mocks
)


target_link_libraries(test-repl
    CppUTest::CppUTest
    CppUTest::CppUTestExt
)




    target_compile_definitions(test-repl PRIVATE ON_TARGET=0)
endif()

add_test(NAME TestRepl COMMAND test-repl)
