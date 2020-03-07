/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "can.h"
#include "dac.h"
#include "sdio.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define MAXDATA 3000
#define NSensori 21
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
extern void dumpMemoriaUART();
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
uint8_t newCanRx = 0;

CAN_TxHeaderTypeDef   TxHeader;
CAN_RxHeaderTypeDef   RxHeader;
uint8_t               TxData[8];
uint8_t               RxData[8];
uint32_t              TxMailbox;
timestamp 			  Orario = {0, 0, 0, 0};
uint16_t d = 0;
SensList SList[NSensori] = {
	//	ID,  NOME, 			Routine, 			 	h, UltimoValore;
		{0,  "Acc X", 		RoutineAccelerometro, 	0, 0}, // Analogico
		{1,  "Acc Y", 		RoutineAccelerometro, 	1, 0}, // Analogico
		{2,  "Giroscopio", 	RoutineGiroscopio, 		0, 0}, // Analogico
		{3,  "RF AS", 		RoutineRF, 				0, 0}, // Ruota Fonica, Digitale
		{4,  "RF AD", 		RoutineRF, 				1, 0}, // Ruota Fonica, Digitale
		{5,  "RF PS", 		RoutineRF, 				2, 0}, // Ruota Fonica, Digitale
		{6,  "RF PD", 		RoutineRF, 				3, 0}, // Ruota Fonica, Digitale
		{7,  "SMOT",    	RoutineSmot, 			0, 0}, // Sens. giri motore, Digitale
		{8,  "V Batt1", 	RoutineV, 				0, 0}, // Analogico, V Batteria 12v
		{9,  "V Batt2", 	RoutineV, 				1, 0}, // Analogico, V Batteria 12v
		{10, "V Batt3", 	RoutineV, 				2, 0}, // Analogico, V Batteria 12v
		{11, "APPS1",   	RoutineAPPS,			0, 0}, // Potenziometro Acceleratore
		{12, "APPS2",   	RoutineAPPS, 			1, 0}, // Potenziometro Acceleratore Backup
		{13, "TPS1",    	RoutineTPS, 			0, 0}, // Potenziometro Apertura Farfalla
		{14, "TPS2",    	RoutineTPS, 			1, 0}, // Potenziometro Apertura Farfalla Backup
		{15, "DAC", 		RoutineDAC,				0, 0}, // Acceleratore STM32
		{16, "Frizione",	RoutineFrizione, 		0, 0}, //
		{17, "TempOlio", 	RoutineTempOlio, 		0, 0}, // Sens. Temp. Olio,		Analogico
		{18, "TempAcqua", 	RoutineTempAcqua, 		0, 0}, // Sens. Temp. Acqua, 	Analogico
		{19, "TempAria",	RoutineTempAria, 		0, 0}, // Sens. Temp. Aria Asp, Analogico
		{20, "GearIns", 	RoutineMarcia, 			0, 0} // Marcia Inserita
};
uint8_t Aggiornamento = 0;
SensDataLog inMemory[4000];
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */
  

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_CAN2_Init();
  MX_DAC_Init();
  MX_SDIO_SD_Init();
  MX_SPI2_Init();
  MX_TIM2_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */
  /* USER CODE END 2 */
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/* USER CODE BEGIN 4 */
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
  HAL_CAN_DeactivateNotification(&hcan2, CAN_IT_RX_FIFO0_MSG_PENDING);

  /* Get RX message */
  if (HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &RxHeader, RxData) != HAL_OK)
    Error_Handler();

  /* Display LEDx
  if ((RxHeader.StdId == 0x321) && (RxHeader.IDE == CAN_ID_STD) && (RxHeader.DLC == 2))
  {
    LED_Display(RxData[0]);
    ubKeyNumber = RxData[0];
  } */

  /* Set the data to be transmitted
  TxData[0] = ubKeyNumber;
  TxData[1] = 0xAD;

  // Start the Transmission process
  if (HAL_CAN_AddTxMessage(&CanHandle, &TxHeader, TxData, &TxMailbox) != HAL_OK)
	// Transmission request Error
	Error_Handler();
  */
  HAL_CAN_ActivateNotification(&hcan2, CAN_IT_RX_FIFO0_MSG_PENDING);
}

void sensCanReq() {

}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim2) {
	Orario.millis++;
	if(Orario.millis >= 1000) {
		Orario.secondi++;
		Orario.millis -= 1000;
	}
	if(Orario.secondi >= 60) {
		Orario.minuti++;
		Orario.secondi -= 60;
	}
	if(Orario.minuti >= 60 ) {
		Orario.ore++;
		Orario.minuti -= 60;
	}

	if(Aggiornamento != 1) {
		Aggiornamento = 1;
		aggSensMemoria();
		Aggiornamento = 0;
	}
}

void aggSensMemoria() {
	if (d >= MAXDATA-NSensori) {
		dumpMemoriaUART();
	}
	for (uint8_t i = 0; i < NSensori; i++) {
		timestamp tsmpTemp = {Orario.millis,
		Orario.secondi, Orario.minuti, Orario.ore};
		uint16_t ValoreTemp;

		SList[i].func(&ValoreTemp, SList[i].helper);

		inMemory[d].IDSensore = i;
		inMemory[d].Valore = ValoreTemp;
		inMemory[d].tmps = tsmpTemp;

		SList[i].lastValoreChecked = ValoreTemp;
		d++;
	}
}

void RoutineAccelerometro(uint16_t *buffer, uint8_t helper) {

}
void RoutineRF(uint16_t *buffer, uint8_t helper) {

}
void RoutineGiroscopio(uint16_t *buffer, uint8_t helper) {

}
void RoutineSmot(uint16_t *buffer, uint8_t helper) {

}
void RoutineV(uint16_t *buffer, uint8_t helper) {

}
void RoutineAPPS(uint16_t *buffer, uint8_t helper) {

}
void RoutineTPS(uint16_t *buffer, uint8_t helper) {

}
void RoutineDAC(uint16_t *buffer, uint8_t helper) {

}
void RoutineFrizione(uint16_t *buffer, uint8_t helper) {

}
void RoutineMarcia(uint16_t *buffer, uint8_t helper) {

}
void RoutineTempAcqua(uint16_t *buffer, uint8_t helper) {

}
void RoutineTempOlio(uint16_t *buffer, uint8_t helper) {

}
void RoutineTempAria(uint16_t *buffer, uint8_t helper) {

}
/* USER CODE END 4 */

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);
  /** Initializes the CPU, AHB and APB busses clocks
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 66;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  RCC_OscInitStruct.PLL.PLLR = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_SDIO|RCC_PERIPHCLK_CLK48;
  PeriphClkInitStruct.Clk48ClockSelection = RCC_CLK48CLKSOURCE_PLLQ;
  PeriphClkInitStruct.SdioClockSelection = RCC_SDIOCLKSOURCE_CLK48;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
