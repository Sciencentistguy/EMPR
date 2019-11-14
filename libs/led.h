#pragma once

#define LED0 1<<18
#define LED1 1<<20
#define LED2 1<<21
#define LED3 1<<23
#define ALL_LEDS LED0 | LED1 | LED2 | LED3

/**
    Write a number (0-15) to the LEDs to be dislayed in binary
*/
void LED_WriteInt(int number);

/**
    Set a specific LED on (1) or off (0)
*/
void LED_SetLED(int led, int state);

/**
    Turn off all 4 LEDs
*/
void LED_Clear();
