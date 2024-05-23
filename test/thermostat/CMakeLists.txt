

file(GLOB_RECURSE TEST_THERMOSTAT_SOURCES ${PROJECT_SOURCE_DIR}/test/thermostat/*.cpp)
file(GLOB_RECURSE THERMOSTAT_SOURCES ${PROJECT_SOURCE_DIR}/src/thermostat/*.cpp)

if(ON_TARGET)

    add_executable(test-thermostat-target
        ${TEST_THERMOSTAT_SOURCES}
        ${THERMOSTAT_SOURCES}
        ${PROJECT_SOURCE_DIR}/test/environment_sensor/mock_environment_sensor.cpp
    )

    target_compile_definitions(test-thermostat-target PRIVATE ON_TARGET=1)

    target_include_directories(test-thermostat-target PRIVATE
        ${PROJECT_SOURCE_DIR}/src/thermostat
        ${PROJECT_SOURCE_DIR}/src/environment_sensor
        ${PROJECT_SOURCE_DIR}/src/i2c_bus
        ${PROJECT_SOURCE_DIR}/src/common
    )

    target_link_libraries(test-thermostat-target
        CppUTest::CppUTest
        CppUTest::CppUTestExt
        pico_stdlib
    )

    target_compile_definitions(test-thermostat-target PRIVATE
        PICO_CXX_DISABLE_ALLOCATION_OVERRIDES
    )

    add_test(NAME TestThermostat COMMAND test-thermostat-target)
else()

    add_executable(test-thermostat-host
        ${TEST_THERMOSTAT_SOURCES}
        ${THERMOSTAT_SOURCES}
        ${PROJECT_SOURCE_DIR}/test/environment_sensor/mock_environment_sensor.cpp
    )

    target_compile_definitions(test-thermostat-host PRIVATE ON_TARGET=0)

    target_include_directories(test-thermostat-host PRIVATE
        ${PROJECT_SOURCE_DIR}/src/thermostat
        ${PROJECT_SOURCE_DIR}/src/environment_sensor
        ${PROJECT_SOURCE_DIR}/src/i2c_bus
        ${PROJECT_SOURCE_DIR}/src/common
    )

    target_link_libraries(test-thermostat-host
        CppUTest::CppUTest
        CppUTest::CppUTestExt
    )

    # Add the test to CTest
    add_test(NAME TestThermostat COMMAND test-thermostat-host)


endif()