#include <lpc17xx_pinsel.h>
#include <lpc17xx_gpio.h>


#include "libs/serial.h"
#include "libs/timer.h"
#include "libs/keypad.h"
#include "libs/pinsel.h"

int int_counter = 0;
char eint_bool = 0;
static char b;

int main(int argc, char* argv[]) {
    TIMER_EnableSysTick();
    SERIAL_Init();
    KEYPAD_Init();
    KEYPAD_EnableInterrupt();
    SERIAL_Printf("St1");
    b = 0;

    while (b == 0)
        SERIAL_Printf("");

    //keypad_clear_int();
    b = 0;
    SERIAL_Printf("Stage 2");
    TIMER_Delay(1000);

    while (b == 0)
        SERIAL_Printf("");

    SERIAL_Printf("Stage3");
}

void EINT3_IRQHandler() {
    b = 1;
    KEYPAD_ClearInterrupt();
}
