#pragma once

#define LCD_ADDR 59


/**
    Initialise the LCD
*/
void LCD_Init();

/**
    Write a single character to the LCD
*/
void LCD_WriteCharacter(unsigned char character);

/**
    Clear the LCD screen
*/
void LCD_ClearScreen();

/**
    Write a c-string literal (char*) to the lcd.
    A '\\n' character will move to the beginning of the next line.
*/
void LCD_WriteString(char* str);

/**
    Reset the position on the LCD screen
    To be used with LCD_WriteCharacter()
*/
void LCD_ResetPos();

/**
    Write a buffer (char*) to the LCD
*/
void LCD_WriteBuf(char* buf, int size);
