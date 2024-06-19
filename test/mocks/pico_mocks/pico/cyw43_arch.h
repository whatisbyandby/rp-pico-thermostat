#include <stdint.h>
#define CYW43_AUTH_WPA2_AES_PSK 0x00400004

int cyw43_arch_init();
void  cyw43_arch_enable_sta_mode();
int cyw43_arch_wifi_connect_timeout_ms(const char *ssid, const char *pw, uint32_t auth, uint32_t timeout);
