#pragma once

/**
 * Initialise the serial connection
 */
void SERIAL_Init();

/**
 * Read a buffer (char*) from serial
 */
void SERIAL_ReadBuf(char* buf, int size);

/**
 * Write a buffer (char*) to serial
 */
void SERIAL_WriteBuf(char* buf, int size);

/**
 * Write a c-string literal (char*) to serial
 */
void SERIAL_WriteString(char*);
