#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include "thermostat.hpp"
#include "environment_sensor.hpp"
#include "thermostat_common.hpp"
#include "hvac.hpp"
#include <iostream>

static Thermostat *thermostat;
static EnvironmentSensor *environmentSensor;
static TemperatureController *temperatureController;
static HVAC *hvac;
static Wifi *wifi;
static Mqtt *mqtt;
static Watchdog *watchdog;
static Configuration *config;

TEST_GROUP(ThermostatTestGroupInit){
    void setup(){
        environmentSensor = new EnvironmentSensor(NULL);
temperatureController = new TemperatureController();
hvac = new HVAC(NULL, NULL, NULL);
wifi = new Wifi();
mqtt = new Mqtt(NULL);
watchdog = new Watchdog();
config = new Configuration();
}

void teardown()
{
   delete environmentSensor;
   delete temperatureController;
   delete hvac;
   delete wifi;
   delete mqtt;
   delete watchdog;
   delete config;

   mock().checkExpectations();
   mock().clear();
}
}
;

TEST(ThermostatTestGroupInit, ThermostatInitalize)
{
   double temperature = 20;
   double humidity = 50;

   mock().expectOneCall("EnvironmentSensor::readTemperatureHumidity").ignoreOtherParameters().withOutputParameterReturning("temperature", &temperature, sizeof(double)).withOutputParameterReturning("humidity", &humidity, sizeof(double)).andReturnValue(ENVIRONMENT_SENSOR_OK);
   mock().expectOneCall("Wifi::initialize").ignoreOtherParameters().andReturnValue(THERMOSTAT_OK);
   mock().expectOneCall("Mqtt::initialize").andReturnValue(THERMOSTAT_OK);
   mock().expectOneCall("Watchdog::initialize").andReturnValue(THERMOSTAT_OK);

   Thermostat *testInit = new Thermostat(environmentSensor, temperatureController, hvac, wifi, mqtt, watchdog, config);
   ENUMS_EQUAL_INT(THERMOSTAT_OK, testInit->initialize());
   CHECK_TRUE(testInit->isInitialized());
   delete testInit;
}

TEST(ThermostatTestGroupInit, ThermostatInitalize_NULL_EnvironmentSensor)
{
   Thermostat *testInitalize = new Thermostat(NULL, temperatureController, hvac, wifi, mqtt, watchdog, config);
   ENUMS_EQUAL_INT(THERMOSTAT_INIT_FAILED, testInitalize->initialize());
   CHECK_FALSE(testInitalize->isInitialized());
   char messageBuffer[256];
   testInitalize->getCurrentErrorMessage(messageBuffer);
   STRCMP_EQUAL("Environment Sensor is NULL", messageBuffer);
   delete testInitalize;
}

TEST(ThermostatTestGroupInit, ThermostatInitalize_NULL_TemperatureController)
{
   Thermostat *testInitalize = new Thermostat(environmentSensor, NULL, hvac, wifi, mqtt, watchdog, config);
   ENUMS_EQUAL_INT(THERMOSTAT_INIT_FAILED, testInitalize->initialize());
   CHECK_FALSE(testInitalize->isInitialized());
   char messageBuffer[256];
   testInitalize->getCurrentErrorMessage(messageBuffer);
   STRCMP_EQUAL("Temperature Controller is NULL", messageBuffer);
   delete testInitalize;
}

TEST(ThermostatTestGroupInit, ThermostatInitalize_NULL_hvac)
{
   Thermostat *testInitalize = new Thermostat(environmentSensor, temperatureController, NULL, wifi, mqtt, watchdog, config);
   ENUMS_EQUAL_INT(THERMOSTAT_INIT_FAILED, testInitalize->initialize());
   CHECK_FALSE(testInitalize->isInitialized());
   char messageBuffer[256];
   testInitalize->getCurrentErrorMessage(messageBuffer);
   STRCMP_EQUAL("HVAC is NULL", messageBuffer);
   delete testInitalize;
}

TEST(ThermostatTestGroupInit, ThermostatInitalize_NULL_wifi)
{
   Thermostat *testInitalize = new Thermostat(environmentSensor, temperatureController, hvac, NULL, mqtt, watchdog, config);
   ENUMS_EQUAL_INT(THERMOSTAT_INIT_FAILED, testInitalize->initialize());
   CHECK_FALSE(testInitalize->isInitialized());
   char messageBuffer[256];
   testInitalize->getCurrentErrorMessage(messageBuffer);
   STRCMP_EQUAL("Wifi is NULL", messageBuffer);
   delete testInitalize;
}

TEST(ThermostatTestGroupInit, ThermostatInitalize_NULL_mqtt)
{
   Thermostat *testInitalize = new Thermostat(environmentSensor, temperatureController, hvac, wifi, NULL, watchdog, config);
   ENUMS_EQUAL_INT(THERMOSTAT_INIT_FAILED, testInitalize->initialize());
   CHECK_FALSE(testInitalize->isInitialized());
   char messageBuffer[256];
   testInitalize->getCurrentErrorMessage(messageBuffer);
   STRCMP_EQUAL("Mqtt is NULL", messageBuffer);
   delete testInitalize;
}

TEST(ThermostatTestGroupInit, ThermostatInitalize_NULL_watchdog)
{
   Thermostat *testInitalize = new Thermostat(environmentSensor, temperatureController, hvac, wifi, mqtt, NULL, config);
   ENUMS_EQUAL_INT(THERMOSTAT_INIT_FAILED, testInitalize->initialize());
   CHECK_FALSE(testInitalize->isInitialized());
   char messageBuffer[256];
   testInitalize->getCurrentErrorMessage(messageBuffer);
   STRCMP_EQUAL("Watchdog is NULL", messageBuffer);
   delete testInitalize;
}

TEST(ThermostatTestGroupInit, ThermostatInitalize_NULL_configuration)
{
   Thermostat *testInitalize = new Thermostat(environmentSensor, temperatureController, hvac, wifi, mqtt, watchdog, NULL);
   ENUMS_EQUAL_INT(THERMOSTAT_INIT_FAILED, testInitalize->initialize());
   CHECK_FALSE(testInitalize->isInitialized());
   char messageBuffer[256];
   testInitalize->getCurrentErrorMessage(messageBuffer);
   STRCMP_EQUAL("Configuration is NULL", messageBuffer);
   delete testInitalize;
}