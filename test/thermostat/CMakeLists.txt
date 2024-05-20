

file(GLOB_RECURSE TEST_THERMOSTAT_SOURCES ${PROJECT_SOURCE_DIR}/test/thermostat/*.cpp)
file(GLOB_RECURSE THERMOSTAT_SOURCES ${PROJECT_SOURCE_DIR}/src/thermostat/*.cpp)




add_executable(test-thermostat
    ${TEST_THERMOSTAT_SOURCES}
    ${THERMOSTAT_SOURCES}
    ${PROJECT_SOURCE_DIR}/test/environment_sensor/mock_environment_sensor.cpp
)

target_compile_definitions(test-thermostat PRIVATE ON_TARGET=0)

target_include_directories(test-thermostat PRIVATE
    ${PROJECT_SOURCE_DIR}/src/thermostat
    ${PROJECT_SOURCE_DIR}/src/environment_sensor
    ${PROJECT_SOURCE_DIR}/src/i2c_bus
    ${PROJECT_SOURCE_DIR}/src/common
)

target_link_libraries(test-thermostat
    CppUTest::CppUTest
    CppUTest::CppUTestExt
)

target_compile_definitions(test-thermostat PRIVATE
    PICO_CXX_DISABLE_ALLOCATION_OVERRIDES
)