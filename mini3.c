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
#include <lpc17xx_gpio.h>

#include "libs/serial.h"
#include "libs/led.h"
#include "libs/lcd.h"
#include "libs/keypad.h"
#include "libs/delay.h"
#include "libs/i2c.h"
#include "libs/utils.h"
#include "libs/adc.h"
#include "libs/dac.h"


char buf[128];
volatile char key = ' ';
volatile char prevKey = ' ';

void IRQInit() {
    LPC_PINCON->PINSEL4 |= 0x4000000; //
    LPC_PINCON->PINSEL0 &= ~(3 << 20); //
    LPC_SC->EXTMODE = 1 << 3;
    LPC_SC->EXTPOLAR = 1 << 3;
    LPC_GPIO0->FIODIR &= ~(1 << 10); //
    LPC_GPIOINT->IO0IntClr = (1 << 10);
    LPC_GPIOINT->IO0IntEnF |= (1 << 10); //
    LPC_SC->EXTINT = 1 << 3; //Clear Pending Interrupts
    //key = ' ';
    //buttonpress = 0;
    //NVIC_SetPriority(EINT3_IRQn, 0x00);
    PIO_IntCmd(0, 1 << 23, 1);
    NVIC_EnableIRQ(EINT3_IRQn);
    __enable_irq();
}



int main() {
    ADC_InitFunc();
    SERIAL_Init();
    KEYPAD_Init();
    IRQInit();
    DAC_InitFunc();
    //while (1) {
    //    zero(buf);
    //    sprintf(buf, "Current voltage: %fV\r\n", ADC_GetVoltage());
    //    SERIAL_WriteBuf(buf, sizeof(buf));
    //    if (KEYPAD_GetKeyPressed() == 'B') {
    //        break;
    //    }
    //}
    //DAC_SineWave(3000, 2.5);
    //while (KEYPAD_GetKeyPressed() != 'A')
    //    (void) 0;
    //DAC_SineWave(4000, 1.5);
    //zero(buf);
    SERIAL_WriteString("go\r\n");
    while (1) {
        sprintf(buf, "%c\r\n", key);
        SERIAL_WriteBuf(buf, sizeof(buf));
    }
}

void EINT3_IRQHandler(void) {

    key = KEYPAD_GetKeyPressed();

    if (key != prevKey && key != ' ') {
        prevKey = key;

    } else if (key == ' ') {
        prevKey = ' ';
    }

    LED_WriteInt(15);
    GPIO_ClearInt(1, 1<<28);
}

//void EINT3_IRQHandler() {
//    LPC_SC->EXTINT = 1 << 3;
//    LPC_GPIOINT->IO0IntClr = (1 << 10);
//    LED_WriteInt(15);
//    SERIAL_WriteString("I'mHERE\r\n");
//}

void SysTick_Handler() {
    //stub
}
