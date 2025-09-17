
#ifndef	__LED_H
#define __LED_H
#include <stdint.h>

void led_init(void);
void led_pa1(uint8_t sta);
void led_toggle(void);

#endif
