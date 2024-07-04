#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include "thermostat.hpp"
#include "temperature_controller.hpp"
#include "environment_sensor.hpp"
#include "thermostat_common.hpp"
#include "hvac.hpp"
#include <iostream>

static Thermostat *thermostat;
static ThermostatContext *context;
static TemperatureController *tempController;
static EnvironmentSensor *sensor;

TEST_GROUP(ThermostatTestGroup){
    void setup(){
      thermostat = new Thermostat();
      context = new ThermostatContext();
      tempController = new TemperatureController();
      sensor = new EnvironmentSensor();

      context->sensor = sensor;
      context->tempController = tempController;

      thermostat->initialize(context);


}

void teardown()
{
   mock().checkExpectations();
   mock().clear();
   delete thermostat;
   delete context;
   delete tempController;
   delete sensor;
   
}
}
;




// // ============ Update Temperature Units

TEST(ThermostatTestGroup, UpdateTargetTemperatureCelsius)
{
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

TEST(ThermostatTestGroup, UpdateTargetTemperatureFAHRENHEIT)
{
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

TEST(ThermostatTestGroup, UpdateMode_Valid)
{
   ENUMS_EQUAL_INT(THERMOSTAT_OK, thermostat->setMode(HEAT));
   ENUMS_EQUAL_INT(HEAT, thermostat->getMode());

   ENUMS_EQUAL_INT(THERMOSTAT_OK, thermostat->setMode(COOL));
   ENUMS_EQUAL_INT(COOL, thermostat->getMode());

   ENUMS_EQUAL_INT(THERMOSTAT_OK, thermostat->setMode(FAN_ONLY));
   ENUMS_EQUAL_INT(FAN_ONLY, thermostat->getMode());

   ENUMS_EQUAL_INT(THERMOSTAT_OK, thermostat->setMode(OFF));
   ENUMS_EQUAL_INT(OFF, thermostat->getMode());
}

TEST(ThermostatTestGroup, UpdateMode_Invalid)
{
   int badValue = 47;
   ENUMS_EQUAL_INT(THERMOSTAT_INVALID_INPUT, thermostat->setMode((ThermostatMode)badValue));
   ENUMS_EQUAL_INT(OFF, thermostat->getMode());
}

TEST(ThermostatTestGroup, GetDesiredHVACState_ModeHeating)
{

   thermostat->setMode(HEAT);

   ENUMS_EQUAL_INT(HEATING, thermostat->getDesiredHVACState(UNDER_TEMPERATURE, IDLE));
   ENUMS_EQUAL_INT(IDLE, thermostat->getDesiredHVACState(UNDER_TEMPERATURE_IN_RANGE, IDLE));
   ENUMS_EQUAL_INT(HEATING, thermostat->getDesiredHVACState(UNDER_TEMPERATURE_IN_RANGE, HEATING));
   ENUMS_EQUAL_INT(IDLE, thermostat->getDesiredHVACState(IN_RANGE, HEATING));
   ENUMS_EQUAL_INT(IDLE, thermostat->getDesiredHVACState(OVER_TEMPERATURE_IN_RANGE, HEATING));
   ENUMS_EQUAL_INT(IDLE, thermostat->getDesiredHVACState(OVER_TEMPERATURE, HEATING));
}

TEST(ThermostatTestGroup, GetDesiredHVACState_ModeCooling)
{

   thermostat->setMode(COOL);

   ENUMS_EQUAL_INT(COOLING, thermostat->getDesiredHVACState(OVER_TEMPERATURE, IDLE));
   ENUMS_EQUAL_INT(IDLE, thermostat->getDesiredHVACState(OVER_TEMPERATURE_IN_RANGE, IDLE));
   ENUMS_EQUAL_INT(COOLING, thermostat->getDesiredHVACState(OVER_TEMPERATURE_IN_RANGE, COOLING));
   ENUMS_EQUAL_INT(IDLE, thermostat->getDesiredHVACState(IN_RANGE, COOLING));
   ENUMS_EQUAL_INT(IDLE, thermostat->getDesiredHVACState(UNDER_TEMPERATURE_IN_RANGE, COOLING));
   ENUMS_EQUAL_INT(IDLE, thermostat->getDesiredHVACState(UNDER_TEMPERATURE, COOLING));
}

TEST(ThermostatTestGroup, GetDesiredHVACState_ModeFanOnly)
{

   thermostat->setMode(FAN_ONLY);

   ENUMS_EQUAL_INT(FAN_ON, thermostat->getDesiredHVACState(IN_RANGE, IDLE));
   ENUMS_EQUAL_INT(FAN_ON, thermostat->getDesiredHVACState(OVER_TEMPERATURE, IDLE));
   ENUMS_EQUAL_INT(FAN_ON, thermostat->getDesiredHVACState(UNDER_TEMPERATURE, IDLE));
}

TEST(ThermostatTestGroup, GetDesiredHVACState_ModeOff)
{

   thermostat->setMode(OFF);

   ENUMS_EQUAL_INT(IDLE, thermostat->getDesiredHVACState(IN_RANGE, IDLE));
   ENUMS_EQUAL_INT(IDLE, thermostat->getDesiredHVACState(OVER_TEMPERATURE, IDLE));
   ENUMS_EQUAL_INT(IDLE, thermostat->getDesiredHVACState(UNDER_TEMPERATURE, IDLE));
}

TEST(ThermostatTestGroup, UpdateThermostatMode)
{
   ENUMS_EQUAL_INT(THERMOSTAT_OK, thermostat->setMode(HEAT));
   ENUMS_EQUAL_INT(HEAT, thermostat->getMode());
}

TEST(ThermostatTestGroup, UpdateThermostat_ExpectHeaterOn_UnderTemp)
{

   thermostat->setMode(HEAT);
   context->tempController->setTargetTemperature(25.0);

   double temperature = 20.0;
   double humidity = 50.0;

   mock()
       .expectOneCall("EnvironmentSensor::readTemperatureHumidity")
       .withOutputParameterReturning("temperature", &temperature, sizeof(double))
       .withOutputParameterReturning("humidity", &humidity, sizeof(double))
       .andReturnValue(THERMOSTAT_OK);

   mock()
       .expectOneCall("HVAC::getCurrentState")
       .andReturnValue(IDLE);

   mock()
       .expectOneCall("HVAC::setDesiredState")
       .withParameter("state", HEATING)
       .andReturnValue(THERMOSTAT_OK);

   ENUMS_EQUAL_INT(THERMOSTAT_OK, thermostat->update());
}

TEST(ThermostatTestGroup, UpdateThermostat_ExpectHeaterOn_InRange)
{

   thermostat->setMode(HEAT);
   context->tempController->setTargetTemperature(20);

   double temperature = 19.9;
   double humidity = 50.0;

   mock()
       .expectOneCall("EnvironmentSensor::readTemperatureHumidity")
       .withOutputParameterReturning("temperature", &temperature, sizeof(double))
       .withOutputParameterReturning("humidity", &humidity, sizeof(double))
       .andReturnValue(THERMOSTAT_OK);

   mock()
       .expectOneCall("HVAC::getCurrentState")
       .andReturnValue(HEATING);

   mock()
       .expectOneCall("HVAC::setDesiredState")
       .withParameter("state", HEATING)
       .andReturnValue(THERMOSTAT_OK);

   ENUMS_EQUAL_INT(THERMOSTAT_OK, thermostat->update());
}

TEST(ThermostatTestGroup, UpdateThermostat_ExpectAllOff_OverTemp)
{

   thermostat->setMode(HEAT);
   context->tempController->setTargetTemperature(20);

   double temperature = 20.1;
   double humidity = 50.0;

   mock()
       .expectOneCall("EnvironmentSensor::readTemperatureHumidity")
       .withOutputParameterReturning("temperature", &temperature, sizeof(double))
       .withOutputParameterReturning("humidity", &humidity, sizeof(double))
       .andReturnValue(THERMOSTAT_OK);

   mock()
       .expectOneCall("HVAC::getCurrentState")
       .andReturnValue(HEATING);

   mock()
       .expectOneCall("HVAC::setDesiredState")
       .withParameter("state", IDLE)
       .andReturnValue(THERMOSTAT_OK);

   ENUMS_EQUAL_INT(THERMOSTAT_OK, thermostat->update());
}

TEST(ThermostatTestGroup, GetState)
{
   thermostat->setMode(HEAT);
   thermostat->setTemperatureUnits(FAHRENHEIT);
   thermostat->setTargetTemperature(68.0);

   context->tempController->setTargetTemperature(20);
   context->tempController->setTemperatureRange(1.0);

   mock().expectOneCall("HVAC::getCurrentState").andReturnValue(HEATING);

   double temperature = 20;
   double humidity = 50.0;

   mock()
       .expectOneCall("EnvironmentSensor::readTemperatureHumidity")
       .withOutputParameterReturning("temperature", &temperature, sizeof(double))
       .withOutputParameterReturning("humidity", &humidity, sizeof(double))
       .andReturnValue(THERMOSTAT_OK);

   mock().expectOneCall("HVAC::setDesiredState").ignoreOtherParameters().andReturnValue(THERMOSTAT_OK);

   mock().expectOneCall("HVAC::getCurrentState").andReturnValue(HEATING);

   thermostat->update();

   ThermostatData data;
   ThermostatError err = thermostat->getData(&data);

   ENUMS_EQUAL_INT(THERMOSTAT_OK, err);
   ENUMS_EQUAL_INT(HEAT, data.mode);
   ENUMS_EQUAL_INT(FAHRENHEIT, data.temperatureUnits);
   ENUMS_EQUAL_INT(HEATING, data.hvacState);
   ENUMS_EQUAL_INT(THERMOSTAT_OK, data.error);
   DOUBLES_EQUAL(68.0, data.targetTemperature, 0.01);
   DOUBLES_EQUAL(68, data.currentTemperature, 0.01);
   DOUBLES_EQUAL(50.0, data.currentHumidity, 0.01);
   DOUBLES_EQUAL(20, data.currentTemperatureStandardUnits, 0.01);
   DOUBLES_EQUAL(20, data.targetTemperatureStandardUnits, 0.01);
   DOUBLES_EQUAL(1.0, data.temperatureRange, 0.1);
}

TEST(ThermostatTestGroup, PrintState)
{
   thermostat->setMode(HEAT);
   thermostat->setTemperatureUnits(CELSIUS);
   thermostat->setTargetTemperature(25.0);

   // initalize an empty string using std::string
   std::string state;

   mock().expectOneCall("HVAC::getCurrentState").andReturnValue(HEATING);

   thermostat->printState(&state);
}
