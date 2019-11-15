#include <lpc17xx_pinsel.h>
#include <lpc17xx_gpio.h>


#include "libs/serial.h"
#include "libs/timer.h"
#include "libs/keypad.h"
#include "libs/pinsel.h"

int int_counter = 0;
char eint_bool = 0;

void KEYPAD_SendByte(unsigned char c);

void keypad_enable_int(void) {
    // ensure GPIO functionality is set on that pin.
    PINSEL_Enable(PINSEL_PORT_0, PINSEL_PIN_23, PINSEL_FUNC_0);
    /* enable interrupts by sending 1's to quasi-bidirectional pins */
    char clean = 0xf0;
    KEYPAD_SendByte(0xf0);
    // Enable GPIO interrupts on P0.23
    // on falling edge
    GPIO_IntCmd(0, 1 << 23, 1);
    // Enable the EINT3 Handler
    NVIC_EnableIRQ(EINT3_IRQn);
}

void keypad_clear_int(void) {
    GPIO_ClearInt(0, 1 << 23);
}

int keypad_get_int(void) {
    return GPIO_GetIntStatus(0, 23, 1);
}
int main(int argc, char* argv[]) {
    TIMER_EnableSysTick();
    SERIAL_Init();
    KEYPAD_Init();
    keypad_enable_int();

    while (1){
        TIMER_Delay(100);
        SERIAL_WriteString(" \r\n");

    }
}

void EINT3_IRQHandler() {
    //char buf[2];
    //buf[0] = KEYPAD_GetKeyPressed();
    //buf[1] = '\0';
    //SERIAL_WriteString(buf);
    SERIAL_WriteString("DONE");
    keypad_clear_int();
}
