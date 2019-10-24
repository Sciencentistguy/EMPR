#include "serial.h"
#include "led.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <lpc17xx_systick.h>
#include <lpc17xx_i2c.h>
#include <lpc17xx_pinsel.h>

char toggleFlag = 0;
char secondCounter = 0;
char counter = 0;

int main() {
    PINSEL_CFG_Type pinsel_CFG = {.Portnum = 0, .Pinnum = 0, .Funcnum = 3, .OpenDrain = 0};
    PINSEL_ConfigPin(&pinsel_CFG);
    pinsel_CFG.Pinnum = 1;
    serial_init();
    PINSEL_ConfigPin(&pinsel_CFG);
    I2C_Init(LPC_I2C1, 100000);
    I2C_Cmd(LPC_I2C1, 1);
    char buf = 0;
    char buf2[64];
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
            j++;
        }
    }

    memset(buf2, 0, sizeof(buf2));
    sprintf(buf2, "There are %i devices connected to the I2C bus.\r\n", j);
    write_usb_serial_blocking(buf2, sizeof(buf2));
}

void SysTick_Handler() {
    //stub
}
