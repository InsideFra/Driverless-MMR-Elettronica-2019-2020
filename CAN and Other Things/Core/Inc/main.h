/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

// AGGIORNARE QUESTI DEFINE SEGUENDO LA LISTA IN MAIN.C SensList SList
#define SMOTIndex 5
#define RPMedia 1

// AGGIORNARE QUESTI DEFINE SECONDO LE ESIGENZE DI MEMORIA
#define MAXDATA8bit 	700
#define MAXDATA16bit 	900
#define NSensori16bit	9
#define NSensori8bit	13
#define NValori

// DEFINE GPIO
#define HIGH 1
#define LOW 0

// DEFINE ADC MCP3208
#define SPI_CS_PIN 	LD2_Pin 		// SPI slave select
#define SPI_CS_PORT LD2_GPIO_Port 	// SPI slave select
#define ADC_VREF 	3300			// 5v Vref
#define ADC_CLK 	1600000 		// SPI clock 1.6MHz
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
typedef struct {
	uint16_t millis;
	uint8_t secondi;
	uint8_t minuti;
	uint8_t ore;
} timestamp;

// TIMESTAMP modificato per occupare meno memoria (tempo di utilizzo max 59 minuti)
typedef struct {
	uint16_t millis;
	uint8_t secondi;
	uint8_t minuti;
} timestamp1;

typedef struct {
	uint8_t IDSensore;
	uint16_t Valore;
	timestamp tmps;
} SensDataLog;

// SE SI TENGONO AGGIORNATI I DEFINE SI PUÒ RISPARMIARE UN BYTE PER OGNI CAMPIONAMENTO
typedef struct {
	uint16_t Valore;
	uint16_t tmps;
} SensDataLog16;

typedef struct {
	uint8_t Valore;
	uint16_t tmps;
} SensDataLog8;

//
typedef struct {
	uint8_t IDSensore;
	char Nome[24];
	void (*func)(uint16_t *buffer, uint8_t helper);
	uint8_t helper;
	uint16_t lastValoreChecked;
} SensList;

typedef struct {
	uint8_t IDValore;
	char Nome[24];
	int16_t Valore;
} DataList;

void sensCanReq();
void RoutineAccelerometro(uint16_t *buffer, uint8_t helper);
void RoutineRF(uint16_t *buffer, uint8_t helper);
void RoutineGiroscopio(uint16_t *buffer, uint8_t helper);
void RoutineV(uint16_t *buffer, uint8_t helper);
void RoutineAPPS(uint16_t *buffer, uint8_t helper);
void RoutineTPS(uint16_t *buffer, uint8_t helper);
void RoutineDAC(uint16_t *buffer, uint8_t helper);
void RoutineFrizione(uint16_t *buffer, uint8_t helper);
void RoutineMarcia(uint16_t *buffer, uint8_t helper);
void RoutineTempAcqua(uint16_t *buffer, uint8_t helper);
void RoutineTempOlio(uint16_t *buffer, uint8_t helper);
void RoutineTempAria(uint16_t *buffer, uint8_t helper);
void noRoutine(uint16_t *buffer, uint8_t helper);
void RoutineSMOT(uint16_t *buffer, uint8_t helper);
void aggSensMemoria();
/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define B1_Pin GPIO_PIN_13
#define B1_GPIO_Port GPIOC
#define B1_EXTI_IRQn EXTI15_10_IRQn
#define csADC1_Pin GPIO_PIN_0
#define csADC1_GPIO_Port GPIOC
#define SmotSensor_Pin GPIO_PIN_0
#define SmotSensor_GPIO_Port GPIOA
#define SmotSensor_EXTI_IRQn EXTI0_IRQn
#define USART_TX_Pin GPIO_PIN_2
#define USART_TX_GPIO_Port GPIOA
#define USART_RX_Pin GPIO_PIN_3
#define USART_RX_GPIO_Port GPIOA
#define LD2_Pin GPIO_PIN_5
#define LD2_GPIO_Port GPIOA
#define rfAS_Pin GPIO_PIN_6
#define rfAS_GPIO_Port GPIOA
#define rfAS_EXTI_IRQn EXTI9_5_IRQn
#define rfAD_Pin GPIO_PIN_7
#define rfAD_GPIO_Port GPIOA
#define rfAD_EXTI_IRQn EXTI9_5_IRQn
#define rfPD_Pin GPIO_PIN_5
#define rfPD_GPIO_Port GPIOC
#define rfPD_EXTI_IRQn EXTI9_5_IRQn
#define rfPS_Pin GPIO_PIN_9
#define rfPS_GPIO_Port GPIOC
#define rfPS_EXTI_IRQn EXTI9_5_IRQn
#define TMS_Pin GPIO_PIN_13
#define TMS_GPIO_Port GPIOA
#define TCK_Pin GPIO_PIN_14
#define TCK_GPIO_Port GPIOA
#define SWO_Pin GPIO_PIN_3
#define SWO_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
