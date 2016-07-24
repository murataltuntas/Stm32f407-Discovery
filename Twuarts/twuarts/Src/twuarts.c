#include "twuarts.h"



#define BUF_SIZE 128



uint8_t rx1;
uint8_t rx4;

uint8_t rxBuf1[BUF_SIZE];
uint32_t rx1Read = 0, rx1Write = 0;

uint8_t rxBuf4[BUF_SIZE];
uint32_t rx4Read = 0, rx4Write = 0;



void TW_Init(void)
{
	HAL_UART_Receive_IT(&huart1, &rx1, 1);
	HAL_UART_Receive_IT(&huart4, &rx4, 1);
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{	
	if (huart == &huart1)
	{
		WriteToRxBuf1(rx1);
		
		HAL_UART_Receive_IT(&huart1, &rx1, 1);
	}
	else if (huart == &huart4)
	{
		WriteToRxBuf4(rx4);

		HAL_UART_Receive_IT(&huart4, &rx4, 1);
	}
}

void WriteToRxBuf1(uint8_t add)
{
	if ((rx1Read == 1 && rx1Write == BUF_SIZE - 1) || (rx1Read == rx1Write + 1))
	{
		// buffer overflow
		rx1Read = 0;
		rx1Write = 0;
		
		return;
	}
	
	if (rx1Write == 0)
	{
		// empty
		rx1Write = 1;
		rx1Read = 1;
	}
	else if (rx1Write == BUF_SIZE - 1)
	{
		// round around the end
		rx1Write = 1;
	}
	else
	{
		rx1Write++;
	}
	
	rxBuf1[rx1Write] = add;
}

void WriteToRxBuf4(uint8_t add)
{

	if ((rx4Read == 1 && rx4Write == BUF_SIZE - 1) || (rx4Read == rx4Write + 1))
	{
		// buffer overflow
		rx4Read = 0;
		rx4Write = 0;
		
		return;
	}
	
	if (rx4Write == 0)
	{
		// empty
		rx4Write = 1;
		rx4Read = 1;
	}
	else if (rx4Write == BUF_SIZE - 1)
	{
		// round about the end
		rx4Write = 1;
	}
	else
	{
		rx4Write++;
	}
	
	rxBuf4[rx4Write] = add;
}

bool ReadFromRxBuf1(uint8_t* read)
{
	if (rx1Read == 0)
	{
		// underflow
		return false;
	}
	else
	{
		HAL_NVIC_DisableIRQ(USART1_IRQn);
		
		*read = rxBuf1[rx1Read];
		
		if (rx1Read == rx1Write)
		{
			// last element
			rx1Write = 0;
			rx1Read = 0;
		}
		else if (rx1Read == BUF_SIZE - 1)
		{
			// round
			rx1Read = 1;
		}
		else
		{
			rx1Read++;
		}
		
		HAL_NVIC_EnableIRQ(USART1_IRQn);
	}
	
	return true;
}

bool ReadFromRxBuf4(uint8_t* read)
{
	if (rx4Read == 0)
	{
		// underflow
		return false;
	}
	else
	{
		HAL_NVIC_DisableIRQ(UART4_IRQn);
		
		*read = rxBuf4[rx4Read];
		
		if (rx4Read == rx4Write)
		{
			// last element
			rx4Write = 0;
			rx4Read = 0;
		}
		else if (rx4Read == BUF_SIZE - 1)
		{
			// round
			rx4Read = 1;
		}
		else
		{
			rx4Read++;
		}
		
		HAL_NVIC_EnableIRQ(UART4_IRQn);
	}
	
	return true;
}

void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)
{
	if (huart == &huart1)
	{
		printf("usart1 error");
	}
	else if (huart == &huart4)
	{
		printf("uart4 error");
	}
}

