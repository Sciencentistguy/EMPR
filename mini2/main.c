#include "serial.h"
#include "led.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <lpc17xx_systick.h>
#include <lpc17xx_i2c.h>
#include <lpc17xx_pinsel.h>
#include "lcd.h"


char toggleFlag = 0;
char secondCounter = 0;
char counter = 0;
char buf2[64];

int main() {
    SERIAL_Init();
    PINSEL_CFG_Type pinsel_CFG = {.Portnum = 0, .Pinnum = 0, .Funcnum = 3, .OpenDrain = 0};
    PINSEL_ConfigPin(&pinsel_CFG);
    pinsel_CFG.Pinnum = 1;
    PINSEL_ConfigPin(&pinsel_CFG);
    I2C_Init(LPC_I2C1, 100000);
    I2C_Cmd(LPC_I2C1, 1);
    // Init screen
    unsigned char data[16];
    memset(data, 0, sizeof(data));
    unsigned char* p = data;
    *p++ = 0x00;
    *p++ = 0x34;
    *p++ = 0x0c;
    *p++ = 0x06;
    *p++ = 0x35;
    *p++ = 0x04;
    *p++ = 0x10;
    *p++ = 0x42;
    *p++ = 0x9f;
    *p++ = 0x34;
    *p++ = 0x02;
    *p++ = 0x00;
    *p++ = 0x02;
    LCD_SendBuf(data, sizeof(data));
    // End screen init

    LCD_ClearScreen();
    LCD_WriteString((unsigned char*) "General Kenobi\nYou are a bold 1");
    //LCD_WriteString((unsigned char*) "Hiya\nPal");
}


void SysTick_Handler() {
    //stub
}
