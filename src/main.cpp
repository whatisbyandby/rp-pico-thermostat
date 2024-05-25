#include "environment_sensor.hpp"
#include "i2c_bus.hpp"
#include "pico/stdlib.h"
#include "hvac.hpp"
#include "thermostat.hpp"
#include "temperature_controller.hpp"
#include <stdio.h>

#include "pico_explorer.hpp"
#include "drivers/st7789/st7789.hpp"
#include "libraries/pico_graphics/pico_graphics.hpp"

#include "font6_data.hpp"
#include "font8_data.hpp"

#include <iostream>
#include <sstream>
#include <iomanip>  // Include this header for std::fixed and std::setprecision

using namespace pimoroni;

extern unsigned char _binary_fox_tga_start[];

ST7789 st7789(PicoExplorer::WIDTH, PicoExplorer::HEIGHT, ROTATE_0, false, get_spi_pins(BG_SPI_FRONT));
PicoGraphics_PenRGB332 graphics(st7789.width, st7789.height, nullptr);

int main()
{
    stdio_init_all();

    graphics.set_font(&font8);

    Pen BG = graphics.create_pen(120, 40, 60);
    Pen WHITE = graphics.create_pen(255, 255, 255);

    I2CBus i2cBus;
    i2cBus.initialize();
    I2CDevice i2cDevice(&i2cBus, 0x38);
    EnvironmentSensor environmentSensor(&i2cDevice);

    Thermostat thermostat;
    thermostat.initialize();

    TemperatureController temperatureController;

    HVAC hvac;

    while (true)
    {
        double temperature;
        double humidity;

        environmentSensor.readTemperatureHumidity(&temperature, &humidity);

        TemperatureState temperatureState = temperatureController.checkTemperature(temperature);

        HVACState desiredState = thermostat.getDesiredHVACState(temperatureState, hvac.getCurrentState());

        // hvac.setDesiredState(desiredState);

        graphics.set_pen(BG);
        graphics.clear();

        graphics.set_pen(WHITE);
        graphics.set_font(&font8);

        // Use stringstream to format the temperature string
        std::stringstream st;
        st << std::fixed << std::setprecision(1) << "Temperature: " << temperature;

        std::string formattedTemperature = st.str();

        std::stringstream sh;
        sh << std::fixed << std::setprecision(1) << "Humidity: " << humidity;

        std::string formattedHumidity = sh.str();

        // Render the formatted string to the display at a specific position
        graphics.text(formattedTemperature, Point(10, 120), 220); // Assuming Point is a valid class for coordinates
        graphics.text(formattedHumidity, Point(10, 180), 220);    // Assuming Point is a valid class for coordinates

        st7789.update(&graphics);

        sleep_ms(1000);
    }
}