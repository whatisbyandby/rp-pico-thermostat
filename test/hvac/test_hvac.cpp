#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include "hvac.hpp"
#include "thermostat_common.hpp"
#include "gpio.hpp"
#include <CppUTestExt/MockExpectedCall.h>

static HVAC *hvac;
static Switch *heater;
static Switch *ac;
static Switch *fan;

TEST_GROUP(HVACTestGroup)
{
    void setup()
    {
        heater = new Switch(1);
        ac = new Switch(2);
        fan = new Switch(3);
        hvac = new HVAC(heater, ac, fan);
    }

    void teardown()
    {
        delete hvac;
        delete heater;
        delete ac;
        delete fan;
        mock().clear();
    }
};

TEST(HVACTestGroup, HVACConstructor)
{
    HVAC *testHvac = new HVAC(NULL, NULL, NULL);

    delete testHvac;
    
}


TEST(HVACTestGroup, SetHeaterOn)
{
    mock().expectOneCall("Switch::turnOn").onObject(heater);
    mock().expectOneCall("Switch::turnOff").onObject(ac);
    mock().expectOneCall("Switch::turnOff").onObject(fan);

    mock().expectOneCall("Switch::isOn").onObject(heater).andReturnValue(true);
    mock().expectOneCall("Switch::isOn").onObject(ac).andReturnValue(false);
    mock().expectOneCall("Switch::isOn").onObject(fan).andReturnValue(false);

    CHECK_EQUAL(THERMOSTAT_OK, hvac->setDesiredState(HEATER_ON));
    CHECK_EQUAL(HEATER_ON, hvac->getCurrentState());
}

TEST(HVACTestGroup, SetAllOffMode)
{
    mock().expectOneCall("Switch::turnOff").onObject(heater);
    mock().expectOneCall("Switch::turnOff").onObject(ac);
    mock().expectOneCall("Switch::turnOff").onObject(fan);

    mock().expectOneCall("Switch::isOn").onObject(heater).andReturnValue(false);
    mock().expectOneCall("Switch::isOn").onObject(ac).andReturnValue(false);
    mock().expectOneCall("Switch::isOn").onObject(fan).andReturnValue(false);

    CHECK_EQUAL(THERMOSTAT_OK, hvac->setDesiredState(ALL_OFF));
    CHECK_EQUAL(ALL_OFF, hvac->getCurrentState());
}

TEST(HVACTestGroup, SetFanMode)
{
    mock().expectOneCall("Switch::turnOff").onObject(heater);
    mock().expectOneCall("Switch::turnOff").onObject(ac);
    mock().expectOneCall("Switch::turnOn").onObject(fan);

    mock().expectOneCall("Switch::isOn").onObject(heater).andReturnValue(false);
    mock().expectOneCall("Switch::isOn").onObject(ac).andReturnValue(false);
    mock().expectOneCall("Switch::isOn").onObject(fan).andReturnValue(true);

    CHECK_EQUAL(THERMOSTAT_OK, hvac->setDesiredState(FAN_ON));
    CHECK_EQUAL(FAN_ON, hvac->getCurrentState());
}

TEST(HVACTestGroup, SetCoolerMode)
{
    mock().expectOneCall("Switch::turnOff").onObject(heater);
    mock().expectOneCall("Switch::turnOn").onObject(ac);
    mock().expectOneCall("Switch::turnOff").onObject(fan);

    mock().expectOneCall("Switch::isOn").onObject(heater).andReturnValue(false);
    mock().expectOneCall("Switch::isOn").onObject(ac).andReturnValue(true);
    mock().expectOneCall("Switch::isOn").onObject(fan).andReturnValue(false);

    CHECK_EQUAL(THERMOSTAT_OK, hvac->setDesiredState(COOLER_ON));
    CHECK_EQUAL(COOLER_ON, hvac->getCurrentState());
}
