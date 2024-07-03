



if (ON_TARGET)

    pico_sdk_init()

    file(GLOB_RECURSE SOURCES
        ${PROJECT_SOURCE_DIR}/src/thermostat/*.cpp
        ${PROJECT_SOURCE_DIR}/src/environment_sensor/*.cpp
        ${PROJECT_SOURCE_DIR}/src/i2c_bus/*.cpp
        ${PROJECT_SOURCE_DIR}/src/gpio/*.cpp
        ${PROJECT_SOURCE_DIR}/src/hvac/*.cpp
        ${PROJECT_SOURCE_DIR}/src/temperature_controller/*.cpp
        ${PROJECT_SOURCE_DIR}/src/command_parser/*.cpp
        ${PROJECT_SOURCE_DIR}/src/repl/*.cpp
        ${PROJECT_SOURCE_DIR}/src/json/*.cpp
        ${PROJECT_SOURCE_DIR}/src/display/*.cpp
        ${PROJECT_SOURCE_DIR}/src/producer/*.cpp
        ${PROJECT_SOURCE_DIR}/src/mqtt/*.cpp
        ${PROJECT_SOURCE_DIR}/src/wifi/*.cpp
		${PROJECT_SOURCE_DIR}/src/configuration/*.cpp
        ${PROJECT_SOURCE_DIR}/src/watchdog/*.cpp
    )

    add_executable(${NAME}
        main.cpp # <-- Add source files here!
        ${SOURCES}
    )

    target_include_directories(${NAME} PRIVATE 
        common
        thermostat
        temperature_controller
        environment_sensor
        i2c_bus
        hvac
        gpio
        command_parser
        repl
        json
        display
        producer
        mqtt
        wifi
		configuration
        watchdog
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
        pico_multicore
        pico_cyw43_arch_lwip_threadsafe_background
        pico_lwip_mqtt
        hardware_i2c
        hardware_flash 
        hardware_sync
        hardware_watchdog
        pico_explorer
        pico_graphics
        st7789
        json_maker
    )

    # # create map/bin/hex file etc.
    pico_add_extra_outputs(${NAME})

    # # Set up files for the release packages
    install(FILES
        ${CMAKE_CURRENT_BINARY_DIR}/${NAME}.uf2
        ${PROJECT_SOURCE_DIR}/README.md
        DESTINATION .
    )

    set(CPACK_INCLUDE_TOPLEVEL_DIRECTORY OFF)
    set(CPACK_GENERATOR "ZIP" "TGZ")
    include(CPack)

endif()