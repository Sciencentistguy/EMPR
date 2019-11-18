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
    SERIAL_WriteString("Starting Count.\r\n");

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

        SERIAL_WriteString("Finished Count");
        exit(0);
    }
}
