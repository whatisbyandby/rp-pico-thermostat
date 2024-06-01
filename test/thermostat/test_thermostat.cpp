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

TEST_GROUP(ThermostatTestGroup)
{
    void setup()
   {
      environmentSensor = new EnvironmentSensor(NULL);
      temperatureController = new TemperatureController();
      hvac = new HVAC(NULL, NULL, NULL);
      thermostat = new Thermostat(environmentSensor, temperatureController, hvac);
   }

   void teardown()
   {
      mock().checkExpectations();
      mock().clear();
      delete thermostat;
      delete environmentSensor;
      delete temperatureController;
      delete hvac;
   }
};


TEST(ThermostatTestGroup, ThermostatConstructor)
{
   Thermostat *thermostatConstructor = new Thermostat(NULL, NULL, NULL);

   CHECK_EQUAL(FAHRENHEIT, thermostat->getTemperatureUnits());
   CHECK_FALSE(thermostat->isInitialized());
   CHECK_EQUAL(OFF, thermostat->getMode());

   delete thermostatConstructor;
}

TEST(ThermostatTestGroup, ThermostatInitalize)
{
   CHECK_EQUAL(THERMOSTAT_OK, thermostat->initialize());
   CHECK_TRUE(thermostat->isInitialized());
}

TEST(ThermostatTestGroup, ThermostatInitalize_NULL){
   Thermostat *testInitalize = new Thermostat(NULL, NULL, NULL);
   CHECK_EQUAL(THERMOSTAT_ERROR, testInitalize->initialize());
   CHECK_FALSE(testInitalize->isInitialized());
   delete testInitalize;
}

TEST(ThermostatTestGroup, UpdateTargetTemperatureCelsius) {
   thermostat->setTemperatureUnits(CELSIUS);

   CHECK_EQUAL(THERMOSTAT_OK, thermostat->setTargetTemperature(25.0));
   DOUBLES_EQUAL(25.0, thermostat->getTargetTemperature(), 0.01);

   CHECK_EQUAL(THERMOSTAT_INVALID_INPUT, thermostat->setTargetTemperature(9.0));
   DOUBLES_EQUAL(25.0, thermostat->getTargetTemperature(), 0.01);

   CHECK_EQUAL(THERMOSTAT_INVALID_INPUT, thermostat->setTargetTemperature(31.0));
   DOUBLES_EQUAL(25.0, thermostat->getTargetTemperature(), 0.01);
}

TEST(ThermostatTestGroup, UpdateTargetTemperatureFAHRENHEIT) {
   thermostat->setTemperatureUnits(FAHRENHEIT);

   CHECK_EQUAL(THERMOSTAT_OK, thermostat->setTargetTemperature(60.0));
   DOUBLES_EQUAL(60.0, thermostat->getTargetTemperature(), 0.01);

   CHECK_EQUAL(THERMOSTAT_INVALID_INPUT, thermostat->setTargetTemperature(48.0));
   DOUBLES_EQUAL(60.0, thermostat->getTargetTemperature(), 0.01);

   CHECK_EQUAL(THERMOSTAT_INVALID_INPUT, thermostat->setTargetTemperature(88.0));
   DOUBLES_EQUAL(60.0, thermostat->getTargetTemperature(), 0.01);
}


TEST(ThermostatTestGroup, UpdateTemperatureUnits)
{
   CHECK_EQUAL(THERMOSTAT_OK, thermostat->setTemperatureUnits(CELSIUS));
   CHECK_EQUAL(CELSIUS, thermostat->getTemperatureUnits());

   CHECK_EQUAL(THERMOSTAT_OK, thermostat->setTemperatureUnits(FAHRENHEIT));
   CHECK_EQUAL(FAHRENHEIT, thermostat->getTemperatureUnits());
}

TEST(ThermostatTestGroup, UpdateMode_Valid) {
   CHECK_EQUAL(THERMOSTAT_OK, thermostat->setMode(HEATING));
   CHECK_EQUAL(HEATING, thermostat->getMode());

   CHECK_EQUAL(THERMOSTAT_OK, thermostat->setMode(COOLING));
   CHECK_EQUAL(COOLING, thermostat->getMode());

   CHECK_EQUAL(THERMOSTAT_OK, thermostat->setMode(FAN_ONLY));
   CHECK_EQUAL(FAN_ONLY, thermostat->getMode());

   CHECK_EQUAL(THERMOSTAT_OK, thermostat->setMode(OFF));
   CHECK_EQUAL(OFF, thermostat->getMode());
}

TEST(ThermostatTestGroup, UpdateMode_Invalid) {
   int badValue = 47;
   CHECK_EQUAL(THERMOSTAT_INVALID_INPUT, thermostat->setMode((ThermostatMode) badValue));
   CHECK_EQUAL(OFF, thermostat->getMode());
}

TEST(ThermostatTestGroup, GetDesiredHVACState_ModeHeating) {

   thermostat->setMode(HEATING);

   CHECK_EQUAL(HEATER_ON, thermostat->getDesiredHVACState(UNDER_TEMPERATURE, ALL_OFF));
   CHECK_EQUAL(ALL_OFF, thermostat->getDesiredHVACState(UNDER_TEMPERATURE_IN_RANGE, ALL_OFF));
   CHECK_EQUAL(HEATER_ON, thermostat->getDesiredHVACState(UNDER_TEMPERATURE_IN_RANGE, HEATER_ON));
   CHECK_EQUAL(ALL_OFF, thermostat->getDesiredHVACState(IN_RANGE, HEATER_ON));
   CHECK_EQUAL(ALL_OFF, thermostat->getDesiredHVACState(OVER_TEMPERATURE_IN_RANGE, HEATER_ON));
   CHECK_EQUAL(ALL_OFF, thermostat->getDesiredHVACState(OVER_TEMPERATURE, HEATER_ON));
}

TEST(ThermostatTestGroup, GetDesiredHVACState_ModeCooling) {

   thermostat->setMode(COOLING);

   CHECK_EQUAL(COOLER_ON, thermostat->getDesiredHVACState(OVER_TEMPERATURE, ALL_OFF));
   CHECK_EQUAL(ALL_OFF, thermostat->getDesiredHVACState(OVER_TEMPERATURE_IN_RANGE, ALL_OFF));
   CHECK_EQUAL(COOLER_ON, thermostat->getDesiredHVACState(OVER_TEMPERATURE_IN_RANGE, COOLER_ON));
   CHECK_EQUAL(ALL_OFF, thermostat->getDesiredHVACState(IN_RANGE, COOLER_ON));
   CHECK_EQUAL(ALL_OFF, thermostat->getDesiredHVACState(UNDER_TEMPERATURE_IN_RANGE, COOLER_ON));
   CHECK_EQUAL(ALL_OFF, thermostat->getDesiredHVACState(UNDER_TEMPERATURE, COOLER_ON));
}

TEST(ThermostatTestGroup, GetDesiredHVACState_ModeFanOnly) {

   thermostat->setMode(FAN_ONLY);
   
   CHECK_EQUAL(FAN_ON, thermostat->getDesiredHVACState(IN_RANGE, ALL_OFF));
   CHECK_EQUAL(FAN_ON, thermostat->getDesiredHVACState(OVER_TEMPERATURE, ALL_OFF));
   CHECK_EQUAL(FAN_ON, thermostat->getDesiredHVACState(UNDER_TEMPERATURE, ALL_OFF));
}

TEST(ThermostatTestGroup, GetDesiredHVACState_ModeOff) {

   thermostat->setMode(OFF);

   CHECK_EQUAL(ALL_OFF, thermostat->getDesiredHVACState(IN_RANGE, ALL_OFF));
   CHECK_EQUAL(ALL_OFF, thermostat->getDesiredHVACState(OVER_TEMPERATURE, ALL_OFF));
   CHECK_EQUAL(ALL_OFF, thermostat->getDesiredHVACState(UNDER_TEMPERATURE, ALL_OFF));
}

TEST(ThermostatTestGroup, GetDesiredHVACState_ModeError) {

   thermostat->setMode(ERROR);

   CHECK_EQUAL(ALL_OFF, thermostat->getDesiredHVACState(IN_RANGE, ALL_OFF));
   CHECK_EQUAL(ALL_OFF, thermostat->getDesiredHVACState(OVER_TEMPERATURE, ALL_OFF));
   CHECK_EQUAL(ALL_OFF, thermostat->getDesiredHVACState(UNDER_TEMPERATURE, ALL_OFF));
}

TEST(ThermostatTestGroup, UpdateThermostatMode) {
   CHECK_EQUAL(THERMOSTAT_OK, thermostat->setMode(HEATING));
   CHECK_EQUAL(HEATING, thermostat->getMode());
}

TEST(ThermostatTestGroup, UpdateThermostat_ExpectHeaterOn_UnderTemp) {


   thermostat->setMode(HEATING);
   temperatureController->setTargetTemperature(25.0);

   double temperature = 20.0;
   double humidity = 50.0;

   mock()
      .expectOneCall("EnvironmentSensor::readTemperatureHumidity")
      .withOutputParameterReturning("temperature", &temperature, sizeof(double))
      .withOutputParameterReturning("humidity", &humidity, sizeof(double))
      .andReturnValue(ENVIRONMENT_SENSOR_OK);

   mock()
      .expectOneCall("HVAC::getCurrentState")
      .andReturnValue(ALL_OFF);

   mock()
      .expectOneCall("HVAC::setDesiredState")
      .withParameter("state", HEATER_ON)
      .andReturnValue(THERMOSTAT_OK);

   CHECK_EQUAL(THERMOSTAT_OK, thermostat->update());
   
}

TEST(ThermostatTestGroup, UpdateThermostat_ExpectHeaterOn_InRange) {

   thermostat->setMode(HEATING);
   temperatureController->setTargetTemperature(20);

   double temperature = 19.9;
   double humidity = 50.0;

   mock()
      .expectOneCall("EnvironmentSensor::readTemperatureHumidity")
      .withOutputParameterReturning("temperature", &temperature, sizeof(double))
      .withOutputParameterReturning("humidity", &humidity, sizeof(double))
      .andReturnValue(ENVIRONMENT_SENSOR_OK);

   mock()
      .expectOneCall("HVAC::getCurrentState")
      .andReturnValue(HEATER_ON);

   mock()
      .expectOneCall("HVAC::setDesiredState")
      .withParameter("state", HEATER_ON)
      .andReturnValue(THERMOSTAT_OK);

   CHECK_EQUAL(THERMOSTAT_OK, thermostat->update());
   
}

TEST(ThermostatTestGroup, UpdateThermostat_ExpectAllOff_OverTemp) {

   thermostat->setMode(HEATING);
   temperatureController->setTargetTemperature(20);

   double temperature = 20.1;
   double humidity = 50.0;

   mock()
      .expectOneCall("EnvironmentSensor::readTemperatureHumidity")
      .withOutputParameterReturning("temperature", &temperature, sizeof(double))
      .withOutputParameterReturning("humidity", &humidity, sizeof(double))
      .andReturnValue(ENVIRONMENT_SENSOR_OK);

   mock()
      .expectOneCall("HVAC::getCurrentState")
      .andReturnValue(HEATER_ON);

   mock()
      .expectOneCall("HVAC::setDesiredState")
      .withParameter("state", ALL_OFF)
      .andReturnValue(THERMOSTAT_OK);

   CHECK_EQUAL(THERMOSTAT_OK, thermostat->update());
   
}

TEST(ThermostatTestGroup, PrintState) {
   thermostat->setMode(HEATING);
   thermostat->setTemperatureUnits(CELSIUS);
   thermostat->setTargetTemperature(25.0);

   // initalize an empty string using std::string
   std::string state;

   mock().expectOneCall("HVAC::getCurrentState")
      .andReturnValue(HEATER_ON);

   thermostat->printState(&state);
   std::cout << state << std::endl;

}
