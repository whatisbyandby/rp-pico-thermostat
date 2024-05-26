

file(GLOB_RECURSE SOURCE ${PROJECT_SOURCE_DIR}/test/i2c_bus/*.cpp)



add_executable(test-i2c-bus
    ${SOURCE}
)

target_include_directories(test-i2c-bus PRIVATE
    ${PROJECT_SOURCE_DIR}/src/i2c_bus
)

target_link_libraries(test-i2c-bus
    CppUTest::CppUTest
    CppUTest::CppUTestExt
)

if(ON_TARGET)
    target_compile_definitions(test-i2c-bus PRIVATE
        ON_TARGET=1
        PICO_CXX_DISABLE_ALLOCATION_OVERRIDES
    )

    target_link_libraries(test-i2c-bus
        pico_stdlib
    )

else()
    target_compile_definitions(test-i2c-bus PRIVATE ON_TARGET=0)
endif()

# Add the test to CTest
add_test(NAME TestI2CBus COMMAND test-i2c-bus)

