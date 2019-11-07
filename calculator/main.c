#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <lpc17xx_i2c.h>
#include <lpc17xx_pinsel.h>

#include "../libs/serial.h"
#include "../libs/led.h"
#include "../libs/lcd.h"
#include "../libs/keypad.h"
#include "../libs/delay.h"
#include "../libs/i2c.h"



char toggleFlag = 0;
char secondCounter = 0;
char counter = 0;
char buf[128];
char buf2[64];

int calculate(char*);

int main() {
    I2C_InitFunc();
    SERIAL_Init();
    LCD_Init();
    KEYPAD_Init();
    char* p = buf;
    memset(buf, 0, sizeof(buf));
    LCD_ClearScreen();

    while (1) {
        char keyPressed = KEYPAD_GetBufferedKey();

        switch (keyPressed) {
            case 'A':
                keyPressed = '+';
                break;

            case 'B':
                keyPressed = '-';
                break;

            case 'C':
                keyPressed = '*';
                break;

            case 'D':
                keyPressed = '/';
                break;

            default:
                break;
        }

        if (keyPressed == '#') {
            LCD_WriteCharacter('=');
            break;
        }

        LCD_WriteCharacter(keyPressed);
        *(p++) = keyPressed;
    }

    int result = calculate(buf);
    memset(buf2, 0, sizeof(buf2));
    sprintf(buf2, "\n%i", result);
    LCD_WriteString(buf2);
}

int calculate(char* input) {
    int to, index, number_length, result;
    char number_string[64];
    int len = strlen(input);
    char op = 0;
    int number;
    len = strlen(input);
    index = 0;
    number_length = 0;

    // Left operands '-1' or '+6' etc

    if (input[index] == '+' || input[index] == '-') // Copy +/-
        *(number_string + number_length++) = *(input + index++);

    for (; isdigit(*(input + index)) ; index++) // Copy digits
        *(number_string + number_length++) = *(input + index);

    *(number_string + number_length) = '\0';  // Add null terminator

    // If we have a left operand, the length of number_string will be > 0. In this case convert to an int
    if (number_length > 0)
        result = atoi(number_string);

    // Now look for operator-number combinations
    for (; index < len;) {
        op = *(input + index++);
        number_length = 0;

        if (input[index] == '+' || input[index] == '-') // Copy +/-
            *(number_string + number_length++) = *(input + index++);

        for (; isdigit(*(input + index)) ; index++) // Copy digits
            *(number_string + number_length++) = *(input + index);

        *(number_string + number_length) = '\0'; // Add null terminator
        number = atoi(number_string);

        switch (op) {
            case '+':      // Addition
                result += number;
                break;

            case '-':      // Subtraction
                result -= number;
                break;

            case '*':      // Multiplication
                result *= number;
                break;

            case '/':      // Division        CLEAR THE LOBBY

                // Check second operand for zero
                if (number == 0)
                    LCD_WriteString("\nNo div/0");

                else
                    result /= number;

                break;
        }
    }

    return result;
}

void SysTick_Handler() {
    //stub
}
