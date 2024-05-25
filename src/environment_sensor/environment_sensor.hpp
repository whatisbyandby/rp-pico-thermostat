#include "i2c_bus.hpp"

#ifndef ENVIRONMENT_SENSOR_HPP
#define ENVIRONMENT_SENSOR_HPP

typedef enum EnvironmentSensorError {
    ENVIRONMENT_SENSOR_READ_ERROR,
    ENVIRONMENT_SENSOR_WRITE_ERROR,
    ENVIRONMENT_SENSOR_OK
} EnvironmentSensorError;

class EnvironmentSensor {
    public:
        EnvironmentSensor(I2CDevice *i2cDevice);
        ~EnvironmentSensor();

        EnvironmentSensorError readTemperatureHumidity(double *temperature, double *humidity);
    private:
        I2CDevice *i2cDevice;
};

#endif // ENVIRONMENT_SENSOR_HPP