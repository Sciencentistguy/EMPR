#pragma once

#define LED0 1<<18
#define LED1 1<<20
#define LED2 1<<21
#define LED3 1<<23
#define ALL_LEDS LED0 | LED1 | LED2 | LED3

/**
 * Write a number between 0-15 inclusive to the 4 bit LED output.
 */
void LED_WriteInt(unsigned char number);

/**
 * Set a specific LED to a specific state.
 */
void SetLED(unsigned char led, unsigned char state);
