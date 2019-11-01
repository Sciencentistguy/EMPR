#include "serial.h"
#include "led.h"
#include "lcd.h"
#include "keypad.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <lpc17xx_i2c.h>
#include <lpc17xx_pinsel.h>


char toggleFlag = 0;
char secondCounter = 0;
char counter = 0;
char buf2[64];

int main() {
    SERIAL_Init();
    LCD_Init();
    KEYPAD_Init();
    I2C_SweepBus();

    do {
        (void) 0;
    } while (KEYPAD_GetBufferedKey() != '*');

    LCD_ClearScreen();
    LCD_WriteString("Hello World");

    do {
        (void) 0;
    } while (KEYPAD_GetBufferedKey() != '*');

    LCD_ClearScreen();
    LCD_WriteString("Hello\nWorld");

    do {
        (void) 0;
    } while (KEYPAD_GetBufferedKey() != '*');

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
