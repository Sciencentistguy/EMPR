#pragma once

#define ADC_CHANNEL ADC_CHANNEL_1

#define ADC_INT_ENABLE NVIC_EnableIRQ(ADC_IRQn)
#define ADC_INT_DISABLE NVIC_DisableIRQ(ADC_IRQn)
/**
    Initialise the ADC_InitFunc
*/
void ADC_InitFunc();

/**
    Convert the raw ADC data to a number in volts
*/
double ADC_ToVoltage(double raw);

/**
    Get the current voltage on pin 16
*/
double ADC_GetVoltage();

void ADC_InterruptConfig(void (*adc_int_handler)(uint32_t value));

void ADC_Start();

void ADC_Stop();
