#pragma once

/**
    Convert an 8-bit number (unsigned char) to an 8-bit binary string
*/
char* CharToBinary(unsigned char number);

/**
    Zero-out a buffer
*/
void zero(void* buf);

/**
    Delay by an arbitary amount of time. 150 seems to be about 1s
*/
void delay(int delay);
