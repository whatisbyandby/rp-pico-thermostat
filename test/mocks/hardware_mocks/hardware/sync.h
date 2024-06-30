#include "stdint.h"
void restore_interrupts(uint32_t status);
uint32_t save_and_disable_interrupts();