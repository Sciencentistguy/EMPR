#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <lpc17xx_systick.h>

#include "libs/serial.h"
#include "libs/led.h"

char toggleFlag = 0;
char secondCounter = 0;
char counter = 0;

int main() {
    SYSTICK_Cmd(ENABLE);
    SYSTICK_IntCmd(ENABLE);
    SYSTICK_InternalInit(100);
    SERIAL_Init();
    char buf[20];
    memset(buf, 0, sizeof(buf));
    sprintf(buf, "Starting Count\r\n");
    SERIAL_WriteBuf(buf, sizeof(buf));
    for (;;);
}

void SysTick_Handler() {
    if (++secondCounter != 10)
        return;

    if (counter < 16) {
        secondCounter = 0;
        LED_WriteInt(counter);
    }

    if (++counter > 16) {
        for (int i = 0; i < 4; i++)
            LED_SetLED(i, 0);

        char buf[16];
        memset(buf, 0, sizeof(buf));
        sprintf(buf, "Finished Count\r\n");
        SERIAL_WriteBuf(buf, sizeof(buf));
        exit(0);
    }
}
