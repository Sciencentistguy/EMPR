#include <stdio.h>
#include <string.h>
#include <lpc17xx_gpio.h>
#include <lpc17xx_systick.h>

#include "serial.h"
#include "led.h"
#include "gpio.h"


void LED_Clear() {
    for (int i = 0; i < 4; i++) {
        LED_SetLED(i, 0);
    };
}


void LED_WriteInt(int number) {
    LED_Clear();

    if (number & 0b1000) {
        LED_SetLED(3, 1);
    }

    if (number & 0b100) {
        LED_SetLED(2, 1);
    }

    if (number & 0b10) {
        LED_SetLED(1, 1);
    }

    if (number & 0b1) {
        LED_SetLED(0, 1);
    }
}

void LED_SetLED(int led, int state) {
    switch (led) {
        case 0:
            GPIO_Init(1, 18, GPIO_DIRECTION_OUTPUT);
            GPIO_SetPin(1, 18, state);
            break;

        case 1:
            GPIO_Init(1, 20, GPIO_DIRECTION_OUTPUT);
            GPIO_SetPin(1, 20, state);
            break;

        case 2:
            GPIO_Init(1, 21, GPIO_DIRECTION_OUTPUT);
            GPIO_SetPin(1, 21, state);
            break;

        case 3:
            GPIO_Init(1, 23, GPIO_DIRECTION_OUTPUT);
            GPIO_SetPin(1, 23, state);
            break;
    }
}
