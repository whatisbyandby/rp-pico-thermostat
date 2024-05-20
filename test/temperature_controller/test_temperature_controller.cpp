#include "CppUTest/TestHarness.h"
#include "temperature_controller.hpp"

static TemperatureController *temperatureController;

TEST_GROUP(TemperatureControllerTestGroup)
{
    void setup()
    {
        temperatureController = new TemperatureController();
    }

    void teardown()
    {
        delete temperatureController;
    }
};

TEST(TemperatureControllerTestGroup, TemperatureControllerConstructor)
{
    TemperatureController *testController = new TemperatureController();

    delete testController;
}

TEST(TemperatureControllerTestGroup, UpdateTargetTemperature)
{
    CHECK_EQUAL(THERMOSTAT_OK, temperatureController->setTargetTemperature(25.0));
    DOUBLES_EQUAL(25.0, temperatureController->getTargetTemperature(), 0.01);
}

TEST(TemperatureControllerTestGroup, UpdateTargetTemperature_Invalid)
{   

    temperatureController->setTargetTemperature(25.0);

    CHECK_EQUAL(THERMOSTAT_INVALID_INPUT, temperatureController->setTargetTemperature(31.0));
    DOUBLES_EQUAL(25.0, temperatureController->getTargetTemperature(), 0.01);

    CHECK_EQUAL(THERMOSTAT_INVALID_INPUT, temperatureController->setTargetTemperature(9.0));
    DOUBLES_EQUAL(25.0, temperatureController->getTargetTemperature(), 0.01);
}