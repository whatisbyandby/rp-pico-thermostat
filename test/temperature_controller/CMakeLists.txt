

file(GLOB_RECURSE TEST_THERMOSTAT_SOURCES ${PROJECT_SOURCE_DIR}/test/temperature_controller/*.cpp)
file(GLOB_RECURSE THERMOSTAT_SOURCES ${PROJECT_SOURCE_DIR}/src/temperature_controller/*.cpp)


add_executable(test-temperature-controller
    ${TEST_THERMOSTAT_SOURCES}
    ${THERMOSTAT_SOURCES}
)

target_compile_definitions(test-temperature-controller PRIVATE ON_TARGET=0)

target_include_directories(test-temperature-controller PRIVATE
    ${PROJECT_SOURCE_DIR}/src/temperature_controller
    ${PROJECT_SOURCE_DIR}/src/common
)

target_link_libraries(test-temperature-controller
    CppUTest::CppUTest
    CppUTest::CppUTestExt
)

target_compile_definitions(test-temperature-controller PRIVATE
    PICO_CXX_DISABLE_ALLOCATION_OVERRIDES
)