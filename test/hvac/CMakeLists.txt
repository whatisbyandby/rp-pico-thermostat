

file(GLOB_RECURSE TEST_HVAC_SOURCES ${PROJECT_SOURCE_DIR}/test/hvac/*.cpp)
file(GLOB_RECURSE HVAC_SOURCES ${PROJECT_SOURCE_DIR}/src/hvac/*.cpp)

if(ON_TARGET)

    add_executable(test-hvac-target
        ${TEST_HVAC_SOURCES}
        ${HVAC_SOURCES}
    )

    target_compile_definitions(test-hvac-target PRIVATE ON_TARGET=1)

    target_include_directories(test-hvac-target PRIVATE
        ${PROJECT_SOURCE_DIR}/src/hvac
        ${PROJECT_SOURCE_DIR}/src/environment_sensor
        ${PROJECT_SOURCE_DIR}/src/i2c_bus
        ${PROJECT_SOURCE_DIR}/src/common
    )

    target_link_libraries(test-hvac-target
        CppUTest::CppUTest
        CppUTest::CppUTestExt
        pico_stdlib
    )

    target_compile_definitions(test-hvac-target PRIVATE
        PICO_CXX_DISABLE_ALLOCATION_OVERRIDES
    )

    add_test(NAME TestHvac COMMAND test-hvac-target)
else()

    add_executable(test-hvac-host
        ${TEST_HVAC_SOURCES}
        ${HVAC_SOURCES}
    )

    target_compile_definitions(test-hvac-host PRIVATE ON_TARGET=0)

    target_include_directories(test-hvac-host PRIVATE
        ${PROJECT_SOURCE_DIR}/src/hvac
        ${PROJECT_SOURCE_DIR}/src/environment_sensor
        ${PROJECT_SOURCE_DIR}/src/i2c_bus
        ${PROJECT_SOURCE_DIR}/src/common
    )

    target_link_libraries(test-hvac-host
        CppUTest::CppUTest
        CppUTest::CppUTestExt
    )

    # Add the test to CTest
    add_test(NAME TestHvac COMMAND test-hvac-host)

endif()