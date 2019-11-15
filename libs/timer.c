#include "lpc17xx_systick.h"
#include "lpc17xx_rit.h"
#include "lpc17xx_timer.h"
#include "timer.h"

volatile unsigned long SysTick_on = 0;
static int RIT_dt = 0;
static int cooldown_count;


void TIMER_EnableSysTick() {
    SYSTICK_Cmd(ENABLE);
    SYSTICK_IntCmd(ENABLE);
    SysTick_Config(SystemCoreClock / 10000);
}

void TIMER_EnableRIT(int dt) {
    RIT_dt = dt;
    RIT_Init(LPC_RIT);
    RIT_TimerConfig(LPC_RIT, dt);
    NVIC_EnableIRQ(RIT_IRQn);
}

void TIMER_SetRIT(int dt) {
    RIT_dt = dt;
    RIT_TimerConfig(LPC_RIT, dt);
}

void TIMER_DisableRIT() {
    NVIC_DisableIRQ(RIT_IRQn);
}

void TIMER_DisableSysTick() {
    SYSTICK_IntCmd(DISABLE);
}

void SysTick_Handler() {
    SysTick_on++;
}

int TIMER_RITGetStatus() {
    return (int) RIT_GetIntStatus(LPC_RIT);
}

void TIMER_Delay(int n) {
    n = n * 10; //Factor in the change to the systick period
    //Maintains the time in ms semantics.
    unsigned long SysTick_count = SysTick_on;

    while ((SysTick_on - SysTick_count) < n);
}

void TIMER_StartCooldown(int n) {
    n *= 10;
    cooldown_count = SysTick_on;
}

int TIMER_CheckCooldown(int n) {
    return !(((SysTick_on - cooldown_count) < n));
}

void TIMER_DelayCallback(int n, timer_callback callback) {
    n = n * 10; //Factor in change to systick period
    //Maintains times in ms semantics.
    unsigned long SysTick_count;
    SysTick_count = SysTick_on;

    if (callback == NULL) {
        while ((SysTick_on - SysTick_count) < n);

    } else {
        while ((SysTick_on - SysTick_count) < n) {
            callback();
        }
    }
}
