#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include "hvac.hpp"
#include "thermostat_common.hpp"
#include "gpio.hpp"


static Hvac *hvac;
static Switch *heater;
static Switch *ac;
static Switch *fan;
static ThermostatContext *context;

TEST_GROUP(HVACTestGroup)
{
    void setup()
    {
        heater = new Switch(1);
        ac = new Switch(2);
        fan = new Switch(3);
        hvac = new Hvac();
        context = new ThermostatContext();

        context->heatSwitch = heater;
        context->coolSwitch = ac;
        context->fanSwitch = fan;

        hvac->initialize(context);

    }

    void teardown()
    {
        mock().checkExpectations();
        mock().clear();
        delete hvac;
        delete heater;
        delete ac;
        delete fan;
        delete context;
    }
};

TEST(HVACTestGroup, HVACConstructor)
{
    Hvac *testHvac = new Hvac();

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

    CHECK_EQUAL(THERMOSTAT_OK, hvac->setDesiredState(HEATING));
    CHECK_EQUAL(HEATING, hvac->getCurrentState());
}

TEST(HVACTestGroup, SetAllOffMode)
{

    mock().expectOneCall("Switch::turnOff").onObject(heater);
    mock().expectOneCall("Switch::turnOff").onObject(ac);
    mock().expectOneCall("Switch::turnOff").onObject(fan);

    mock().expectOneCall("Switch::isOn").onObject(heater).andReturnValue(false);
    mock().expectOneCall("Switch::isOn").onObject(ac).andReturnValue(false);
    mock().expectOneCall("Switch::isOn").onObject(fan).andReturnValue(false);

    CHECK_EQUAL(THERMOSTAT_OK, hvac->setDesiredState(IDLE));
    CHECK_EQUAL(IDLE, hvac->getCurrentState());
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

    CHECK_EQUAL(THERMOSTAT_OK, hvac->setDesiredState(COOLING));
    CHECK_EQUAL(COOLING, hvac->getCurrentState());
}
