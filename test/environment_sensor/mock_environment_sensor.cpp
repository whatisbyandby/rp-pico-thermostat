#include "environment_sensor.hpp"


EnvironmentSensor::EnvironmentSensor(I2CDevice *i2cDevice) {
    this->i2cDevice = i2cDevice;
}

