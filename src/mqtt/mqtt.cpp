#include "mqtt.hpp"
#include "secrets.h"
#include "lwip/apps/mqtt.h"
#include "pico/cyw43_arch.h"

static mqtt_client_t *client;

Mqtt::Mqtt()
{
    client = mqtt_client_new();
}

Mqtt::~Mqtt()
{
    mqtt_client_free(client);
}

ThermostatError Mqtt::initalize()
{
    return THERMOSTAT_OK;
}

ThermostatError Mqtt::connect()
{
    const struct mqtt_connect_client_info_t client_info = {
        .client_id = "home-thermostat",
        .client_user = MQTT_USER,
        .client_pass = MQTT_PASS,
        .will_topic = "home/themostat/status",
        .will_msg = "offline",
        .will_qos = 1,
        .will_retain = 1,
    };

    ip_addr_t ipaddr;
    const char *ip_str = MQTT_SERVER_HOST;

    if (!ipaddr_aton(ip_str, &ipaddr))
    {
        // Conversion failed
        printf("Failed to convert IP address: %s\n", ip_str);
        return THERMOSTAT_ERROR;
    }

    cyw43_arch_lwip_begin();
    err_t err = mqtt_client_connect(client, &ipaddr, MQTT_SERVER_PORT, NULL, 0, &client_info);
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

ThermostatError Mqtt::subscribe()
{
    return THERMOSTAT_OK;
}

bool Mqtt::isConnected()
{
    return mqtt_client_is_connected(client);
}
