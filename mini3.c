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
#include <lpc17xx_nvic.h>

#include "libs/serial.h"
#include "libs/led.h"
#include "libs/lcd.h"
#include "libs/keypad.h"
#include "libs/utils.h"
#include "libs/adc.h"
#include "libs/dac.h"
#include "libs/timer.h"

char buf[128];
static char b;

volatile uint32_t adc_val;
volatile uint8_t read = 0;
void ADC_Int(uint32_t val);

int main() {
    TIMER_EnableSysTick();
    ADC_InitFunc();
    SERIAL_Init();
    KEYPAD_Init();
    KEYPAD_EnableInterrupt();
    DAC_InitFunc();
    b = 0;

    while (b == 0) {
        SERIAL_Printf("Current voltage: %fV\r\n", ADC_GetVoltage());
    }

    b = 0;
    KEYPAD_ClearInterrupt();
    DAC_SineWave(3000, 2.5);
    TIMER_Delay(3 * 1000);
    DAC_SineWave(4000, 1.5);
    TIMER_Delay(3 * 1000);
    DAC_SineWave(2500, 1);
    TIMER_Delay(3 * 1000);
    b = 0;

    while (b == 0)
        (void) 0;

    DAC_StopSend();
    SERIAL_Printf("Stage 3\r\n");
    //for (;;);
    ADC_InterruptConfig(ADC_Int);
    ADC_Start();

    while (1) {
        if (!read)
            continue;

        DAC_UpdateData(adc_val * (1024 / 4096));
        read = 0;
        ADC_INT_ENABLE;
    }
}

void ADC_Int(uint32_t val) {
    adc_val = val;
    read = 1;
    ADC_INT_DISABLE;
}

void EINT3_IRQHandler() {
    b = 1;
    KEYPAD_ClearInterrupt();
}
