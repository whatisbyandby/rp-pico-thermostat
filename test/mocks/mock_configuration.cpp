#include <CppUTestExt/MockSupport.h>
#include "configuration.hpp"


Configuration::Configuration()
{
}

Configuration::~Configuration()
{
}


ThermostatError Configuration::load()
{
	return (ThermostatError) mock().actualCall("Configuration::load").returnIntValueOrDefault(THERMOSTAT_OK);
}

ThermostatError Configuration::save()
{
	return (ThermostatError) mock().actualCall("Configuration::save").returnIntValueOrDefault(THERMOSTAT_OK);
}

ThermostatError Configuration::setConfig(ConfigValues *newConfig)
{
	return (ThermostatError) mock().actualCall("Configuration::setConfig").withPointerParameter("newConfig", newConfig).returnIntValueOrDefault(THERMOSTAT_OK);
}


ThermostatError Configuration::getConfig(ConfigValues *config)
{
	return (ThermostatError) mock()
		.actualCall("Configuration::getConfig")
		.withOutputParameter("config", config)
		.returnIntValueOrDefault(THERMOSTAT_OK);
}
