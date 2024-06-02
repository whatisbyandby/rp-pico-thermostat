
file(GLOB_RECURSE SOURCE ${PROJECT_SOURCE_DIR}/src/logging/*.cpp)

file(GLOB TEST_SOURCE
    ${PROJECT_SOURCE_DIR}/test/logging/test_logger.cpp
    ${PROJECT_SOURCE_DIR}/test/logging/test_logger_main.cpp
)


add_executable(test-logger
    ${SOURCE}
    ${TEST_SOURCE}
)


target_include_directories(test-logger PRIVATE
    ${PROJECT_SOURCE_DIR}/src/logging
)

target_link_libraries(test-logger
    CppUTest::CppUTest
    CppUTest::CppUTestExt
)

# Add the test to CTest
if(ON_TARGET)
    target_link_libraries(test-logger
        pico_stdlib
    )

    target_compile_definitions(test-logger PRIVATE
        ON_TARGET=1
        PICO_CXX_DISABLE_ALLOCATION_OVERRIDES
    )

else()

    target_compile_definitions(test-logger PRIVATE ON_TARGET=0)

endif()

add_test(NAME TestLogging COMMAND test-logger)