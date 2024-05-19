
if(ON_TARGET)

else()
    file(GLOB_RECURSE SOURCES
        ${PROJECT_SOURCE_DIR}/src/thermostat/*.cpp
        ${PROJECT_SOURCE_DIR}/src/environment_sensor/*.cpp
    )

    file(GLOB_RECURSE TEST_SOURCES
        test_main.cpp
        ${PROJECT_SOURCE_DIR}/test/thermostat/*.cpp
        ${PROJECT_SOURCE_DIR}/test/environment_sensor/*.cpp
        ${PROJECT_SOURCE_DIR}/test/i2c_bus/*.cpp
    )

    # CppUTest
    include(FetchContent)
    FetchContent_Declare(
        CppUTest
        GIT_REPOSITORY https://github.com/cpputest/cpputest.git
        GIT_TAG        master # or use release tag, eg. v4.0
    )
    # Set this to ON if you want to have the CppUTests in your project as well.
    set(TESTS OFF CACHE BOOL "Switch off CppUTest Test build")
    FetchContent_MakeAvailable(CppUTest)

    add_executable(test-pico-thermostat
        ${SOURCES}
        ${TEST_SOURCES}
    )

    target_compile_definitions(test-pico-thermostat PRIVATE ON_TARGET=0)

    target_include_directories(test-pico-thermostat PRIVATE
        ${PROJECT_SOURCE_DIR}/src/thermostat
        ${PROJECT_SOURCE_DIR}/src/environment_sensor
        ${PROJECT_SOURCE_DIR}/src/i2c_bus
        ${PROJECT_SOURCE_DIR}/test/i2c_bus
    )

    target_link_libraries(test-pico-thermostat
        CppUTest::CppUTest
        CppUTest::CppUTestExt
    )

    target_compile_definitions(test-pico-thermostat PRIVATE
        PICO_CXX_DISABLE_ALLOCATION_OVERRIDES
    )
endif()
