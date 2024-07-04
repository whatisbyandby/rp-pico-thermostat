#include "mqtt.hpp"
#include "lwip/apps/mqtt.h"
#include "pico/cyw43_arch.h"


static mqtt_client_t *client;

Mqtt::Mqtt()
{   

}

Mqtt::~Mqtt()
{
    mqtt_client_free(client);
}

ThermostatError Mqtt::initialize(Configuration *newConfig)
{
    configuration = newConfig;
    client = mqtt_client_new();
    return THERMOSTAT_OK;
}

ThermostatError Mqtt::connect()
{   

    ConfigValues configValues;
    configuration->getConfig(&configValues);

    const struct mqtt_connect_client_info_t client_info = {
        .client_id = "home-thermostat",
        .client_user = configValues.mqtt_username,
        .client_pass = configValues.mqtt_password,
        .will_topic = "home/themostat/status",
        .will_msg = "offline",
        .will_qos = 1,
        .will_retain = 1,
    };

    ip_addr_t ipaddr;
    const char *ip_str = configValues.mqtt_host;

    if (!ipaddr_aton(ip_str, &ipaddr))
    {
        // Conversion failed
        printf("Failed to convert IP address: %s\n", ip_str);
        return THERMOSTAT_ERROR;
    }

    cyw43_arch_lwip_begin();
    err_t err = mqtt_client_connect(client, &ipaddr, configValues.mqtt_port, NULL, 0, &client_info);
    cyw43_arch_lwip_end();
    return THERMOSTAT_OK;
}

ThermostatError Mqtt::publish(const char *topic, char *message)
{
    err_t err = mqtt_publish(client, topic, message, strlen(message), 0, 0, 0, 0);
    if (err != ERR_OK)
    {
        return THERMOSTAT_ERROR;
    }
    return THERMOSTAT_OK;
}

ThermostatError Mqtt::subscribe(const char *topic)
{
    return THERMOSTAT_OK;
}

bool Mqtt::isConnected()
{
    return mqtt_client_is_connected(client);
}
