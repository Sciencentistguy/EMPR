#include <stdio.h>
#include <string.h>
#include <lpc17xx_gpio.h>
#include <lpc17xx_systick.h>
#include "serial.h"
#include "led.h"

#define LED0 1<<18
#define LED1 1<<20
#define LED2 1<<21
#define LED3 1<<23
#define ALL_LEDS LED0 | LED1 | LED2 | LED3


void LED_WriteInt(int number) {
    char bin[8];
    memset(bin, 0, sizeof(bin));
    sprintf(bin, "0000");

    for (int i = 0; i < 4; i++) {
        SetLED(i, 0);
    };

    if (number & 0b1000) {
        SetLED(3, 1);
        bin[0] = '1';
    }

    if (number & 0b100) {
        SetLED(2, 1);
        bin[1] = '1';
    }

    if (number & 0b10) {
        SetLED(1, 1);
        bin[2] = '1';
    }

    if (number & 0b1) {
        SetLED(0, 1);
        bin[3] = '1';
    }

    char buf[64];
    memset(buf, 0, sizeof(buf));
    sprintf(buf, "Writing leds with number %02i (dec), 0x%X (hex), 0b%s (bin). \r\n", number, number, bin);
    write_usb_serial_blocking(buf, sizeof(buf));
}

void SetLED(int led, int state) {
//    char buf[128];
//    memset(buf, 0, sizeof(buf));
//    sprintf(buf, "Setting LED%i to %i\n", led, state);
//    write_usb_serial_blocking(buf, sizeof(buf));
    switch (led) {
        case 0:
            GPIO_SetDir(1, LED0, 1);

            if (state == 1) {
                GPIO_SetValue(1, LED0);

            } else {
                GPIO_ClearValue(1, LED0);
            }

            break;

        case 1:
            GPIO_SetDir(1, LED1, 1);

            if (state == 1) {
                GPIO_SetValue(1, LED1);

            } else {
                GPIO_ClearValue(1, LED1);
            }

            break;

        case 2:
            GPIO_SetDir(1, LED2, 1);

            if (state == 1) {
                GPIO_SetValue(1, LED2);

            } else {
                GPIO_ClearValue(1, LED2);
            }

            break;

        case 3:
            GPIO_SetDir(1, LED3, 1);

            if (state == 1) {
                GPIO_SetValue(1, LED3);

            } else {
                GPIO_ClearValue(1, LED3);
            }

            break;
    }
}
