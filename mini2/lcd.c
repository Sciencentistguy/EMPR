#include <lpc17xx_i2c.h>
#include <lpc17xx_pinsel.h>
#include <stdio.h>
#include <string.h>

#include "serial.h"
#include "lcd.h"


void LCD_Init() {
    PINSEL_CFG_Type pinsel_CFG = {.Portnum = 0, .Pinnum = 0, .Funcnum = 3, .OpenDrain = 0};
    PINSEL_ConfigPin(&pinsel_CFG);
    pinsel_CFG.Pinnum = 1;
    PINSEL_ConfigPin(&pinsel_CFG);
    I2C_Init(LPC_I2C1, 100000);
    I2C_Cmd(LPC_I2C1, 1);
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


void I2C_SweepBus() {
    unsigned char buf;
    I2C_M_SETUP_Type t;
    int j = 0;
    char buf2[64];

    for (int i = 0; i < 128; i++) {
        t.sl_addr7bit = i & 0b1111111;
        t.tx_data = &buf;
        t.tx_length = sizeof(buf);
        t.retransmissions_max = 2;
        t.rx_length = 0;
        t.rx_data = NULL;

        if (I2C_MasterTransferData(LPC_I2C1, &t, I2C_TRANSFER_POLLING) == SUCCESS) {
            memset(buf2, 0, sizeof(buf2));
            sprintf(buf2, "There is something on address %i\r\n", i);
            SERIAL_WriteBuf(buf2, sizeof(buf2));
            j++;
        }
    }

    memset(buf2, 0, sizeof(buf2));
    sprintf(buf2, "There are %i devices connected to the I2C bus.\r\n", j);
    SERIAL_WriteBuf(buf2, sizeof(buf2));
}

unsigned char LCD_DecodeCharacter(unsigned char c) {
    switch (c) {
        case 'A':
            return 0xC1;

        case 'B':
            return 0xC2;

        case 'C':
            return 0xC3;

        case 'D':
            return 0xC4;

        case 'E':
            return 0xC5;

        case 'F':
            return 0xC6;

        case 'G':
            return 0xC7;

        case 'H':
            return 0xC8;

        case 'I':
            return 0xC9;

        case 'J':
            return 0xCA;

        case 'K':
            return 0xCB;

        case 'L':
            return 0xCC;

        case 'M':
            return 0xCD;

        case 'N':
            return 0xCE;

        case 'O':
            return 0xCF;

        case 'P':
            return 0xD0;

        case 'Q':
            return 0xD1;

        case 'R':
            return 0xD2;

        case 'S':
            return 0xD3;

        case 'T':
            return 0xD4;

        case 'U':
            return 0xD5;

        case 'V':
            return 0xD6;

        case 'W':
            return 0xD7;

        case 'X':
            return 0xD8;

        case 'Y':
            return 0xD9;

        case 'Z':
            return 0xDA;

        case 'a':
            return 0x61;

        case 'b':
            return 0x62;

        case 'c':
            return 0x63;

        case 'd':
            return 0x64;

        case 'e':
            return 0x65;

        case 'f':
            return 0x66;

        case 'g':
            return 0x67;

        case 'h':
            return 0x68;

        case 'i':
            return 0x69;

        case 'j':
            return 0x6A;

        case 'k':
            return 0x6B;

        case 'l':
            return 0x6C;

        case 'm':
            return 0x6D;

        case 'n':
            return 0x6E;

        case 'o':
            return 0x6F;

        case 'p':
            return 0x70;

        case 'q':
            return 0x71;

        case 'r':
            return 0x72;

        case 's':
            return 0x73;

        case 't':
            return 0x74;

        case 'u':
            return 0x75;

        case 'v':
            return 0x76;

        case 'w':
            return 0x77;

        case 'x':
            return 0x78;

        case 'y':
            return 0x79;

        case 'z':
            return 0x7A;

        case '0':
            return 0xB0;

        case '1':
            return 0xB1;

        case '2':
            return 0xB2;

        case '3':
            return 0xB3;

        case '4':
            return 0xB4;

        case '5':
            return 0xB5;

        case '6':
            return 0xB6;

        case '7':
            return 0xB7;

        case '8':
            return 0xB8;

        case '9':
            return 0xB9;

        case ' ':
            return 0xA0;
            
        default: // If in doubt, return '?'
            return 0xBF;
    }
}
