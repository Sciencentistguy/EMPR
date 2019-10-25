#pragma once

#define LCD_ADDR 59

void LCD_WriteChar(unsigned char, unsigned char);
void LCD_ClearScreen();
void LCD_SendByte(unsigned char);
void LCD_SendBuf(unsigned char*, int);
unsigned char LCD_DecodeCharacter(unsigned char);
void LCD_WriteString(unsigned char*);
void stage_1();
