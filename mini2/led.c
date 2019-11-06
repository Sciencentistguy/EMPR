#include <stdio.h>
#include <string.h>
#include <lpc17xx_gpio.h>
#include <lpc17xx_systick.h>
#include "serial.h"
#include "led.h"


void LED_Clear() {
    for (int i = 0; i < 4; i++) {
        LED_SetLED(i, 0);
    };
}


void LED_WriteInt(int number) {
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
            GPIO_SetDir(1, LED0, 1);
            state ? GPIO_SetValue(1, LED0) : GPIO_ClearValue(1, LED0);
            break;

        case 1:
            GPIO_SetDir(1, LED1, 1);
            state ? GPIO_SetValue(1, LED1) : GPIO_ClearValue(1, LED1);
            break;

        case 2:
            GPIO_SetDir(1, LED2, 1);
            state ? GPIO_SetValue(1, LED2) : GPIO_ClearValue(1, LED2);
            break;

        case 3:
            GPIO_SetDir(1, LED3, 1);
            state ? GPIO_SetValue(1, LED3) : GPIO_ClearValue(1, LED3);
            break;
    }
}
