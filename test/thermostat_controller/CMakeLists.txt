

file(GLOB TEST_SOURCE ${PROJECT_SOURCE_DIR}/test/thermostat_controller/*.cpp)
file(GLOB SOURCE ${PROJECT_SOURCE_DIR}/src/thermostat_controller/*.cpp)
file(GLOB MOCK_SOURCE ${PROJECT_SOURCE_DIR}/test/thermostat/mock_thermostat.cpp)


add_executable(test-thermostat-controller
    ${TEST_SOURCE}
    ${SOURCE}
    ${MOCK_SOURCE}
)

    
target_include_directories(test-thermostat-controller PRIVATE
    ${PROJECT_SOURCE_DIR}/src/thermostat_controller
    ${PROJECT_SOURCE_DIR}/src/temperature_controller
    ${PROJECT_SOURCE_DIR}/src/hvac
    ${PROJECT_SOURCE_DIR}/src/gpio
    ${PROJECT_SOURCE_DIR}/src/common
    ${PROJECT_SOURCE_DIR}/src/thermostat
    ${PROJECT_SOURCE_DIR}/src/environment_sensor
    ${PROJECT_SOURCE_DIR}/src/i2c_bus
)

target_link_libraries(test-thermostat-controller
    CppUTest::CppUTest
    CppUTest::CppUTestExt
)

if(ON_TARGET)
    target_compile_definitions(test-thermostat-controller PRIVATE ON_TARGET=1 PICO_CXX_DISABLE_ALLOCATION_OVERRIDES)

    target_link_libraries(test-thermostat-controller
        pico_stdlib
    )
else()
    target_compile_definitions(test-thermostat-controller PRIVATE ON_TARGET=0)

endif()


# Add the test to CTest
add_test(NAME TestThermostatController COMMAND test-thermostat-controller)
