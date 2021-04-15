/**
  ******************************************************************************
  * File Name          : USART.c
  * Description        : This file provides code for the configuration
  *                      of the USART instances.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "usart.h"

/* USER CODE BEGIN 0 */
extern uint16_t d;
//extern SensDataLog inMemory[3000]; variabile deprecata
uint16_t lastSensDump = 0;
uint16_t i = 0;
uint8_t dataFormat[25] = "[00:00:00:000] 000 0000;";
uint8_t bufferRxUART[8] = {0};
/* USER CODE END 0 */

UART_HandleTypeDef huart2;

/* USART2 init function */

void MX_USART2_UART_Init(void)
{

  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }

}

void HAL_UART_MspInit(UART_HandleTypeDef* uartHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(uartHandle->Instance==USART2)
  {
  /* USER CODE BEGIN USART2_MspInit 0 */

  /* USER CODE END USART2_MspInit 0 */
    /* USART2 clock enable */
    __HAL_RCC_USART2_CLK_ENABLE();
  
    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**USART2 GPIO Configuration    
    PA2     ------> USART2_TX
    PA3     ------> USART2_RX 
    */
    GPIO_InitStruct.Pin = USART_TX_Pin|USART_RX_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* USART2 interrupt Init */
    HAL_NVIC_SetPriority(USART2_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(USART2_IRQn);
  /* USER CODE BEGIN USART2_MspInit 1 */

  /* USER CODE END USART2_MspInit 1 */
  }
}

void HAL_UART_MspDeInit(UART_HandleTypeDef* uartHandle)
{

  if(uartHandle->Instance==USART2)
  {
  /* USER CODE BEGIN USART2_MspDeInit 0 */

  /* USER CODE END USART2_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART2_CLK_DISABLE();
  
    /**USART2 GPIO Configuration    
    PA2     ------> USART2_TX
    PA3     ------> USART2_RX 
    */
    HAL_GPIO_DeInit(GPIOA, USART_TX_Pin|USART_RX_Pin);

    /* USART2 interrupt Deinit */
    HAL_NVIC_DisableIRQ(USART2_IRQn);
  /* USER CODE BEGIN USART2_MspDeInit 1 */

  /* USER CODE END USART2_MspDeInit 1 */
  }
} 

/* USER CODE BEGIN 1 */
void dumpMemoriaUART() {
	/*i = 0;
	adjustTimestamp(dataFormat, inMemory[i].tmps);
	adjustID(dataFormat, inMemory[i].IDSensore);
	adjustValue(dataFormat, inMemory[i].Valore);

	HAL_UART_Transmit_IT(&huart2, dataFormat, 25);*/
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart2) {
	/*lastSensDump++;
	if(lastSensDump < d) {
		i = lastSensDump;
		adjustTimestamp(dataFormat, inMemory[i].tmps);
		adjustID(dataFormat, inMemory[i].IDSensore);
		adjustValue(dataFormat, inMemory[i].Valore);
		HAL_UART_Transmit_IT(huart2, dataFormat, 25);

	} else {
		d = 0;
		lastSensDump = 0;
	}*/
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart2) {
	switch(bufferRxUART[0]) {
	case 1:
		break;
	case 2:
		break;
	case 3:
		break;
	default:
		break;
	}
}

void adjustTimestamp(uint8_t *buffer, timestamp tmp) {
	uint16_t millis = tmp.millis;
	//uint8_t sec = tmp.secondi;
	//uint8_t min = tmp.minuti;
	//uint8_t ore  = tmp.ore;

	if (millis < 10)
	{
		buffer[10] = '0';
		buffer[11] = '0';
		buffer[12] = '0' + millis%10;
	}
	else if (millis < 100)
	{
		buffer[10] = '0';
		buffer[11] = '0' + millis/10;
		buffer[12] = '0' + millis - millis/10 * 10;
	}
	else
	{
		buffer[10] = '0' + millis/100;
		buffer[11] = '0' + (millis - millis/100 * 100)/10;
		buffer[12] = '0' + millis - (millis/10) * 10;
	}
}

void adjustID(uint8_t *buffer, uint8_t ID) {
	if(ID < 10) {
		buffer[15] = '0';
		buffer[16] = '0';
		buffer[17] = '0' + ID%10;
	} else if(ID < 100) {
		buffer[15] = '0';
		buffer[16] = '0' + ID/10;
		buffer[17] = '0' + ID - ID/10 * 10;
	} else if(ID < 1000) {
		buffer[15] = '0' + ID/100;
		buffer[16] = '0' + (ID - ID/100 * 100)/10;
		buffer[17] = '0' + ID - (ID/10) * 10;
	}
}

void adjustValue(uint8_t *buffer, uint16_t Value) {
	if (Value < 10) {
		buffer[19] = '0';
		buffer[20] = '0';
		buffer[21] = '0';
		buffer[22] = '0' + Value%10;
	} else if(Value < 100) {
		buffer[19] = '0';
		buffer[20] = '0';
		buffer[21] = '0' + Value/10;
		buffer[22] = '0' + Value - Value/10 * 10;
	} else if(Value < 1000) {
		buffer[19] = '0';
		buffer[20] = '0' + Value/100;
		buffer[21] = '0' + (Value - Value/100 * 100)/10;
		buffer[22] = '0' + Value - (Value/10) * 10;
	} else if(Value < 10000) {
		buffer[19] = '0' + Value/1000;
		buffer[20] = '0' + Value - (Value/1000 * 1000)/100;
		buffer[21] = '0' + Value - (Value/100 * 100)/10;
		buffer[22] = '0' + Value - (Value/10 * 10);
	}
}
/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
