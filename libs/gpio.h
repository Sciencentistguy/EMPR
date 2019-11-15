#pragma once

#define GPIO_DIRECTION_INPUT 0
#define GPIO_DIRECTION_OUTPUT 1

/**
    Enable GPIO on a Port.Pin, with direction.
    `pin` is the number not the binary address.
*/
void GPIO_Init(int port, int pin, int direction);

/**
    Set a Port.Pin to value (0 or 1)
    `pin` is the number not the binary address
*/
void GPIO_SetPin(int port, int pin, int value);
