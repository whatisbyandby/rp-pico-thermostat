#include "CppUTestExt/MockSupport.h"
#include "environment_sensor.hpp"


EnvironmentSensor::EnvironmentSensor(I2CDevice *i2cDevice) {
    this->i2cDevice = i2cDevice;
}

EnvironmentSensor::~EnvironmentSensor() {
}

EnvironmentSensorError EnvironmentSensor::readTemperatureHumidity(double *temperature, double *humidity) {
    return (EnvironmentSensorError) mock()
        .actualCall("EnvironmentSensor::readTemperatureHumidity")
        .withOutputParameter("temperature", temperature)
        .withOutputParameter("humidity", humidity)
        .returnIntValueOrDefault(ENVIRONMENT_SENSOR_OK);
}



