
file(GLOB_RECURSE SOURCE ${PROJECT_SOURCE_DIR}/src/environment_sensor/*.cpp)

file(GLOB TEST_SOURCE
    ${PROJECT_SOURCE_DIR}/test/environment_sensor/test_environment_sensor.cpp
    ${PROJECT_SOURCE_DIR}/test/environment_sensor/test_environment_sensor_main.cpp
)

file(GLOB MOCK_SOURCE 
    ${PROJECT_SOURCE_DIR}/test/i2c_bus/mock_i2c_bus.cpp
)


add_executable(test-environment-sensor
    ${SOURCE}
    ${TEST_SOURCE}
    ${MOCK_SOURCE}
)


target_include_directories(test-environment-sensor PRIVATE
    ${PROJECT_SOURCE_DIR}/src/environment_sensor
    ${PROJECT_SOURCE_DIR}/src/common
    ${PROJECT_SOURCE_DIR}/src/i2c_bus
)

target_link_libraries(test-environment-sensor
    CppUTest::CppUTest
    CppUTest::CppUTestExt
)

# Add the test to CTest
if(ON_TARGET)
    target_link_libraries(test-environment-sensor
        pico_stdlib
    )

    target_compile_definitions(test-environment-sensor PRIVATE
        ON_TARGET=1
        PICO_CXX_DISABLE_ALLOCATION_OVERRIDES
    )

else()

    target_compile_definitions(test-environment-sensor PRIVATE ON_TARGET=0)

endif()

add_test(NAME TestEnvironmentSensor COMMAND test-environment-sensor)