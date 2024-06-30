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


      double temperature = 20;
      double humidity = 50;

      mock().expectOneCall("EnvironmentSensor::readTemperatureHumidity")
         .withOutputParameterReturning("temperature", &temperature, sizeof(double))
         .withOutputParameterReturning("humidity", &humidity, sizeof(double))
         .andReturnValue(ENVIRONMENT_SENSOR_OK);
      thermostat->initialize();
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

   ENUMS_EQUAL_INT(FAHRENHEIT, thermostat->getTemperatureUnits());
   CHECK_FALSE(thermostatConstructor->isInitialized());
   ENUMS_EQUAL_INT(OFF, thermostat->getMode());

   delete thermostatConstructor;
}


TEST(ThermostatTestGroup, ThermostatInitalize)
{

   double temperature = 20;
   double humidity = 50;

   mock().expectOneCall("EnvironmentSensor::readTemperatureHumidity")
      .ignoreOtherParameters()
      .withOutputParameterReturning("temperature", &temperature, sizeof(double))
      .withOutputParameterReturning("humidity", &humidity, sizeof(double))
      .andReturnValue(THERMOSTAT_ERROR);
   Thermostat *testInit = new Thermostat(environmentSensor, temperatureController, hvac);
   ENUMS_EQUAL_INT(THERMOSTAT_OK, testInit->initialize());
   CHECK_TRUE(testInit->isInitialized());
   delete testInit;
}

TEST(ThermostatTestGroup, ThermostatInitalize_NULL_EnvironmentSensor){
   Thermostat *testInitalize = new Thermostat(NULL, NULL, NULL);
   ENUMS_EQUAL_INT(THERMOSTAT_INIT_FAILED, testInitalize->initialize());
   CHECK_FALSE(testInitalize->isInitialized());
   char messageBuffer[256];
   testInitalize->getCurrentErrorMessage(messageBuffer);
   STRCMP_EQUAL("Environment Sensor is NULL", messageBuffer);
   delete testInitalize;
}

TEST(ThermostatTestGroup, ThermostatInitalize_NULL_TemperatureController){
   Thermostat *testInitalize = new Thermostat(environmentSensor, NULL, NULL);
   ENUMS_EQUAL_INT(THERMOSTAT_INIT_FAILED, testInitalize->initialize());
   CHECK_FALSE(testInitalize->isInitialized());
   char messageBuffer[256];
   testInitalize->getCurrentErrorMessage(messageBuffer);
   STRCMP_EQUAL("Temperature Controller is NULL", messageBuffer);
   delete testInitalize;
}

TEST(ThermostatTestGroup, ThermostatInitalize_NULL_hvac){
   Thermostat *testInitalize = new Thermostat(environmentSensor, temperatureController, NULL);
   ENUMS_EQUAL_INT(THERMOSTAT_INIT_FAILED, testInitalize->initialize());
   CHECK_FALSE(testInitalize->isInitialized());
   char messageBuffer[256];
   testInitalize->getCurrentErrorMessage(messageBuffer);
   STRCMP_EQUAL("HVAC is NULL", messageBuffer);
   delete testInitalize;
}

TEST(ThermostatTestGroup, ThermostatSensorError)
{	

   double temperature = -1;
   double humidity = -1;

	mock().expectOneCall("EnvironmentSensor::readTemperatureHumidity")
      .withOutputParameterReturning("temperature", &temperature, sizeof(double))
      .withOutputParameterReturning("humidity", &humidity, sizeof(double))
      .andReturnValue(ENVIRONMENT_SENSOR_READ_ERROR);
   
   Thermostat *testInit = new Thermostat(environmentSensor, temperatureController, hvac);
	ENUMS_EQUAL_INT(THERMOSTAT_SENSOR_ERROR, testInit->initialize());
   CHECK_FALSE(testInit->isInitialized());
   ENUMS_EQUAL_INT(THERMOSTAT_SENSOR_ERROR, testInit->getCurrentError());
   char messageBuffer[256];
   testInit->getCurrentErrorMessage(messageBuffer);
   STRCMP_EQUAL("Temperature or Humidity values are under a reasonable value", messageBuffer);
   delete testInit;

}

TEST(ThermostatTestGroup, ThermostatSensorInvalid)
{	

   double temperature = -1;
   double humidity = -1;

	mock().expectOneCall("EnvironmentSensor::readTemperatureHumidity")
      .withOutputParameterReturning("temperature", &temperature, sizeof(double))
      .withOutputParameterReturning("humidity", &humidity, sizeof(double))
      .andReturnValue(ENVIRONMENT_SENSOR_OK);
   
   Thermostat *testInit = new Thermostat(environmentSensor, temperatureController, hvac);
	ENUMS_EQUAL_INT(THERMOSTAT_SENSOR_ERROR, testInit->initialize());
   CHECK_FALSE(testInit->isInitialized());
   ENUMS_EQUAL_INT(THERMOSTAT_SENSOR_ERROR, testInit->getCurrentError());
   delete testInit;

}


// ============ Update Temperature Units

TEST(ThermostatTestGroup, UpdateTargetTemperatureCelsius) {
   thermostat->setTemperatureUnits(CELSIUS);

   ENUMS_EQUAL_INT(THERMOSTAT_OK, thermostat->setTargetTemperature(25.0));
   DOUBLES_EQUAL(25.0, thermostat->getTargetTemperature(), 0.01);

   ENUMS_EQUAL_INT(THERMOSTAT_OK, thermostat->setTargetTemperature(35.0));
   DOUBLES_EQUAL(35.0, thermostat->getTargetTemperature(), 0.01);

   ENUMS_EQUAL_INT(THERMOSTAT_OK, thermostat->setTargetTemperature(7.0));
   DOUBLES_EQUAL(7.0, thermostat->getTargetTemperature(), 0.01);

   ENUMS_EQUAL_INT(THERMOSTAT_OK, thermostat->setTargetTemperature(25.0));
   DOUBLES_EQUAL(25.0, thermostat->getTargetTemperature(), 0.01);


   ENUMS_EQUAL_INT(THERMOSTAT_INVALID_INPUT, thermostat->setTargetTemperature(6.9));
   DOUBLES_EQUAL(25.0, thermostat->getTargetTemperature(), 0.01);

   ENUMS_EQUAL_INT(THERMOSTAT_INVALID_INPUT, thermostat->setTargetTemperature(35.1));
   DOUBLES_EQUAL(25.0, thermostat->getTargetTemperature(), 0.01);
}

TEST(ThermostatTestGroup, UpdateTargetTemperatureFAHRENHEIT) {
   thermostat->setTemperatureUnits(FAHRENHEIT);

   ENUMS_EQUAL_INT(THERMOSTAT_OK, thermostat->setTargetTemperature(60.0));
   DOUBLES_EQUAL(60.0, thermostat->getTargetTemperature(), 0.01);

   ENUMS_EQUAL_INT(THERMOSTAT_OK, thermostat->setTargetTemperature(44.6));
   DOUBLES_EQUAL(44.6, thermostat->getTargetTemperature(), 0.01);

   ENUMS_EQUAL_INT(THERMOSTAT_OK, thermostat->setTargetTemperature(95.0));
   DOUBLES_EQUAL(95, thermostat->getTargetTemperature(), 0.01);

   ENUMS_EQUAL_INT(THERMOSTAT_OK, thermostat->setTargetTemperature(60.0));
   DOUBLES_EQUAL(60.0, thermostat->getTargetTemperature(), 0.01);

   ENUMS_EQUAL_INT(THERMOSTAT_INVALID_INPUT, thermostat->setTargetTemperature(44.5));
   DOUBLES_EQUAL(60.0, thermostat->getTargetTemperature(), 0.01);


   ENUMS_EQUAL_INT(THERMOSTAT_INVALID_INPUT, thermostat->setTargetTemperature(95.1));
   DOUBLES_EQUAL(60.0, thermostat->getTargetTemperature(), 0.01);
}


TEST(ThermostatTestGroup, UpdateTemperatureUnits)
{
   ENUMS_EQUAL_INT(THERMOSTAT_OK, thermostat->setTemperatureUnits(CELSIUS));
   ENUMS_EQUAL_INT(CELSIUS, thermostat->getTemperatureUnits());

   ENUMS_EQUAL_INT(THERMOSTAT_OK, thermostat->setTemperatureUnits(FAHRENHEIT));
   ENUMS_EQUAL_INT(FAHRENHEIT, thermostat->getTemperatureUnits());
}

TEST(ThermostatTestGroup, UpdateMode_Valid) {
   ENUMS_EQUAL_INT(THERMOSTAT_OK, thermostat->setMode(HEATING));
   ENUMS_EQUAL_INT(HEATING, thermostat->getMode());

   ENUMS_EQUAL_INT(THERMOSTAT_OK, thermostat->setMode(COOLING));
   ENUMS_EQUAL_INT(COOLING, thermostat->getMode());

   ENUMS_EQUAL_INT(THERMOSTAT_OK, thermostat->setMode(FAN_ONLY));
   ENUMS_EQUAL_INT(FAN_ONLY, thermostat->getMode());

   ENUMS_EQUAL_INT(THERMOSTAT_OK, thermostat->setMode(OFF));
   ENUMS_EQUAL_INT(OFF, thermostat->getMode());
}

TEST(ThermostatTestGroup, UpdateMode_Invalid) {
   int badValue = 47;
   ENUMS_EQUAL_INT(THERMOSTAT_INVALID_INPUT, thermostat->setMode((ThermostatMode) badValue));
   ENUMS_EQUAL_INT(OFF, thermostat->getMode());
}

TEST(ThermostatTestGroup, GetDesiredHVACState_ModeHeating) {

   thermostat->setMode(HEATING);

   ENUMS_EQUAL_INT(HEATER_ON, thermostat->getDesiredHVACState(UNDER_TEMPERATURE, ALL_OFF));
   ENUMS_EQUAL_INT(ALL_OFF, thermostat->getDesiredHVACState(UNDER_TEMPERATURE_IN_RANGE, ALL_OFF));
   ENUMS_EQUAL_INT(HEATER_ON, thermostat->getDesiredHVACState(UNDER_TEMPERATURE_IN_RANGE, HEATER_ON));
   ENUMS_EQUAL_INT(ALL_OFF, thermostat->getDesiredHVACState(IN_RANGE, HEATER_ON));
   ENUMS_EQUAL_INT(ALL_OFF, thermostat->getDesiredHVACState(OVER_TEMPERATURE_IN_RANGE, HEATER_ON));
   ENUMS_EQUAL_INT(ALL_OFF, thermostat->getDesiredHVACState(OVER_TEMPERATURE, HEATER_ON));
}

TEST(ThermostatTestGroup, GetDesiredHVACState_ModeCooling) {

   thermostat->setMode(COOLING);

   ENUMS_EQUAL_INT(COOLER_ON, thermostat->getDesiredHVACState(OVER_TEMPERATURE, ALL_OFF));
   ENUMS_EQUAL_INT(ALL_OFF, thermostat->getDesiredHVACState(OVER_TEMPERATURE_IN_RANGE, ALL_OFF));
   ENUMS_EQUAL_INT(COOLER_ON, thermostat->getDesiredHVACState(OVER_TEMPERATURE_IN_RANGE, COOLER_ON));
   ENUMS_EQUAL_INT(ALL_OFF, thermostat->getDesiredHVACState(IN_RANGE, COOLER_ON));
   ENUMS_EQUAL_INT(ALL_OFF, thermostat->getDesiredHVACState(UNDER_TEMPERATURE_IN_RANGE, COOLER_ON));
   ENUMS_EQUAL_INT(ALL_OFF, thermostat->getDesiredHVACState(UNDER_TEMPERATURE, COOLER_ON));
}

TEST(ThermostatTestGroup, GetDesiredHVACState_ModeFanOnly) {

   thermostat->setMode(FAN_ONLY);
   
   ENUMS_EQUAL_INT(FAN_ON, thermostat->getDesiredHVACState(IN_RANGE, ALL_OFF));
   ENUMS_EQUAL_INT(FAN_ON, thermostat->getDesiredHVACState(OVER_TEMPERATURE, ALL_OFF));
   ENUMS_EQUAL_INT(FAN_ON, thermostat->getDesiredHVACState(UNDER_TEMPERATURE, ALL_OFF));
}

TEST(ThermostatTestGroup, GetDesiredHVACState_ModeOff) {

   thermostat->setMode(OFF);

   ENUMS_EQUAL_INT(ALL_OFF, thermostat->getDesiredHVACState(IN_RANGE, ALL_OFF));
   ENUMS_EQUAL_INT(ALL_OFF, thermostat->getDesiredHVACState(OVER_TEMPERATURE, ALL_OFF));
   ENUMS_EQUAL_INT(ALL_OFF, thermostat->getDesiredHVACState(UNDER_TEMPERATURE, ALL_OFF));
}

TEST(ThermostatTestGroup, GetDesiredHVACState_ModeError) {

   thermostat->setMode(ERROR);

   ENUMS_EQUAL_INT(ALL_OFF, thermostat->getDesiredHVACState(IN_RANGE, ALL_OFF));
   ENUMS_EQUAL_INT(ALL_OFF, thermostat->getDesiredHVACState(OVER_TEMPERATURE, ALL_OFF));
   ENUMS_EQUAL_INT(ALL_OFF, thermostat->getDesiredHVACState(UNDER_TEMPERATURE, ALL_OFF));
}

TEST(ThermostatTestGroup, UpdateThermostatMode) {
   ENUMS_EQUAL_INT(THERMOSTAT_OK, thermostat->setMode(HEATING));
   ENUMS_EQUAL_INT(HEATING, thermostat->getMode());
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

   ENUMS_EQUAL_INT(THERMOSTAT_OK, thermostat->update());
   
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

   ENUMS_EQUAL_INT(THERMOSTAT_OK, thermostat->update());
   
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

   ENUMS_EQUAL_INT(THERMOSTAT_OK, thermostat->update());
   
}

TEST(ThermostatTestGroup, GetState) {
   thermostat->setMode(HEATING);
   thermostat->setTemperatureUnits(FAHRENHEIT);
   thermostat->setTargetTemperature(68.0);

   temperatureController->setTargetTemperature(20);
   temperatureController->setTemperatureRange(1.0);

   mock().expectOneCall("HVAC::getCurrentState")
      .andReturnValue(HEATER_ON);

   double temperature = 20;
   double humidity = 50.0;

   mock()
      .expectOneCall("EnvironmentSensor::readTemperatureHumidity")
      .withOutputParameterReturning("temperature", &temperature, sizeof(double))
      .withOutputParameterReturning("humidity", &humidity, sizeof(double))
      .andReturnValue(ENVIRONMENT_SENSOR_OK);

   mock().expectOneCall("HVAC::setDesiredState")
      .ignoreOtherParameters()
      .andReturnValue(THERMOSTAT_OK);


   mock().expectOneCall("HVAC::getCurrentState")
      .andReturnValue(HEATER_ON);

   

   thermostat->update();

   ThermostatState state; 
   ThermostatError err = thermostat->getState(&state);

   ENUMS_EQUAL_INT(THERMOSTAT_OK, err);
   ENUMS_EQUAL_INT(HEATING, state.mode);
   ENUMS_EQUAL_INT(FAHRENHEIT, state.temperatureUnits);
   ENUMS_EQUAL_INT(HEATER_ON, state.hvacState);
   ENUMS_EQUAL_INT(THERMOSTAT_OK, state.error);
   DOUBLES_EQUAL(68.0, state.targetTemperature, 0.01);
   DOUBLES_EQUAL(68, state.currentTemperature, 0.01);
   DOUBLES_EQUAL(50.0, state.currentHumidity, 0.01);
   DOUBLES_EQUAL(20, state.currentTemperatureStandardUnits, 0.01);
   DOUBLES_EQUAL(20, state.targetTemperatureStandardUnits, 0.01);
   DOUBLES_EQUAL(1.0, state.temperatureRange, 0.1);
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

}
