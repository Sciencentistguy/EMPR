#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <lpc17xx_i2c.h>
#include <lpc17xx_pinsel.h>

#include "serial.h"
#include "led.h"
#include "lcd.h"
#include "keypad.h"
#include "delay.h"
#include "i2c.h"



char toggleFlag = 0;
char secondCounter = 0;
char counter = 0;
char buf2[64];

int main() {
    I2C_InitFunc();
    SERIAL_Init();
    LCD_Init();
    KEYPAD_Init();
    I2C_SweepBus();
    delay(150);
    LCD_ClearScreen();
    LCD_WriteString("Hello World");
    delay(150);
    LCD_ClearScreen();
    LCD_WriteString("Hello\nWorld");
    delay(150);
    LCD_ClearScreen();

    for (;;) {
        char keyPressed = KEYPAD_GetKeyPressed();

        if (keyPressed != ' ') {
            if (keyPressed == '*') {
                LCD_ClearScreen();
                LCD_ResetPos();

            } else {
                LCD_WriteCharacter(keyPressed);
            }

            while (KEYPAD_GetKeyPressed() != ' ')
                (void) 0;
        }
    }
}


void SysTick_Handler() {
    //stub
}
