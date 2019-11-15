#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <lpc17xx_i2c.h>
#include <lpc17xx_pinsel.h>
#include <lpc17xx_adc.h>
#include <lpc17xx_dac.h>
#include <lpc17xx_timer.h>
#include <lpc17xx_gpdma.h>

#include "libs/serial.h"
#include "libs/led.h"
#include "libs/lcd.h"
#include "libs/keypad.h"
#include "libs/utils.h"
#include "libs/adc.h"
#include "libs/dac.h"
#include "libs/timer.h"

char buf[128];


int main() {
    TIMER_EnableSysTick();
    ADC_InitFunc();
    SERIAL_Init();
    KEYPAD_Init();
    DAC_InitFunc();

    while (1) {
        zero(buf);
        sprintf(buf, "Current voltage: %fV\r\n", ADC_GetVoltage());
        SERIAL_WriteBuf(buf, sizeof(buf));

        if (KEYPAD_GetKeyPressed() == 'B') {
            break;
        }
    }

    DAC_SineWave(3000, 2.5);

    TIMER_Delay(5*1000);

    DAC_SineWave(4000, 1.5);

    for (;;);
}

void EINT3_IRQHandler();
