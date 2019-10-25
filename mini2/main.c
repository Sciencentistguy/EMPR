#include "serial.h"
#include "led.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <lpc17xx_systick.h>
#include <lpc17xx_i2c.h>
#include <lpc17xx_pinsel.h>

#define LCD_ADDR 59

char toggleFlag = 0;
char secondCounter = 0;
char counter = 0;
void stage_1();
char buf2[64];
void LCD_WriteChar(unsigned char, unsigned char);
void LCD_ClearScreen();
void LCD_SendByte(unsigned char);

int main() {
    SERIAL_Init();
    PINSEL_CFG_Type pinsel_CFG = {.Portnum = 0, .Pinnum = 0, .Funcnum = 3, .OpenDrain = 0};
    PINSEL_ConfigPin(&pinsel_CFG);
    pinsel_CFG.Pinnum = 1;
    PINSEL_ConfigPin(&pinsel_CFG);
    I2C_Init(LPC_I2C1, 100000);
    I2C_Cmd(LPC_I2C1, 1);
    // Init screen
    LCD_SendByte(0x00);
    LCD_SendByte(0x00);
    LCD_SendByte(0x34);
    LCD_SendByte(0x0c);
    LCD_SendByte(0x06);
    LCD_SendByte(0x35);
    LCD_SendByte(0x04);
    LCD_SendByte(0x10);
    LCD_SendByte(0x42);
    LCD_SendByte(0x9f);
    LCD_SendByte(0x34);
    LCD_SendByte(0x02);
    LCD_SendByte(0x00);
    LCD_SendByte(0x01);
    // End init
    LCD_ClearScreen();
    LCD_WriteChar(0x80, 0xC8);
    LCD_WriteChar(0x81, 0x65);
    LCD_WriteChar(0x82, 0xEC);
    LCD_WriteChar(0x83, 0xEC);
    LCD_WriteChar(0x84, 0xEF);
    LCD_WriteChar(0x86, 0xD7);
    LCD_WriteChar(0x87, 0xEF);
    LCD_WriteChar(0x88, 0x72);
    LCD_WriteChar(0x89, 0xEC);
    LCD_WriteChar(0x8a, 0x64);
}

void LCD_ClearScreen() {
    LCD_SendByte(0b1000);

    for (int i = 0; i < 32; i++)
        LCD_WriteChar(0x80 + i, 0xA0);

    LCD_SendByte(0b1100);
}

void LCD_SendByte(unsigned char b1) {
    I2C_M_SETUP_Type t;
    t.sl_addr7bit = LCD_ADDR;
    t.tx_data = &b1;
    t.tx_length = sizeof(b1);
    t.retransmissions_max = 2;
    t.rx_length = 0;
    t.rx_data = NULL;
    I2C_MasterTransferData(LPC_I2C1, &t, I2C_TRANSFER_POLLING);
}

void LCD_WriteChar(unsigned char location, unsigned char character) {
    LCD_SendByte(0x00);
    LCD_SendByte(location);
    LCD_SendByte(0x40);
    LCD_SendByte(character);
}

void stage_1() {
    char buf;
    I2C_M_SETUP_Type t;
    int j = 0;
    LED_WriteInt(15);
    /*
        t.retransmissions_count = 0;
        t.tx_count = 0;
        t.rx_count = 0;
    */
    LED_WriteInt(1);

    for (int i = 0; i < 128; i++) {
        t.sl_addr7bit = i & 0b1111111;
        t.tx_data = (uint8_t*)&buf;
        t.tx_length = 1; // sizeof(buf);
        t.retransmissions_max = 2;
        t.rx_length = 0;
        t.rx_data = NULL;
        LED_WriteInt(0);

        if (I2C_MasterTransferData(LPC_I2C1, &t, I2C_TRANSFER_POLLING) == SUCCESS) {
            memset(buf2, 0, sizeof(buf2));
            sprintf(buf2, "there is something on address %i\r\n", i);
            SERIAL_WriteBuf(buf2, sizeof(buf2));
            j++;
        }
    }

    memset(buf2, 0, sizeof(buf2));
    sprintf(buf2, "There are %i devices connected to the I2C bus.\r\n", j);
    SERIAL_WriteBuf(buf2, sizeof(buf2));
}
void SysTick_Handler() {
    //stub
}
