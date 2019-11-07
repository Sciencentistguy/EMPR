#include "keypad.h"
#include "serial.h"
#include "led.h"
#include "lcd.h"

#include <lpc17xx_i2c.h>
#include <lpc17xx_pinsel.h>
#include <stdio.h>
#include <string.h>

// Internal functions
unsigned char KEYPAD_ReceiveByte();
unsigned char DecodeLocation(unsigned char x, unsigned char y);

void KEYPAD_Init() {
    PINSEL_CFG_Type pinsel_CFG = {.Portnum = 0, .Pinnum = 0, .Funcnum = 3, .OpenDrain = 0};
    PINSEL_ConfigPin(&pinsel_CFG);
    pinsel_CFG.Pinnum = 1;
    PINSEL_ConfigPin(&pinsel_CFG);
    I2C_Init(LPC_I2C1, 100000);
    I2C_Cmd(LPC_I2C1, 1);
}


void KEYPAD_SendByte(unsigned char c) {
    I2C_M_SETUP_Type t;
    t.sl_addr7bit = KEYPAD_ADDR;
    t.retransmissions_max = 2;
    t.rx_data = NULL;
    t.rx_length = 0;
    t.tx_length = 1;
    t.tx_data = &c;
    I2C_MasterTransferData(LPC_I2C1, &t, I2C_TRANSFER_POLLING);
}


unsigned char KEYPAD_GetBufferedKey() {
    unsigned char ret;

    for (;;) {
        ret = KEYPAD_GetKeyPressed();

        if (ret != ' ') {
            break;
        }
    }

    while (KEYPAD_GetKeyPressed() != ' ') {
        (void)0;
    }

    return ret;
}

unsigned char KEYPAD_GetKeyPressed() {
    char addrs[4] = {COL0, COL1, COL2, COL3};
    char rec[4];

    for (int i = 0; i < 4; i++) {
        KEYPAD_SendByte(addrs[i]);
        rec[i] = KEYPAD_ReceiveByte();
    }

    for (int i = 0; i < 4; i++) {
        switch (rec[i] & 0xf) {
            case 0x7:
                return DecodeLocation(i, 0);

            case 0xB:
                return DecodeLocation(i, 1);

            case 0xD:
                return DecodeLocation(i, 2);

            case 0xE:
                return DecodeLocation(i, 3);
        }
    }

    return ' ';
}


unsigned char KEYPAD_ReceiveByte() {
    unsigned char buf;
    I2C_M_SETUP_Type t;
    t.sl_addr7bit = KEYPAD_ADDR;
    t.retransmissions_max = 2;
    t.tx_data = NULL;
    t.tx_length = 0;
    t.rx_length = 1;
    t.rx_data = &buf;
    I2C_MasterTransferData(LPC_I2C1, &t, I2C_TRANSFER_POLLING);
    return buf;
}


unsigned char DecodeLocation(unsigned char x, unsigned char y) {
    switch (y) {
        case 0:
            switch (x) {
                case 0:
                    return '1';

                case 1:
                    return '2';

                case 2:
                    return '3';

                case 3:
                    return 'A';
            }

        case 1:
            switch (x) {
                case 0:
                    return '4';

                case 1:
                    return '5';

                case 2:
                    return '6';

                case 3:
                    return 'B';
            }

        case 2:
            switch (x) {
                case 0:
                    return '7';

                case 1:
                    return '8';

                case 2:
                    return '9';

                case 3:
                    return 'C';
            }

        case 3:
            switch (x) {
                case 0:
                    return '*';

                case 1:
                    return '0';

                case 2:
                    return '#';

                case 3:
                    return 'D';
            }
    }

    return ' ';
}
