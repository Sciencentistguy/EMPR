#pragma once

#define LED0 1<<18
#define LED1 1<<20
#define LED2 1<<21
#define LED3 1<<23
#define ALL_LEDS LED0 | LED1 | LED2 | LED3

void LED_WriteInt(int number);
void SetLED(int led, int state);
