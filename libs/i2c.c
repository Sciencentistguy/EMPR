#include <lpc17xx_pinsel.h>
#include <lpc17xx_i2c.h>
#include <stdio.h>
#include <string.h>

#include "serial.h"

void I2C_InitFunc(){
    PINSEL_CFG_Type pinsel_CFG = {.Portnum = 0, .Pinnum = 0, .Funcnum = 3, .OpenDrain = 0};
    PINSEL_ConfigPin(&pinsel_CFG);
    pinsel_CFG.Pinnum = 1;
    PINSEL_ConfigPin(&pinsel_CFG);
    I2C_Init(LPC_I2C1, 100000);
    I2C_Cmd(LPC_I2C1, 1);
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
