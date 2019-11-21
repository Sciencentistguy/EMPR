#include <lpc17xx_adc.h>
#include <lpc17xx_pinsel.h>

#include "adc.h"
#include "pinsel.h"

void (*adc_callback)(uint32_t val);

double ADC_ToVoltage(double adcOutpt) {
    return (adcOutpt / (double) 4095) * 3.3;
}

void ADC_InitFunc() {
    PINSEL_Enable(PINSEL_PORT_1, PINSEL_PIN_24, PINSEL_FUNC_1);
    ADC_Init(LPC_ADC, 200000);
    ADC_ChannelCmd(LPC_ADC, ADC_CHANNEL, ENABLE);
    ADC_BurstCmd(LPC_ADC, ENABLE);
}


void ADC_InterruptConfig(void (*adc_int_handler)(uint32_t value)) {
    adc_callback = adc_int_handler;
    ADC_IntConfig(LPC_ADC, ADC_ADINTEN0, ENABLE);
    ADC_ChannelCmd(LPC_ADC, 0, ENABLE);
}

void ADC_Start() {
    NVIC_EnableIRQ(ADC_IRQn);
    ADC_BurstCmd(LPC_ADC, ENABLE);
    ADC_StartCmd(LPC_ADC, ADC_START_CONTINUOUS);
}

void ADC_Stop() {
    NVIC_DisableIRQ(ADC_IRQn);
    ADC_PowerdownCmd(LPC_ADC, DISABLE);
    ADC_DeInit(LPC_ADC);
}

void ADC_IRQHandler(void) {
    if (ADC_ChannelGetStatus(LPC_ADC, ADC_CHANNEL_0, ADC_DATA_DONE)) {
        adc_callback(ADC_ChannelGetData(LPC_ADC, ADC_CHANNEL_0));
    }
}



double ADC_GetVoltage() {
    return ADC_ToVoltage(ADC_ChannelGetData(LPC_ADC, ADC_CHANNEL));
}
