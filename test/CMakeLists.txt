
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


add_subdirectory(thermostat)
add_subdirectory(temperature_controller)

    # Custom target to build all tests
add_custom_target(build_tests
    DEPENDS test-thermostat # Add all your test executables here
)

    # Custom target to run all tests
add_custom_target(run_tests
    COMMAND ${CMAKE_COMMAND} -E env bash ${CMAKE_SOURCE_DIR}/run_tests.sh ${TEST_EXECUTABLES_DIR}
    DEPENDS build_tests
)

