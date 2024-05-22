#include "CppUTest/TestHarness.h"
#include "thermostat.hpp"
#include "environment_sensor.hpp"
#include "thermostat_common.hpp"

static Thermostat *thermostat;
static EnvironmentSensor *environmentSensor;

TEST_GROUP(ThermostatTestGroup)
{
    void setup()
   {
      environmentSensor = new EnvironmentSensor(NULL);
      thermostat = new Thermostat();
   }

   void teardown()
   {
      delete thermostat;
      delete environmentSensor;
   }
};


TEST(ThermostatTestGroup, ThermostatConstructor)
{
   Thermostat *thermostat = new Thermostat();

   CHECK_EQUAL(FAHRENHEIT, thermostat->getTemperatureUnits());
   CHECK_FALSE(thermostat->isInitialized());

   delete thermostat;
}


TEST(ThermostatTestGroup, UpdateTemperatureUnits)
{
   CHECK_EQUAL(THERMOSTAT_OK, thermostat->setTemperatureUnits(CELSIUS));
   CHECK_EQUAL(CELSIUS, thermostat->getTemperatureUnits());

   CHECK_EQUAL(THERMOSTAT_OK, thermostat->setTemperatureUnits(FAHRENHEIT));
   CHECK_EQUAL(FAHRENHEIT, thermostat->getTemperatureUnits());
}

TEST(ThermostatTestGroup, GetDesiredHVACState_ModeHeating) {
   CHECK_EQUAL(HEATER_ON, thermostat->getDesiredHVACState(UNDER_TEMPERATURE, HEATING, IDLE));
   CHECK_EQUAL(HEATER_ON, thermostat->getDesiredHVACState(IN_RANGE, HEATING, HEATER_ON));
   CHECK_EQUAL(IDLE, thermostat->getDesiredHVACState(OVER_TEMPERATURE, HEATING, IDLE));
}

TEST(ThermostatTestGroup, GetDesiredHVACState_ModeCooling) {
   CHECK_EQUAL(COOLER_ON, thermostat->getDesiredHVACState(OVER_TEMPERATURE, COOLING, IDLE));
   CHECK_EQUAL(COOLER_ON, thermostat->getDesiredHVACState(IN_RANGE, COOLING, COOLER_ON));
   CHECK_EQUAL(IDLE, thermostat->getDesiredHVACState(UNDER_TEMPERATURE, COOLING, IDLE));
}

TEST(ThermostatTestGroup, GetDesiredHVACState_ModeFanOnly) {
   CHECK_EQUAL(FAN_ON, thermostat->getDesiredHVACState(IN_RANGE, FAN_ONLY, IDLE));
   CHECK_EQUAL(FAN_ON, thermostat->getDesiredHVACState(OVER_TEMPERATURE, FAN_ONLY, IDLE));
   CHECK_EQUAL(FAN_ON, thermostat->getDesiredHVACState(UNDER_TEMPERATURE, FAN_ONLY, IDLE));
}

TEST(ThermostatTestGroup, GetDesiredHVACState_ModeOff) {
   CHECK_EQUAL(ALL_OFF, thermostat->getDesiredHVACState(IN_RANGE, OFF, IDLE));
   CHECK_EQUAL(ALL_OFF, thermostat->getDesiredHVACState(OVER_TEMPERATURE, OFF, IDLE));
   CHECK_EQUAL(ALL_OFF, thermostat->getDesiredHVACState(UNDER_TEMPERATURE, OFF, IDLE));
}

TEST(ThermostatTestGroup, GetDesiredHVACState_ModeError) {
   CHECK_EQUAL(ALL_OFF, thermostat->getDesiredHVACState(IN_RANGE, ERROR, IDLE));
   CHECK_EQUAL(ALL_OFF, thermostat->getDesiredHVACState(OVER_TEMPERATURE, ERROR, IDLE));
   CHECK_EQUAL(ALL_OFF, thermostat->getDesiredHVACState(UNDER_TEMPERATURE, ERROR, IDLE));
}