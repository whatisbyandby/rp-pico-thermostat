

file(GLOB_RECURSE TEST_THERMOSTAT_SOURCES ${PROJECT_SOURCE_DIR}/test/temperature_controller/*.cpp)
file(GLOB_RECURSE THERMOSTAT_SOURCES ${PROJECT_SOURCE_DIR}/src/temperature_controller/*.cpp)

if(ON_TARGET)

    add_executable(test-temperature-controller-target
        ${TEST_THERMOSTAT_SOURCES}
        ${THERMOSTAT_SOURCES}
    )

    target_compile_definitions(test-temperature-controller-target PRIVATE ON_TARGET=1)

    target_include_directories(test-temperature-controller-target PRIVATE
        ${PROJECT_SOURCE_DIR}/src/temperature_controller
        ${PROJECT_SOURCE_DIR}/src/common
    )

    target_link_libraries(test-temperature-controller-target
        CppUTest::CppUTest
        CppUTest::CppUTestExt
        pico_stdlib
    )

    target_compile_definitions(test-temperature-controller-target PRIVATE
        PICO_CXX_DISABLE_ALLOCATION_OVERRIDES
    )

    # Add the test to CTest
    add_test(NAME TestThermostat COMMAND test-temperature-controller-target)

else()

    add_executable(test-temperature-controller-host
        ${TEST_THERMOSTAT_SOURCES}
        ${THERMOSTAT_SOURCES}
    )

    target_compile_definitions(test-temperature-controller-host PRIVATE ON_TARGET=0)

    target_include_directories(test-temperature-controller-host PRIVATE
        ${PROJECT_SOURCE_DIR}/src/temperature_controller
        ${PROJECT_SOURCE_DIR}/src/common
    )

    target_link_libraries(test-temperature-controller-host
        CppUTest::CppUTest
        CppUTest::CppUTestExt
    )

# Add the test to CTest
add_test(NAME TestThermostat COMMAND test-temperature-controller-host)

endif()