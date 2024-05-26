#include "CppUTest/TestHarness.h"
#include <CppUTestExt/MockSupport.h>
#include "environment_sensor.hpp"
#include "i2c_bus.hpp"

static I2CBus *i2cBus;
static EnvironmentSensor *environmentSensor;
static I2CDevice *i2cDevice;


TEST_GROUP(EnvironmentSensorTestGroup)
{
    void setup()
    {
        i2cBus = new I2CBus();
        i2cDevice = new I2CDevice(i2cBus, 0x31);
        environmentSensor = new EnvironmentSensor(i2cDevice);
    }

    void teardown()
    {   
        mock().checkExpectations();
        mock().clear();
        delete environmentSensor;
        delete i2cDevice;
        delete i2cBus;
    }
};

TEST(EnvironmentSensorTestGroup, EnvironmentSensorConstructor) {



    EnvironmentSensor *environment_sensor = new EnvironmentSensor(i2cDevice);


    delete environment_sensor;
}

TEST(EnvironmentSensorTestGroup, EnvironmentSensorReadTemperature) {

    uint8_t written_data[3] = {0xAC, 0x33, 0x00};

    mock()
        .expectOneCall("I2CDevice::write")
        .withParameter("length", 3)
        .withOutputParameterReturning("data", written_data, 3)
        .andReturnValue(I2C_OK);

    uint8_t read_data[7] = {0x00, 0x80, 0x00, 0x05, 0x99, 0x99, 0x99}; // Corrected values for 50% humidity and 20°C

    mock()
        .expectOneCall("I2CDevice::read")
        .withParameter("length", 6)
        .withOutputParameterReturning("data", read_data, 6)
        .andReturnValue(I2C_OK);

    double temperatureReading;
    double humidityReading;

    environmentSensor->readTemperatureHumidity(&temperatureReading, &humidityReading);

    DOUBLES_EQUAL(20.0, temperatureReading, 0.01);
    DOUBLES_EQUAL(50.0, humidityReading, 0.01);
}