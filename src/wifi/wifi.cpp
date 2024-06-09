#include "wifi.hpp"
#include "pico/cyw43_arch.h"


Wifi::Wifi() {
    initalized = false;
}

Wifi::~Wifi() {
    
}

ThermostatError Wifi::initalize() {
    if (initalized) {
        return THERMOSTAT_OK;
    }
    if (cyw43_arch_init()) {
        printf("failed to initialise\n");
        return THERMOSTAT_ERROR;
    }
    cyw43_arch_enable_sta_mode();
    initalized = true;
    return THERMOSTAT_OK;
}

ThermostatError Wifi::connect(const char *ssid, const char *password) {
    printf("Connecting to Wi-Fi...\n");
    if (cyw43_arch_wifi_connect_timeout_ms(ssid, password, CYW43_AUTH_WPA2_AES_PSK, 30000)) {
        printf("failed to connect.\n");
        return THERMOSTAT_ERROR;
    } else {
        printf("Connected.\n");
    }
    return THERMOSTAT_OK;
}

ThermostatError Wifi::disconnect() {
    return THERMOSTAT_OK;
}

ThermostatError Wifi::deinitalize() {
    return THERMOSTAT_OK;
}
