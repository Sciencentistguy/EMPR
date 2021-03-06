#include <lpc17xx_i2c.h>
#include <lpc17xx_pinsel.h>
#include <stdio.h>
#include <string.h>

#include "serial.h"
#include "lcd.h"
#include "pinsel.h"

//internal functions
void LCD_SendByte(unsigned char byte);
void LCD_SendBuf(unsigned char* buf, int size);
unsigned char LCD_DecodeCharacter(unsigned char c);
void LCD_WriteChar(unsigned char location, unsigned char character);

char pos = 0;

void LCD_Init() {
    PINSEL_Enable(PINSEL_PORT_0, PINSEL_PIN_0, PINSEL_FUNC_3);
    PINSEL_Enable(PINSEL_PORT_0, PINSEL_PIN_1, PINSEL_FUNC_3);
    I2C_Init(LPC_I2C1, 100000);
    I2C_Cmd(LPC_I2C1, ENABLE);
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
    LCD_ClearScreen();
}

void LCD_SendBuf(unsigned char* buf, int size) {
    I2C_M_SETUP_Type t;
    t.sl_addr7bit = LCD_ADDR;
    t.tx_data = buf;
    t.tx_length = size;
    t.retransmissions_max = 2;
    t.rx_length = 0;
    t.rx_data = NULL;
    I2C_MasterTransferData(LPC_I2C1, &t, I2C_TRANSFER_POLLING);
}

void LCD_WriteBuf(char* str, int size) {
    for (int i = 0; i < size; i++) {
        LCD_WriteChar(0x80 + i, str[i]);
    }
}

void LCD_WriteString(char* str) {
    char c, j;
    j = 0x80;

    for (int i = 0;; i++) {
        c = str[i];

        if (c == '\0')
            break;

        if (c == '\n') {
            j = 0xA8;
            continue;
        }

        LCD_WriteChar(j, LCD_DecodeCharacter(c));
        j++;
    };
}

void LCD_ResetPos() {
    pos = 0x80;
}

void LCD_WriteCharacter(unsigned char c) {
    if (pos < 0x80u || pos > (unsigned char)0x80 + 16)
        LCD_ResetPos();

    LCD_WriteChar(pos, LCD_DecodeCharacter(c));
    pos++;
}

void LCD_ClearScreen() {
    LCD_SendByte(0b1000);

    for (int i = 0; i < 64; i++)
        LCD_WriteChar(0x80 + i, 0xA0);

    LCD_SendByte(0b1100);
}

void LCD_SendByte(unsigned char b1) {
    LCD_SendBuf(&b1, 1);
}

void LCD_WriteChar(unsigned char location, unsigned char character) {
    unsigned char buf[2];
    buf[0] = 0x00;
    buf[1] = location;
    LCD_SendBuf(buf, sizeof(buf));
    buf[0] = 0x40;
    buf[1] = character;
    LCD_SendBuf(buf, sizeof(buf));
}


unsigned char LCD_DecodeCharacter(unsigned char c) {
    if ('A' <= c && c <= 'Z') {
        return c + 0x80;
    }

    if ('a' <= c && c <= 'z') {
        return c;
    }

    if ('0' <= c && c <= '9') {
        return 0xb0 | (c & 0xf);
    }

    switch (c) {
        case ' ':
            return 0xA0;

        case '#':
            return 0xA3;

        case '*':
            return 0xAA;

        case '+':
            return 0xAB;

        case '-':
            return 0xAD;

        case '/':
            return 0xAF;

        case '=':
            return 0xBD;

        default:
            return 0xBF; // Default to '?'
    }
}
