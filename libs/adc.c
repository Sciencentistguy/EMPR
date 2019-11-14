#include <lpc17xx_adc.h>
#include <lpc17xx_pinsel.h>
#include "adc.h"


double ADC_ToVoltage(double adcOutpt) {
    return (adcOutpt / (double) 4095) * 3.3;
}

void ADC_InitFunc(){
    PINSEL_CFG_Type t;
    t.Funcnum = 1;
    t.OpenDrain = 0;
    t.Pinmode = 0;
    t.Portnum = 0;
    t.Pinnum = 24;
    PINSEL_ConfigPin(&t);
    ADC_Init(LPC_ADC, 200000);
    ADC_ChannelCmd(LPC_ADC, ADC_CHANNEL, ENABLE);
    ADC_BurstCmd(LPC_ADC, ENABLE);
}

double ADC_GetVoltage() {
        return ADC_ToVoltage(ADC_ChannelGetData(LPC_ADC, ADC_CHANNEL));
}
