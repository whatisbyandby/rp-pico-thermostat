#include "CppUTestExt/MockSupport.h"
#include "environment_sensor.hpp"


EnvironmentSensor::EnvironmentSensor() {
}

EnvironmentSensor::~EnvironmentSensor() {
}


ThermostatError EnvironmentSensor::readTemperatureHumidity(double *temperature, double *humidity) {
    return (ThermostatError) mock()
        .actualCall("EnvironmentSensor::readTemperatureHumidity")
        .withOutputParameter("temperature", temperature)
        .withOutputParameter("humidity", humidity)
        .returnIntValueOrDefault(THERMOSTAT_OK);
}



