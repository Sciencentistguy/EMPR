#pragma once

#define KEYPAD_ADDR 33

#define COL0 0x7f
#define COL1 0xbf
#define COL2 0xdf
#define COL3 0xef


unsigned char KEYPAD_GetKeyPressed();
void KEYPAD_Poll();
unsigned char KEYPAD_ReceiveByte();
