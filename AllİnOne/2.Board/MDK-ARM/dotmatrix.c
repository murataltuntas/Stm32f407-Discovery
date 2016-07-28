#include "dotmatrix.h"
#include "spi.h"



void SendCommand(uint8_t addr, uint8_t param);



void Init(void)
{
	SendCommand(0x09, 0x00);
	SendCommand(0x0A, 0x07);
	SendCommand(0x0B, 0x07);
	SendCommand(0x0C, 0x01);
	SendCommand(0xFF, 0x00);
	
	SendCommand(0x01, 0x00);
	SendCommand(0x02, 0x66);
	SendCommand(0x03, 0xFF);
	SendCommand(0x04, 0xFF);
	SendCommand(0x05, 0x7E);
	SendCommand(0x06, 0x3C);
	SendCommand(0x07, 0x18);
	SendCommand(0x08, 0x00);
}

void SendCommand(uint8_t addr, uint8_t param)
{
	uint8_t tx[2];
	tx[0] = addr;
	tx[1] = param;
	
	HAL_GPIO_WritePin(SPI1_CS_GPIO_Port, SPI1_CS_Pin, GPIO_PIN_RESET);
	HAL_SPI_Transmit(&hspi1, tx, 2, 100);
	HAL_GPIO_WritePin(SPI1_CS_GPIO_Port, SPI1_CS_Pin, GPIO_PIN_SET);	
}


