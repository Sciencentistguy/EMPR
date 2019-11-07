#include <string.h>
#include <stdio.h>
#include <stdlib.h>
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
char buf2[64];

void I2C_SweepBus();

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
