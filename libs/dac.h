#pragma once

#include <lpc17xx_gpdma.h>

#define PRECISION 147 /*clear the lobby*/
#define PI 3.1415926535897932384626433832

/**
 * Initialise the DAC on pin 26 (18)
 */
void DAC_InitFunc();

/**
 * Write out the data in the GPDMA buffer to the DAC
 */
void DAC_StartSend(int frequency, int size);

/**
 * Initialise the GPDMA with buffer buf
 */
void GPDMA_InitFunc(uint32_t* buf, GPDMA_LLI_Type* DMA_Struct, GPDMA_Channel_CFG_Type* GPDMA_Cfg, int size);


/**
 * Output a sine wave with specified frequency and amplitude
 */
void DAC_SineWave(int frequency, double amplitude);
