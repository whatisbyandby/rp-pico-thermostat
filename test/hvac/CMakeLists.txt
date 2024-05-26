
file(GLOB TEST_SOURCE 
    ${PROJECT_SOURCE_DIR}/test/hvac/test_hvac_main.cpp
    ${PROJECT_SOURCE_DIR}/test/hvac/test_hvac.cpp
)
file(GLOB_RECURSE SOURCE ${PROJECT_SOURCE_DIR}/src/hvac/*.cpp)
file(GLOB MOCK_SOURCE ${PROJECT_SOURCE_DIR}/test/gpio/mock_gpio.cpp)

add_executable(test-hvac
    ${TEST_SOURCE}
    ${SOURCE}
    ${MOCK_SOURCE}
)

target_include_directories(test-hvac PRIVATE
    ${PROJECT_SOURCE_DIR}/src/hvac
    ${PROJECT_SOURCE_DIR}/src/environment_sensor
    ${PROJECT_SOURCE_DIR}/src/i2c_bus
    ${PROJECT_SOURCE_DIR}/src/common
    ${PROJECT_SOURCE_DIR}/src/gpio
)

target_link_libraries(test-hvac
    CppUTest::CppUTest
    CppUTest::CppUTestExt
)

    
if(ON_TARGET)

    target_compile_definitions(test-hvac PRIVATE
        ON_TARGET=1
        PICO_CXX_DISABLE_ALLOCATION_OVERRIDES
    )
    target_link_libraries(test-hvac
        pico_stdlib
    )

else()
    target_compile_definitions(test-hvac PRIVATE ON_TARGET=0)
endif()

add_test(NAME TestHvac COMMAND test-hvac-host)