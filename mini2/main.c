#include "serial.h"
#include "led.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <lpc17xx_i2c.h>
#include <lpc17xx_pinsel.h>
#include "lcd.h"


char toggleFlag = 0;
char secondCounter = 0;
char counter = 0;
char buf2[64];

int main() {
    SERIAL_Init();
    LCD_ClearScreen();
    LCD_WriteString("Hello World");
    LCD_WriteString("Hello\nWorld");
}


void SysTick_Handler() {
    //stub
}
