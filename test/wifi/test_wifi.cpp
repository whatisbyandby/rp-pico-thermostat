#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"

#include "wifi.hpp"

static Wifi *wifi;
static Configuration *config;

TEST_GROUP(TestGroupWifi){
    void setup(){
        wifi = new Wifi();
config = new Configuration();
}

void teardown()
{
    mock().checkExpectations();
    mock().clear();
    delete wifi;
    delete config;
}
}
;

TEST(TestGroupWifi, initalize)
{
    mock().expectOneCall("cyw43_arch_init").andReturnValue(0);
    mock().expectOneCall("cyw43_arch_enable_sta_mode");

    ENUMS_EQUAL_INT(THERMOSTAT_OK, wifi->initialize(config));
}

TEST(TestGroupWifi, initalize_failed)
{
    mock().expectOneCall("cyw43_arch_init").andReturnValue(1);

    ENUMS_EQUAL_INT(THERMOSTAT_INIT_FAILED, wifi->initialize(config));
}

TEST(TestGroupWifi, connect)
{

    ConfigValues configValues{
        .ssid = "ssid",
        .password = "password",
    };

    mock().expectOneCall("Configuration::getConfig").withOutputParameterReturning("config", &configValues, sizeof(configValues));

    mock().expectOneCall("cyw43_arch_wifi_connect_timeout_ms").withStringParameter("ssid", "ssid").withStringParameter("pw", "password").withUnsignedIntParameter("auth", 0x00400004).withUnsignedIntParameter("timeout", 30000).andReturnValue(0);

    ENUMS_EQUAL_INT(THERMOSTAT_OK, wifi->connect());
}

TEST(TestGroupWifi, connectFailed)
{

    ConfigValues configValues{
        .ssid = "ssid",
        .password = "password",
    };

    mock().expectOneCall("Configuration::getConfig").withOutputParameterReturning("config", &configValues, sizeof(configValues));

    mock().expectOneCall("cyw43_arch_wifi_connect_timeout_ms").withStringParameter("ssid", "ssid").withStringParameter("pw", "password").withUnsignedIntParameter("auth", 0x00400004).withUnsignedIntParameter("timeout", 30000).andReturnValue(-1);

    ENUMS_EQUAL_INT(THERMOSTAT_INIT_FAILED, wifi->connect());
}
