#include "wifi.hpp"
#include "pico/cyw43_arch.h"


Wifi::Wifi() {
    initalized = false;
}

Wifi::~Wifi() {
    
}

ThermostatError Wifi::initialize(Configuration *newConfig) {

    config = newConfig;

    if (initalized) {
        return THERMOSTAT_OK;
    }
    if (cyw43_arch_init()) {
        return THERMOSTAT_INIT_FAILED;
    }
    cyw43_arch_enable_sta_mode();
    initalized = true;
    return THERMOSTAT_OK;
}


ThermostatError Wifi::connect() {

    ConfigValues configValues;
    config->getConfig(&configValues);

    if (cyw43_arch_wifi_connect_timeout_ms(configValues.ssid, configValues.password, CYW43_AUTH_WPA2_AES_PSK, 30000)) {
        return THERMOSTAT_INIT_FAILED;
    }
    return THERMOSTAT_OK;
}

ThermostatError Wifi::disconnect() {
    return THERMOSTAT_OK;
}

ThermostatError Wifi::deinitalize() {
    return THERMOSTAT_OK;
}

