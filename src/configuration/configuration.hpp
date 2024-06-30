#ifndef CONFIGURATION_HPP
#define CONFIGURATION_HPP

#include "thermostat_common.hpp"

struct ConfigValues
{
	char ssid[128];
	char password[128];
	char mqtt_host[20];
	int mqtt_port;
	char mqtt_username[128];
	char mqtt_password[128];
};


class Configuration
{
public:
    Configuration();
    ~Configuration();
	ThermostatError load();
	ThermostatError save();

	ThermostatError setConfig(ConfigValues *newConfig);
	ThermostatError getConfig(ConfigValues *config);
	
	void print();

    
private:
    char ssid[128];
	char password[128];
	char mqtt_host[20];
	int mqtt_port;
	char mqtt_username[128];
	char mqtt_password[128];
};

#endif // CONFIGURATION_HPP
