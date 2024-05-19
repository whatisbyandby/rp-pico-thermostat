#include "environment_sensor.hpp"
#include "i2c_bus.hpp"
#include "pico/stdlib.h"
#include <stdio.h>

int main() {
   stdio_init_all();

    I2CBus i2cBus;
    i2cBus.initialize();
    I2CDevice i2cDevice(&i2cBus, 0x38);
    EnvironmentSensor environmentSensor(&i2cDevice);


    while (true) {

        double temperatureReading;
        double humidityReading;

        environmentSensor.readTemperatureHumidity(&temperatureReading, &humidityReading);

        printf("Temperature: %f\n", temperatureReading);
        printf("Humidity: %f\n", humidityReading);
        sleep_ms(1000);
    }
}