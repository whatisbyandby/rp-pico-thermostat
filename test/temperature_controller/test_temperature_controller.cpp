#include "CppUTest/TestHarness.h"
#include "temperature_controller.hpp"

static TemperatureController *temperatureController;

TEST_GROUP(TemperatureControllerTestGroup)
{
    void setup()
    {
        temperatureController = new TemperatureController();
        temperatureController->initialize();
    }

    void teardown()
    {
        delete temperatureController;
    }
};

TEST(TemperatureControllerTestGroup, TemperatureControllerConstructor)
{
    TemperatureController *testController = new TemperatureController();

    testController->initialize();

    DOUBLES_EQUAL(20.0, testController->getTargetTemperature(), 0.01);
    DOUBLES_EQUAL(1.0, testController->getTemperatureRange(), 0.01);

    delete testController;
}

TEST(TemperatureControllerTestGroup, UpdateTargetTemperature)
{
    CHECK_EQUAL(THERMOSTAT_OK, temperatureController->setTargetTemperature(25.0));
    DOUBLES_EQUAL(25.0, temperatureController->getTargetTemperature(), 0.01);
}

TEST(TemperatureControllerTestGroup, UpdateTargetTemperature_Invalid)
{   

   ENUMS_EQUAL_INT(THERMOSTAT_OK, temperatureController->setTargetTemperature(25.0));
   DOUBLES_EQUAL(25.0, temperatureController->getTargetTemperature(), 0.01);

   ENUMS_EQUAL_INT(THERMOSTAT_OK, temperatureController->setTargetTemperature(35.0));
   DOUBLES_EQUAL(35.0, temperatureController->getTargetTemperature(), 0.01);

   ENUMS_EQUAL_INT(THERMOSTAT_OK, temperatureController->setTargetTemperature(7.0));
   DOUBLES_EQUAL(7.0, temperatureController->getTargetTemperature(), 0.01);

   ENUMS_EQUAL_INT(THERMOSTAT_OK, temperatureController->setTargetTemperature(25.0));
   DOUBLES_EQUAL(25.0, temperatureController->getTargetTemperature(), 0.01);


   ENUMS_EQUAL_INT(THERMOSTAT_INVALID_INPUT, temperatureController->setTargetTemperature(6.9));
   DOUBLES_EQUAL(25.0, temperatureController->getTargetTemperature(), 0.01);

   ENUMS_EQUAL_INT(THERMOSTAT_INVALID_INPUT, temperatureController->setTargetTemperature(35.1));
   DOUBLES_EQUAL(25.0, temperatureController->getTargetTemperature(), 0.01);
}

TEST(TemperatureControllerTestGroup, UpdateTemperatureRange)
{
    CHECK_EQUAL(THERMOSTAT_OK, temperatureController->setTemperatureRange(1.0));
    DOUBLES_EQUAL(1.0, temperatureController->getTemperatureRange(), 0.01);
}

TEST(TemperatureControllerTestGroup, UpdateTemperatureRange_Invalid)
{

    temperatureController->setTemperatureRange(1.0);

    CHECK_EQUAL(THERMOSTAT_INVALID_INPUT, temperatureController->setTemperatureRange(2.1));
    DOUBLES_EQUAL(1.0, temperatureController->getTemperatureRange(), 0.01);

    CHECK_EQUAL(THERMOSTAT_INVALID_INPUT, temperatureController->setTemperatureRange(0.4));
    DOUBLES_EQUAL(1.0, temperatureController->getTemperatureRange(), 0.01);
}

TEST(TemperatureControllerTestGroup, CheckTemperature)
{
    temperatureController->setTargetTemperature(25.0);

    CHECK_EQUAL(IN_RANGE, temperatureController->checkTemperature(25.0));
    CHECK_EQUAL(UNDER_TEMPERATURE, temperatureController->checkTemperature(23.9));
    CHECK_EQUAL(OVER_TEMPERATURE, temperatureController->checkTemperature(26.1));
    CHECK_EQUAL(UNDER_TEMPERATURE_IN_RANGE, temperatureController->checkTemperature(24.1));
    CHECK_EQUAL(OVER_TEMPERATURE_IN_RANGE, temperatureController->checkTemperature(25.9));
}