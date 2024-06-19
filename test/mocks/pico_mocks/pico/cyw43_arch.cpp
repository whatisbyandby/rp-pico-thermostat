#include <CppUTestExt/MockSupport.h>

int cyw43_arch_init(){
    return mock().actualCall("cyw43_arch_init").returnIntValueOrDefault(0);
}

void  cyw43_arch_enable_sta_mode() {
    mock().actualCall("cyw43_arch_enable_sta_mode");
}

int cyw43_arch_wifi_connect_timeout_ms(const char *ssid, const char *pw, uint32_t auth, uint32_t timeout) {
    return mock().actualCall("cyw43_arch_wifi_connect_timeout_ms")
        .withStringParameter("ssid", ssid)
        .withStringParameter("pw", pw)
        .withUnsignedIntParameter("auth", auth)
        .withUnsignedIntParameter("timeout", timeout)
        .returnIntValueOrDefault(0);
}