#include <lpc17xx_gpio.h>
#include <lpc17xx_systick.h>

#define LED1 0b1000000000000000000
#define LED2 0b100000000000000000000
#define LED3 0b1000000000000000000000
#define LED4 0b100000000000000000000000
#define ALL_LEDS LED1 | LED2 | LED3 | LED4

void SysTick_Handler();

char toggleCounter = 0;
char loopCounter = 0;
char flag3 = 0;
int main() {
    SYSTICK_Cmd(ENABLE);
    SYSTICK_IntCmd(ENABLE);
    SYSTICK_InternalInit(100);
    GPIO_SetDir(1, ALL_LEDS, 1);

    for (;;);
}

void SysTick_Handler() {
    if (++loopCounter != 10)
        return;

    loopCounter = 0;

    if (toggleCounter == 0) {
        GPIO_SetValue(1, ALL_LEDS);
        toggleCounter = 1;

    } else {
        GPIO_ClearValue(1, ALL_LEDS);
        toggleCounter = 0;
    }
}
