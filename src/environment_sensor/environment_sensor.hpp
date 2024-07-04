#include "i2c_bus.hpp"
#include "thermostat_common.hpp"

#ifndef ENVIRONMENT_SENSOR_HPP
#define ENVIRONMENT_SENSOR_HPP

class EnvironmentSensor {
    public:
        EnvironmentSensor();
        ~EnvironmentSensor();

        ThermostatError initialize(I2CDevice *i2cDevice);

        ThermostatError readTemperatureHumidity(double *temperature, double *humidity);
    private:
        I2CDevice *i2cDevice;
};

#endif // ENVIRONMENT_SENSOR_HPP