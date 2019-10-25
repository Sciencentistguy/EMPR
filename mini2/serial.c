#include <lpc17xx_uart.h>
#include <lpc17xx_pinsel.h>
#include "lpc_types.h"
#include "serial.h"


void SERIAL_ReadBuf(char* buf, int length) {
    UART_Receive(LPC_UART0, (unsigned char*)buf, length, NONE_BLOCKING);
}

void SERIAL_WriteBuf(char* buf, int length) {
    UART_Send(LPC_UART0, (unsigned char*)buf, length, BLOCKING);
}

void SERIAL_WriteString(char* str) {
    int i;

    for (i = 0;; i++) {
        if (str[i] == '\0')
            break;
    }

    SERIAL_WriteBuf(str, i);
}

void SERIAL_Init(void) {
    UART_CFG_Type UARTConfigStruct;
    UART_FIFO_CFG_Type UARTFIFOConfigStruct;
    PINSEL_CFG_Type PinCfg = {.Funcnum = 1, .OpenDrain = 0, .Pinmode = 0, .Portnum = 0, .Pinnum = 2};
    PINSEL_ConfigPin(&PinCfg);
    PinCfg.Pinnum = 3;
    PINSEL_ConfigPin(&PinCfg);
    /*  Initialize UART Configuration parameter structure to default state:
        - Baudrate = 9600bps
        - 8 data bit
        - 1 Stop bit
        - None parity
    */
    UART_ConfigStructInit(&UARTConfigStruct);
    /*  Initialize FIFOConfigStruct to default state:
        - FIFO_DMAMode = DISABLE
        - FIFO_Level = UART_FIFO_TRGLEV0
        - FIFO_ResetRxBuf = ENABLE
        - FIFO_ResetTxBuf = ENABLE
        - FIFO_State = ENABLE
    */
    UART_FIFOConfigStructInit(&UARTFIFOConfigStruct);
    // Built the basic structures, lets start the devices/
    // USB serial
    UART_Init(LPC_UART0, &UARTConfigStruct);         // Initialize UART0 peripheral with given to corresponding parameter
    UART_FIFOConfig(LPC_UART0, &UARTFIFOConfigStruct);   // Initialize FIFO for UART0 peripheral
    UART_TxCmd(LPC_UART0, ENABLE);           // Enable UART Transmit
}
