

file(GLOB_RECURSE TEST_SOURCE ${PROJECT_SOURCE_DIR}/test/temperature_controller/*.cpp)
file(GLOB_RECURSE SOURCE ${PROJECT_SOURCE_DIR}/src/temperature_controller/*.cpp)


add_executable(test-temperature-controller
    ${TEST_SOURCE}
    ${SOURCE}
)

target_include_directories(test-temperature-controller PRIVATE
    ${PROJECT_SOURCE_DIR}/src/temperature_controller
    ${PROJECT_SOURCE_DIR}/src/common
)

target_link_libraries(test-temperature-controller
    CppUTest::CppUTest
    CppUTest::CppUTestExt
)

if(ON_TARGET)
    target_compile_definitions(test-temperature-controller PRIVATE
        ON_TARGET=1
        PICO_CXX_DISABLE_ALLOCATION_OVERRIDES
    )

    target_link_libraries(test-temperature-controller
        pico_stdlib
    )

else()
    target_compile_definitions(test-temperature-controller PRIVATE ON_TARGET=0)
endif()

# Add the test to CTest
add_test(NAME TestTemperatureController COMMAND test-temperature-controller)

