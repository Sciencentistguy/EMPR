#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <lpc17xx_i2c.h>
#include <lpc17xx_pinsel.h>
#include <lpc17xx_adc.h>

#include "libs/serial.h"
#include "libs/led.h"
#include "libs/lcd.h"
#include "libs/keypad.h"
#include "libs/delay.h"
#include "libs/i2c.h"
#include "libs/utils.h"
#include "libs/adc.h"

char buf[128];

int main() {
    ADC_InitFunc();
    SERIAL_Init();

    while (1) {
        zero(buf);
        sprintf(buf, "Current voltage: %fV\r\n", ADC_GetVoltage());
        SERIAL_WriteBuf(buf, sizeof(buf));
    }
}

void SysTick_Handler() {
    //stub
}
