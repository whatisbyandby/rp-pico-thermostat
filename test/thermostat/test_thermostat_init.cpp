#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include "thermostat.hpp"
#include "environment_sensor.hpp"
#include "thermostat_common.hpp"
#include "hvac.hpp"
#include <iostream>

static Thermostat *thermostat;
static ThermostatContext *context;

TEST_GROUP(ThermostatTestGroupInit){
    void setup(){
      ThermostatContext newCtx;
      context = &newCtx;

}

void teardown()
{

   mock().checkExpectations();
   mock().clear();
}
}
;

TEST(ThermostatTestGroupInit, ThermostatInitalize)
{

   Thermostat *testInit = new Thermostat();
   ENUMS_EQUAL_INT(THERMOSTAT_OK, testInit->initialize(context));
   CHECK_TRUE(testInit->isInitialized());
   delete testInit;
}
