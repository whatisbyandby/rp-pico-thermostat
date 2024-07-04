#include "environment_sensor.hpp"
#include "thermostat_common.hpp"

EnvironmentSensor::EnvironmentSensor()
{
    
}

EnvironmentSensor::~EnvironmentSensor()
{
}

ThermostatError EnvironmentSensor::initialize(I2CDevice *i2cDevice) {
    this->i2cDevice = i2cDevice;
    return THERMOSTAT_OK;
}

ThermostatError EnvironmentSensor::readTemperatureHumidity(double *temperature, double *humidity)
{
    uint8_t write_data[3] = {0xAC, 0x33, 0x00};
    i2cDevice->write(write_data, 3);

    uint8_t read_buffer[6] = {0x00};
    i2cDevice->read(read_buffer, 6);

    uint32_t raw_humidity = (read_buffer[1] << 12) | (read_buffer[2] << 4) | (read_buffer[3] >> 4);
    uint32_t raw_temperature = ((read_buffer[3] & 0x0F) << 16) | (read_buffer[4] << 8) | read_buffer[5];

    double humidity_calculated = (double) raw_humidity / 1048576.0 * 100.0; // 2^20 = 1048576
    double temperature_calculated = (double) raw_temperature / 1048576.0 * 200.0 - 50.0; // Range from -50°C to 150°C

    *humidity = humidity_calculated;
    *temperature = temperature_calculated;

    return THERMOSTAT_OK;
}
