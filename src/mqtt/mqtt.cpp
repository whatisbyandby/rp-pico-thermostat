#include "mqtt.hpp"
#include "lwip/apps/mqtt.h"
#include "pico/cyw43_arch.h"
#include "pico/stdlib.h"


static mqtt_client_t *client;


static void publish_callback(void *arg, const char *topic, u32_t tot_len)
{
    Mqtt *mqtt = (Mqtt *)arg;
    printf("Publish callback\n");
    mqtt->commandBuffer[0] = '\0';
    mqtt->messageLength = tot_len;
    mqtt->currentWriteIndex = 0;
}

static void data_callback(void *arg, const u8_t *data, u16_t len, u8_t flags)
{
    Mqtt *mqtt = (Mqtt *)arg;
    printf("Data callback\n");
    for (int i = 0; i < len; i++)
    {
        mqtt->commandBuffer[mqtt->currentWriteIndex++] = data[i];
    }
    mqtt->commandBuffer[mqtt->currentWriteIndex] = '\0';
    if (flags & MQTT_DATA_FLAG_LAST)
    {
        ThermostatCommand *command = new ThermostatCommand();
        std::string inputString = std::string((char *)mqtt->commandBuffer);
        command->command_string = inputString;
        mqtt->executeCallback(command);
    }
}


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
    mqtt_set_inpub_callback(client, publish_callback, data_callback, this);
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

ThermostatError Mqtt::subscribe(const char *topic, CommandCallback callback, void *arg)
{
    commandCallback = callback;
    callbackArg = arg;
    err_t err = mqtt_subscribe(client, topic, 0, NULL, NULL);
    return THERMOSTAT_OK;
}

void Mqtt::executeCallback(ThermostatCommand *command)
{
    commandCallback(command, callbackArg);
}


bool Mqtt::isConnected()
{
    return mqtt_client_is_connected(client);
}
