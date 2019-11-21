#pragma once

#define KEYPAD_ADDR 33

#define COL0 0x7f
#define COL1 0xbf
#define COL2 0xdf
#define COL3 0xef

/**
    Initialise the keypad
*/
void KEYPAD_Init();

/**
    Get the current key being pressed
*/
unsigned char KEYPAD_GetKeyPressed();

/**
    Get the current key being pressed, but return when the key is released
*/
unsigned char KEYPAD_GetBufferedKey();

/**
    Enable interrupt mode on the keypad
*/
void KEYPAD_EnableInterrupt();

/**
    Get Interrupt status
*/
int KEYPAD_GetInterrupt();

/**
    Reset the interrupt on the keypad
*/
void KEYPAD_ClearInterrupt();
