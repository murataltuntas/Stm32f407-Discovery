#ifndef __TWUARTS_H__
#define __TWUARTS_H__



#include <stdbool.h>
#include "usart.h"



void TW_Init(void);
void WriteToRxBuf1(uint8_t add);
void WriteToRxBuf4(uint8_t add);
bool ReadFromRxBuf1(uint8_t* read);
bool ReadFromRxBuf4(uint8_t* read);



#endif





