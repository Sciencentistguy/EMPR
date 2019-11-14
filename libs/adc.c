#include <lpc17xx_adc.h>
#include <lpc17xx_pinsel.h>

#include "adc.h"
#include "pinsel.h"


double ADC_ToVoltage(double adcOutpt) {
    return (adcOutpt / (double) 4095) * 3.3;
}

void ADC_InitFunc() {
    PINSEL_Enable(PINSEL_PORT_1, PINSEL_PIN_24, PINSEL_FUNC_1);
    ADC_Init(LPC_ADC, 200000);
    ADC_ChannelCmd(LPC_ADC, ADC_CHANNEL, ENABLE);
    ADC_BurstCmd(LPC_ADC, ENABLE);
}

double ADC_GetVoltage() {
    return ADC_ToVoltage(ADC_ChannelGetData(LPC_ADC, ADC_CHANNEL));
}
