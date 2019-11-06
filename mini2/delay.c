/******************************************************************************
* File:             delay.c
*
* Author:           Jamie Quigley  
* Created:          11/06/19 
* Description:      A delay function
*****************************************************************************/

void delay(unsigned long tick) {
    for (unsigned long j = 0; j < tick; j++) {
        for (unsigned int i = 0; i < 0x100000; i++) {
            (void) 0;
        }
    }
}
