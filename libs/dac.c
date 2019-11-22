#include <math.h>
#include <lpc17xx_pinsel.h>
#include <lpc17xx_gpdma.h>
#include <lpc17xx_dac.h>

#include "dac.h"
#include "utils.h"
#include "pinsel.h"


void DAC_InitFunc() {
    PINSEL_Enable(PINSEL_PORT_0, PINSEL_PIN_26, PINSEL_FUNC_2);
    DAC_Init(LPC_DAC);
}

void DAC_StartSend(int Frequency, int NumSamples) {
    DAC_CONVERTER_CFG_Type DAC_Conv;
    DAC_Conv.CNT_ENA = SET;
    DAC_Conv.DMA_ENA = SET;
    DAC_SetDMATimeOut(LPC_DAC, 25000000 / (Frequency * NumSamples));
    DAC_ConfigDAConverterControl(LPC_DAC, &DAC_Conv);
    GPDMA_ChannelCmd(1, ENABLE);
}

void DAC_UpdateData(uint16_t data) {
    DAC_UpdateValue(LPC_DAC, data);
}

void DAC_StopSend() {
    DAC_CONVERTER_CFG_Type DAC_Conv;
    DAC_Conv.CNT_ENA = 0;
    DAC_Conv.DMA_ENA = 0;
    DAC_ConfigDAConverterControl(LPC_DAC, &DAC_Conv);
    GPDMA_ChannelCmd(1, DISABLE);
}

void GPDMA_InitFunc(uint32_t* Source, GPDMA_LLI_Type* DMA_Struct, GPDMA_Channel_CFG_Type* GPDMA_Cfg, int NumSamples) {
    DMA_Struct->SrcAddr = (uint32_t)Source; //The address where the list of values are stored
    DMA_Struct->DstAddr = (uint32_t) & (LPC_DAC->DACR); //What memory address to send the data to
    DMA_Struct->NextLLI = (uint32_t)DMA_Struct; //Once the current list is finished, which DMA_Struct to output afterwards
    DMA_Struct->Control = NumSamples | (2 << 18) | (2 << 21) | (1 << 26); //Bit pattern to send to the DMA controller to specify the size of the addresses + to increment the source ptr each time
    GPDMA_Init();
    GPDMA_Cfg->ChannelNum = 1;
    GPDMA_Cfg->SrcMemAddr = (uint32_t)Source;
    GPDMA_Cfg->DstMemAddr = 0;
    GPDMA_Cfg->TransferSize = NumSamples;
    GPDMA_Cfg->TransferWidth = 0;
    GPDMA_Cfg->TransferType = GPDMA_TRANSFERTYPE_M2P;
    GPDMA_Cfg->SrcConn = 0;
    GPDMA_Cfg->DstConn = GPDMA_CONN_DAC; //Point give data to the DAC converter memory address
    GPDMA_Cfg->DMALLI = (uint32_t)DMA_Struct;
    GPDMA_Setup(GPDMA_Cfg);
}

void DAC_SineWave(int frequency, double amplitude) {
    uint32_t sineTable[PRECISION];
    zero(sineTable);
    double MaxAmplitude = amplitude > 3 ? 3 : amplitude;

    for (int i = 0; i < PRECISION; i++) {
        sineTable[i] = (uint32_t)(sin(2 * i * PI / PRECISION) * MaxAmplitude * 9680 + (9680 * MaxAmplitude));
    }

    GPDMA_LLI_Type t;
    GPDMA_Channel_CFG_Type CCFG_Struct;
    GPDMA_InitFunc((uint32_t*)sineTable, &t, &CCFG_Struct, PRECISION);
    DAC_StartSend(frequency, PRECISION);
}
