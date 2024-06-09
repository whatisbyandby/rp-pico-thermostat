
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
add_subdirectory(environment_sensor)
add_subdirectory(hvac)
add_subdirectory(thermostat_controller)
add_subdirectory(i2c_bus)
add_subdirectory(command_parser)
add_subdirectory(logging)
add_subdirectory(json)
add_subdirectory(producer)



