cmake_minimum_required(VERSION 3.12)

# Change your executable name to something creative!
set(NAME pico-thermostat) # <-- Name your project/executable here!

option(ON_TARGET "Build for a Pico target" ON)


include(pico_sdk_import.cmake)
include(pimoroni_pico_import.cmake)
 
# Gooey boilerplate
project(${NAME} C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

if (ON_TARGET)

    pico_sdk_init()

    file(GLOB_RECURSE SOURCES
        ${PROJECT_SOURCE_DIR}/src/thermostat/*.cpp
        ${PROJECT_SOURCE_DIR}/src/environment_sensor/*.cpp
        ${PROJECT_SOURCE_DIR}/src/i2c_bus/*.cpp
    )

    # Add your source files
    add_executable(${NAME}
        src/main.cpp # <-- Add source files here!
        ${SOURCES}
    )

    target_include_directories(${NAME} PRIVATE 
        src/thermostat
        src/environment_sensor
        src/i2c_bus
    )

    # Include required libraries
    # This assumes `pimoroni-pico` is stored alongside your project
    include(common/pimoroni_i2c)
    include(common/pimoroni_bus)
    include(libraries/bitmap_fonts/bitmap_fonts)
    include(libraries/hershey_fonts/hershey_fonts)
    include(libraries/pico_explorer/pico_explorer)

    # Don't forget to link the libraries you need!
    target_link_libraries(${NAME}
        pico_stdlib
        hardware_i2c
    )

    # # create map/bin/hex file etc.
    pico_add_extra_outputs(${NAME})

    # # Set up files for the release packages
    install(FILES
        ${CMAKE_CURRENT_BINARY_DIR}/${NAME}.uf2
        ${CMAKE_CURRENT_LIST_DIR}/README.md
        DESTINATION .
    )

    set(CPACK_INCLUDE_TOPLEVEL_DIRECTORY OFF)
    set(CPACK_GENERATOR "ZIP" "TGZ")
    include(CPack)

endif()

add_subdirectory(test)
