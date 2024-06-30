#include <CppUTestExt/MockSupport.h>
#include "thermostat.hpp"


Thermostat::Thermostat(EnvironmentSensor *environmentSensor, TemperatureController *temperatureController, HVAC *hvac){

}

Thermostat::~Thermostat(){

}

ThermostatError Thermostat::initialize() {
    return (ThermostatError) mock().actualCall("Thermostat::initialize").returnIntValueOrDefault(THERMOSTAT_OK);
}

bool Thermostat::isInitialized() {
    return mock().actualCall("Thermostat::isInitialized").returnIntValueOrDefault(false);
}

ThermostatError Thermostat::setTemperatureUnits(TemperatureUnits temperatureUnits) {
    return (ThermostatError) mock()
        .actualCall("Thermostat::setTemperatureUnits")
        .withIntParameter("temperatureUnits", temperatureUnits)
        .returnIntValueOrDefault(THERMOSTAT_OK);
}

TemperatureUnits Thermostat::getTemperatureUnits() {
    return (TemperatureUnits) mock().actualCall("Thermostat::getTemperatureUnits").returnIntValueOrDefault(FAHRENHEIT);
}

ThermostatError Thermostat::setTargetTemperature(double targetTemperature) {
    return (ThermostatError) mock()
        .actualCall("Thermostat::setTargetTemperature")
        .withDoubleParameter("targetTemperature", targetTemperature)
        .returnIntValueOrDefault(THERMOSTAT_OK);
}

double Thermostat::getTargetTemperature() {
    return mock()
        .actualCall("Thermostat::getTargetTemperature")
        .returnDoubleValueOrDefault(0.0);
}

ThermostatState Thermostat::getDesiredHVACState(TemperatureState temperatureState, ThermostatState currentHVACState) {
    return (ThermostatState) mock()
        .actualCall("Thermostat::getDesiredHVACState")
        .withIntParameter("temperatureState", temperatureState)
        .withIntParameter("currentHVACState", currentHVACState)
        .returnIntValueOrDefault(IDLE);
}

ThermostatMode Thermostat::getMode() {
    return (ThermostatMode) mock().actualCall("Thermostat::getMode").returnIntValueOrDefault(OFF);
}

ThermostatError Thermostat::setMode(ThermostatMode mode) {
    return (ThermostatError) mock()
        .actualCall("Thermostat::setMode")
        .withIntParameter("mode", mode)
        .returnIntValueOrDefault(THERMOSTAT_OK);
}

ThermostatError Thermostat::printState(std::string *output) {
    return (ThermostatError) mock()
        .actualCall("Thermostat::printState")
        .withPointerParameter("output", output)
        .returnIntValueOrDefault(THERMOSTAT_OK);
}


ThermostatError Thermostat::update() {
    return (ThermostatError) mock()
        .actualCall("Thermostat::update")
        .returnIntValueOrDefault(THERMOSTAT_OK);
}
