#include "furkan.h"
#include <stdint.h>
#include "usart.h"


#define BUFF_SIZE					1024


uint8_t terminalRx, pairRx;
char hello[] = "hello\r\n";
uint8_t cbufTerm[BUFF_SIZE], cbufPair[BUFF_SIZE];

static uint16_t Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint16_t BufferLength);

void FRK_Init(void)
{
	HAL_UART_Transmit_IT(&huart1, (uint8_t*)hello, 7);
	HAL_UART_Transmit_IT(&huart2, (uint8_t*)hello, 7);
	HAL_UART_Receive(&huart1, (uint8_t *)&terminalRx, 1, 1);
	HAL_UART_Receive(&huart2, (uint8_t *)&pairRx, 1, 1);
}

// usart1'den gelen terminalden gelir
// usart2'ye (diger karta) yönlendilir
// usart2'den gelen diger karttan gelir
// usart1'den (terminale) yönlendilir

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
	if (huart == NULL)
	{
		return;
	}
	else if (huart == &huart1)
	{
	}
	else if (huart == &huart2)
	{
	}
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if (huart == NULL)
	{
		return;
	}
	else if (huart == &huart1)
	{
		// terminalden gelmis
		//FRK_AddToTermBuf(terminalRx);
		HAL_NVIC_DisableIRQ(USART1_IRQn);
		HAL_UART_Transmit(&huart2, &terminalRx, 1, 1);
		HAL_NVIC_EnableIRQ(USART1_IRQn);
		HAL_UART_Receive(&huart1, &terminalRx, 1, 1);
	}
	else if (huart == &huart2)
	{
		// diger karttan gelmis
		//FRK_AddToPairBuf(pairRx);
		HAL_NVIC_DisableIRQ(USART2_IRQn);
		HAL_UART_Transmit(&huart1, &pairRx, 1, 1);
		HAL_NVIC_EnableIRQ(USART2_IRQn);
		HAL_UART_Receive(&huart2, &pairRx, 1, 1);
	}
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
}

