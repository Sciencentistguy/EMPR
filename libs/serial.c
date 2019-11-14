#include <lpc17xx_uart.h>
#include <lpc17xx_pinsel.h>
#include <string.h>

#include "serial.h"
#include "pinsel.h"


void SERIAL_ReadBuf(char* buf, int length) {
    UART_Receive(LPC_UART0, (unsigned char*)buf, length, NONE_BLOCKING);
}

void SERIAL_WriteBuf(char* buf, int length) {
    UART_Send(LPC_UART0, (unsigned char*)buf, length, BLOCKING);
}

void SERIAL_WriteString(char* str) {
    SERIAL_WriteBuf(str, strlen(str));
}

void SERIAL_Init(void) {
    UART_CFG_Type UARTConfigStruct;
    UART_FIFO_CFG_Type UARTFIFOConfigStruct;
    PINSEL_Enable(PINSEL_PORT_0, PINSEL_PIN_2, PINSEL_FUNC_1);
    PINSEL_Enable(PINSEL_PORT_0, PINSEL_PIN_3, PINSEL_FUNC_1);
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
