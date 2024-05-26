cmake_minimum_required(VERSION 3.12)

# Change your executable name to something creative!
set(NAME pico-thermostat) # <-- Name your project/executable here!



option(ON_TARGET "Build for a Pico target" OFF)


if(TARGET_ARCH STREQUAL "arm")
    set(ON_TARGET ON)
endif()

if(ON_TARGET)

    message(STATUS "Configuring for target build")

    include(pico_sdk_import.cmake)
    include(pimoroni_pico_import.cmake)
endif()
 
# Gooey boilerplate
project(${NAME} C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Include CTest
include(CTest)

# Enable testing
enable_testing()


add_subdirectory(src)
add_subdirectory(test)
