

file(GLOB TEST_SOURCE 
    ${PROJECT_SOURCE_DIR}/test/thermostat/test_thermostat_main.cpp
    ${PROJECT_SOURCE_DIR}/test/thermostat/test_thermostat.cpp
)

file(GLOB SOURCE 
    ${PROJECT_SOURCE_DIR}/src/thermostat/thermostat.cpp
    ${PROJECT_SOURCE_DIR}/src/temperature_controller/temperature_controller.cpp
)

file(GLOB MOCK_SOURCE

    ${PROJECT_SOURCE_DIR}/test/environment_sensor/mock_environment_sensor.cpp
    ${PROJECT_SOURCE_DIR}/test/hvac/mock_hvac.cpp
)



add_executable(test-thermostat
    ${SOURCE}
    ${TEST_SOURCE}
    ${MOCK_SOURCE}
)

    
target_include_directories(test-thermostat PRIVATE
    ${PROJECT_SOURCE_DIR}/src/common
    ${PROJECT_SOURCE_DIR}/src/environment_sensor
    ${PROJECT_SOURCE_DIR}/src/gpio
    ${PROJECT_SOURCE_DIR}/src/hvac
    ${PROJECT_SOURCE_DIR}/src/i2c_bus
    ${PROJECT_SOURCE_DIR}/src/temperature_controller
    ${PROJECT_SOURCE_DIR}/src/thermostat
    ${PROJECT_SOURCE_DIR}/src/thermostat_controller
)


target_link_libraries(test-thermostat
    CppUTest::CppUTest
    CppUTest::CppUTestExt
)



if(ON_TARGET)
    target_compile_definitions(test-thermostat PRIVATE ON_TARGET=1 PICO_CXX_DISABLE_ALLOCATION_OVERRIDES)

    target_link_libraries(test-thermostat
        pico_stdlib
    )
else()
    target_compile_definitions(test-thermostat PRIVATE ON_TARGET=0)
endif()

add_test(NAME TestThermostat COMMAND test-thermostat)
