
file(GLOB_RECURSE THERMOSTAT_SOURCES ${PROJECT_SOURCE_DIR}/src/environment_sensor/*.cpp)
file(GLOB_RECURSE MOCK_SOURCES ${PROJECT_SOURCE_DIR}/test/i2c_bus/*.cpp)

if(ON_TARGET)

    add_executable(test-environment-sensor-target
        ${PROJECT_SOURCE_DIR}/test/environment_sensor/test_environment_sensor.cpp
        ${PROJECT_SOURCE_DIR}/test/environment_sensor/test_environment_sensor_main.cpp
        ${THERMOSTAT_SOURCES}
        ${MOCK_SOURCES}
    )

    target_compile_definitions(test-environment-sensor-target PRIVATE ON_TARGET=1)

    target_include_directories(test-environment-sensor-target PRIVATE
        ${PROJECT_SOURCE_DIR}/src/environment_sensor
        ${PROJECT_SOURCE_DIR}/src/common
        ${PROJECT_SOURCE_DIR}/src/i2c_bus
    )

    target_link_libraries(test-environment-sensor-target
        CppUTest::CppUTest
        CppUTest::CppUTestExt
        pico_stdlib
    )

    target_compile_definitions(test-environment-sensor-target PRIVATE
        PICO_CXX_DISABLE_ALLOCATION_OVERRIDES
    )

    # Add the test to CTest
    add_test(NAME TestEnvironmentSensor COMMAND test-environment-sensor-target)

else()

    add_executable(test-environment-sensor-host
        ${PROJECT_SOURCE_DIR}/test/environment_sensor/test_environment_sensor.cpp
        ${PROJECT_SOURCE_DIR}/test/environment_sensor/test_environment_sensor_main.cpp
        ${THERMOSTAT_SOURCES}
        ${MOCK_SOURCES}
    )


    target_compile_definitions(test-environment-sensor-host PRIVATE ON_TARGET=0)

    target_include_directories(test-environment-sensor-host PRIVATE
        ${PROJECT_SOURCE_DIR}/src/environment_sensor
        ${PROJECT_SOURCE_DIR}/src/common
        ${PROJECT_SOURCE_DIR}/src/i2c_bus
    )

    target_link_libraries(test-environment-sensor-host
        CppUTest::CppUTest
        CppUTest::CppUTestExt
    )

# Add the test to CTest
add_test(NAME TestEnvironmentSensor COMMAND test-environment-sensor-host)

endif()