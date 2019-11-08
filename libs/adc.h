#pragma once

#define ADC_CHANNEL ADC_CHANNEL_1

/**
 * Initialise the ADC_InitFunc
 */
void ADC_InitFunc();

/**
 * Convert the raw ADC data to a number in volts
 */
double ADC_ToVoltage(double raw);

/**
 * Get the current voltage on pin 16
 */
double ADC_GetVoltage();
