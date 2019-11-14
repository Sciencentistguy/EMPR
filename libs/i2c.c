#include <lpc17xx_pinsel.h>
#include <lpc17xx_i2c.h>
#include <stdio.h>
#include <string.h>

#include "serial.h"

void I2C_InitFunc() {
    PINSEL_CFG_Type pinsel_CFG = {.Portnum = 0, .Pinnum = 0, .Funcnum = 3, .OpenDrain = 0};
    PINSEL_ConfigPin(&pinsel_CFG);
    pinsel_CFG.Pinnum = 1;
    PINSEL_ConfigPin(&pinsel_CFG);
    I2C_Init(LPC_I2C1, 100000);
    I2C_Cmd(LPC_I2C1, 1);
}
