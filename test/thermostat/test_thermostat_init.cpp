#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include "thermostat.hpp"
#include "environment_sensor.hpp"
#include "thermostat_common.hpp"
#include "hvac.hpp"
#include <iostream>

static Thermostat *thermostat;
static EnvironmentSensor *environmentSensor;
static TemperatureController *tempController;
static Hvac *hvac;

TEST_GROUP(ThermostatTestGroupInit){
    void setup(){
         environmentSensor = new EnvironmentSensor();
         tempController = new TemperatureController();
         hvac = new Hvac();
         thermostat = new Thermostat();
         thermostat->initialize(environmentSensor, tempController, hvac);


}

void teardown()
{

   mock().checkExpectations();
   mock().clear();
   delete thermostat;
   delete environmentSensor;
   delete tempController;
   delete hvac;
}
}
;

TEST(ThermostatTestGroupInit, ThermostatInitalize)
{

   Thermostat *testInit = new Thermostat();
   ENUMS_EQUAL_INT(THERMOSTAT_OK, testInit->initialize(environmentSensor, tempController, hvac));
   CHECK_TRUE(testInit->isInitialized());
   delete testInit;
}
