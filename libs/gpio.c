#include <lpc17xx_gpio.h>

#include "gpio.h"

void GPIO_Init(int port, int pin, int direction) {
    GPIO_SetDir(port, 1 << pin, direction);
}

void GPIO_SetPin(int port, int pin, int value) {
    if (!value) {
        GPIO_ClearValue(port, 1 << pin);

    } else {
        GPIO_SetValue(port, 1 << pin);
    }
}
