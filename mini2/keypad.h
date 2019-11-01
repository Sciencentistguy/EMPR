#pragma once

#define KEYPAD_ADDR 33

#define COL0 0x7f
#define COL1 0xbf
#define COL2 0xdf
#define COL3 0xef


unsigned char KEYPAD_GetKeyPressed();
unsigned char KEYPAD_GetBufferedKey();
void KEYPAD_Init();
unsigned char KEYPAD_ReceiveByte();
