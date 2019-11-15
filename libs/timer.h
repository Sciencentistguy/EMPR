#pragma once

typedef void (*timer_callback)();

/**
    Enable the SysTick timer
*/
void TIMER_EnableSysTick();

/**
    Enable the RIT with some period `dt`
*/
void TIMER_EnableRIT(int dt);

/**
    Set the RIT's timer to `dt`
*/
void TIMER_SetRIT(int dt);

/**
    Disable the RIT
*/
void TIMER_DisableRIT();

/**
    Disable the SysTick timer
*/
void TIMER_DisableSysTick();

/**
    Get RIT Interrupt status.
    Returns an int, where SET=1 and RESET=0
*/
int TIMER_RITGetStatus();

/**
    Delay for an amount of ms before returning control
*/
void TIMER_Delay(int ms);

/**
    Delay for an amount of ms before calling the function pointer `callbackPtr` then returning control
*/
void TIMER_DelayCallback(int ms, timer_callback callbackPtr);

int TIMER_CheckCooldown();
void TIMER_StartCooldown(int n);
