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