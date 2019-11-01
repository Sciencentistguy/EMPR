#pragma once

void SERIAL_ReadBuf(char*, int);

void SERIAL_WriteBuf(char*, int);
void SERIAL_WriteString(char*);

void SERIAL_Init();

char* SERIAL_UcharToBin(unsigned char);
