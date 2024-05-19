#include "CppUTest/TestHarness.h"
#include "thermostat.hpp"
#include "environment_sensor.hpp"

static Thermostat *thermostat;
static EnvironmentSensor *environmentSensor;

TEST_GROUP(ThermostatTestGroup)
{
    void setup()
   {
      thermostat = new Thermostat();
   }

   void teardown()
   {
      delete thermostat;
   }
};

TEST(ThermostatTestGroup, TestConvertFtoC){
      DOUBLES_EQUAL(0.0, convertFahrenheitToCelsius(32.0), 0.01);
      DOUBLES_EQUAL(100.0, convertFahrenheitToCelsius(212.0), 0.01);
      DOUBLES_EQUAL(37.7778, convertFahrenheitToCelsius(100.0), 0.01);
}

TEST(ThermostatTestGroup, TestConvertCtoF){
      DOUBLES_EQUAL(32.0, convertCelsiusToFahrenheit(0.0), 0.01);
      DOUBLES_EQUAL(212.0, convertCelsiusToFahrenheit(100.0), 0.01);
      DOUBLES_EQUAL(100.0, convertCelsiusToFahrenheit(37.7778), 0.01);
}

TEST(ThermostatTestGroup, ThermostatConstructor)
{
   Thermostat *thermostat = new Thermostat();


   CHECK_EQUAL(68.0, thermostat->getTargetTemperature());
   CHECK_EQUAL(FAHRENHEIT, thermostat->getTemperatureUnits());
   CHECK_FALSE(thermostat->isInitialized());

   delete thermostat;
}

TEST(ThermostatTestGroup, ThermostatSetEnvironmentSensor)
{
   EnvironmentSensor *environmentSensor = new EnvironmentSensor(NULL);

   CHECK_EQUAL(THERMOSTAT_OK, thermostat->setEnvironmentSensor(environmentSensor));
}

TEST(ThermostatTestGroup, ThermostatSetEnvironmentSensor_NULL)
{
   CHECK_EQUAL(THERMOSTAT_INVALID_INPUT, thermostat->setEnvironmentSensor(NULL));
}

TEST(ThermostatTestGroup, ThermostatInitalize) {

   environmentSensor = new EnvironmentSensor(NULL);

   thermostat->setEnvironmentSensor(environmentSensor);

   CHECK_EQUAL(THERMOSTAT_OK, thermostat->initialize());
   CHECK_TRUE(thermostat->isInitialized());
}

TEST(ThermostatTestGroup, UpdateTargetTemperature_CELSIUS)
{
   thermostat->setTemperatureUnits(CELSIUS);

   CHECK_EQUAL(THERMOSTAT_OK, thermostat->setTargetTemperature(20.0));
   DOUBLES_EQUAL(20.0, thermostat->getTargetTemperature(), 0.01);   
}

TEST(ThermostatTestGroup, UpdateTargetTemperature_FAHRENHEIT)
{
   thermostat->setTemperatureUnits(FAHRENHEIT);

   CHECK_EQUAL(THERMOSTAT_OK, thermostat->setTargetTemperature(68.0));
   DOUBLES_EQUAL(68.0, thermostat->getTargetTemperature(), 0.01);   
}

TEST(ThermostatTestGroup, UpdateTargetTemperature_OutOfRange_CELSIUS)
{
   thermostat->setTemperatureUnits(CELSIUS);
   thermostat->setTargetTemperature(20.0);

   CHECK_EQUAL(THERMOSTAT_INVALID_INPUT, thermostat->setTargetTemperature(31.0));
   DOUBLES_EQUAL(20.0, thermostat->getTargetTemperature(), 0.01);

   CHECK_EQUAL(THERMOSTAT_INVALID_INPUT, thermostat->setTargetTemperature(9.0));
   DOUBLES_EQUAL(20.0, thermostat->getTargetTemperature(), 0.01);
   
}

TEST(ThermostatTestGroup, UpdateTargetTemperature_OutOfRange_FAHRENHEIT)
{
   thermostat->setTemperatureUnits(FAHRENHEIT);
   thermostat->setTargetTemperature(68.0);

   CHECK_EQUAL(THERMOSTAT_INVALID_INPUT, thermostat->setTargetTemperature(87.0));
   DOUBLES_EQUAL(68.0, thermostat->getTargetTemperature(), 0.01);

   CHECK_EQUAL(THERMOSTAT_INVALID_INPUT, thermostat->setTargetTemperature(49.0));
   DOUBLES_EQUAL(68.0, thermostat->getTargetTemperature(), 0.01);
   
}

TEST(ThermostatTestGroup, UpdateTemperatureUnits)
{
   CHECK_EQUAL(THERMOSTAT_OK, thermostat->setTemperatureUnits(CELSIUS));
   CHECK_EQUAL(CELSIUS, thermostat->getTemperatureUnits());

   CHECK_EQUAL(THERMOSTAT_OK, thermostat->setTemperatureUnits(FAHRENHEIT));
   CHECK_EQUAL(FAHRENHEIT, thermostat->getTemperatureUnits());
}