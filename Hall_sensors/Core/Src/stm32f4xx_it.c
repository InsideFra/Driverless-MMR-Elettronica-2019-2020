/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32f4xx_it.c
  * @brief   Interrupt Service Routines.
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
#include "stm32f4xx_it.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

Hall Memory_first_hall[100]; /*anteriore sinistra*/
Hall Memory_second_hall[100]; /*anteriore destra*/
Hall Memory_third_hall[100]; /*posteriore sinistra*/
Hall Memory_forth_hall[100]; /*posteriore destra*/

uint8_t index1=0;
uint8_t index2=0;
uint8_t index3=0;
uint8_t index4=0;
uint8_t indexvect=0;

const uint8_t n_dentini = 5;
/*const uint8_t n_tot_dentini= 50;*/
const float teta=0; /*angolo in rad tra l'n-esimo dentino e l' n+5 dentino)*/
uint8_t counter_front_sx=0; /*counter per anteriore sinistra*/
uint8_t counter_front_dx=0; /*counter per anteriore destra*/
uint8_t counter_back_sx=0; /*counter per posteriore sinistra*/
uint8_t counter_back_dx=0; /*counter per posteriore destra*/

/*uint16_t RPM_front_sx=0; RPM anteriore sinistra*/
/*uint16_t RPM_front_dx=0; RPM anteriore destra*/
/*uint16_t RPM_back_sx=0; RPM posteriore sinistra*/
/*uint16_t RPM_back_dx=0;*RPM posteriore destra*/

/*const float ang_speed_converter=  9.5492965964254; costante per convertire gli RPM in rad/s*/

float ang_speed_front_sx=0; /*velocità angolare ruota anteriore sinistra*/
float ang_speed_front_dx=0; /* velocità angolare ruota anteriore destra*/
float ang_speed_back_sx=0; /* velocità angolare ruota posteriore sinistra*/
float ang_speed_back_dx=0;  /*velocità angolare ruota posteriore destra*/
/*per facilitare l'accesso creo 4  memorie diverse per i 4 sensori */

float angularspeed[500]; /* lo implemento a con il dump quando ho settato tutti e 4 gli exti*/

extern Orario TC;
/*per facilitare l'accesso creo 4  memorie diverse per i 4 sensori */
/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern TIM_HandleTypeDef htim4;
/* USER CODE BEGIN EV */

/* USER CODE END EV */

/******************************************************************************/
/*           Cortex-M4 Processor Interruption and Exception Handlers          */
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */

  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
    /* USER CODE END W1_HardFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Memory management fault.
  */
void MemManage_Handler(void)
{
  /* USER CODE BEGIN MemoryManagement_IRQn 0 */

  /* USER CODE END MemoryManagement_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_MemoryManagement_IRQn 0 */
    /* USER CODE END W1_MemoryManagement_IRQn 0 */
  }
}

/**
  * @brief This function handles Pre-fetch fault, memory access fault.
  */
void BusFault_Handler(void)
{
  /* USER CODE BEGIN BusFault_IRQn 0 */

  /* USER CODE END BusFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_BusFault_IRQn 0 */
    /* USER CODE END W1_BusFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Undefined instruction or illegal state.
  */
void UsageFault_Handler(void)
{
  /* USER CODE BEGIN UsageFault_IRQn 0 */

  /* USER CODE END UsageFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_UsageFault_IRQn 0 */
    /* USER CODE END W1_UsageFault_IRQn 0 */
  }
}

/**
  * @brief This function handles System service call via SWI instruction.
  */
void SVC_Handler(void)
{
  /* USER CODE BEGIN SVCall_IRQn 0 */

  /* USER CODE END SVCall_IRQn 0 */
  /* USER CODE BEGIN SVCall_IRQn 1 */

  /* USER CODE END SVCall_IRQn 1 */
}

/**
  * @brief This function handles Debug monitor.
  */
void DebugMon_Handler(void)
{
  /* USER CODE BEGIN DebugMonitor_IRQn 0 */

  /* USER CODE END DebugMonitor_IRQn 0 */
  /* USER CODE BEGIN DebugMonitor_IRQn 1 */

  /* USER CODE END DebugMonitor_IRQn 1 */
}

/**
  * @brief This function handles Pendable request for system service.
  */
void PendSV_Handler(void)
{
  /* USER CODE BEGIN PendSV_IRQn 0 */

  /* USER CODE END PendSV_IRQn 0 */
  /* USER CODE BEGIN PendSV_IRQn 1 */

  /* USER CODE END PendSV_IRQn 1 */
}

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */

  /* USER CODE END SysTick_IRQn 0 */
  HAL_IncTick();
  /* USER CODE BEGIN SysTick_IRQn 1 */

  /* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32F4xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f4xx.s).                    */
/******************************************************************************/

/**
  * @brief This function handles EXTI line 0 interrupt.
  */
void EXTI0_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI0_IRQn 0 */
	uint8_t read_status;
	read_status=HAL_GPIO_ReadPin(GPIOC, hall_sensor1_Pin);
		if(read_status==GPIO_PIN_SET){
			counter_front_sx++;
			Memory_first_hall[index1].tmps=TC;
			Memory_first_hall[index1].read_value=1; /*RISING*/
		}else if (read_status==GPIO_PIN_RESET){
			Memory_first_hall[index1].tmps=TC;
			Memory_first_hall[index1].read_value=0; /*FALLING*/
		}

	index1++;

	if(counter_front_sx == n_dentini){
	// RPM_front_sx=n_dentini/(n_tot_dentini*(Memory_first_hall[index1].tmps - Memory_first_hall[index1-5].tmps));  */
	ang_speed_front_sx=teta/(timeconversion(Memory_first_hall[index1].tmps)- timeconversion(Memory_first_hall[index1-10].tmps));  /* non dovrebbere essere 10 al posto di 5, dal momento che salvo anche il tempo di falling)*/
	}
	/* USER CODE END EXTI0_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);
  /* USER CODE BEGIN EXTI0_IRQn 1 */

  /* USER CODE END EXTI0_IRQn 1 */
}

void  HAL_GPIO_EXTI_Callback (uint16_t GPIO_Pin){

}


/**
  * @brief This function handles EXTI line 1 interrupt.
  */
void EXTI1_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI1_IRQn 0 */
	uint8_t read_status2;
	read_status2=HAL_GPIO_ReadPin(GPIOC, hall_sensor2_Pin);
	if(read_status2==GPIO_PIN_SET){
		counter_front_dx++;
		Memory_second_hall[index2].tmps=TC;
		Memory_second_hall[index2].read_value=1; /*RISING*/
	}else if (read_status2==GPIO_PIN_RESET){
		Memory_second_hall[index2].tmps=TC;
		Memory_second_hall[index2].read_value=0; /*FALLING*/
	}

	index2++;

	if(counter_front_dx == n_dentini){
		// RPM_front_sx=n_dentini/(n_tot_dentini*(Memory_first_hall[index1].tmps - Memory_first_hall[index1-5].tmps)); non lo guardare lui!!!!!! */
		ang_speed_front_dx=teta/(timeconversion(Memory_second_hall[index2].tmps)- timeconversion(Memory_second_hall[index2-10].tmps));  /* non dovrebbere essere 10 al posto di 5, dal momento che salvo anche il tempo di falling)*/
	}
  /* USER CODE END EXTI1_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_1);

  /* USER CODE BEGIN EXTI1_IRQn 1 */

  /* USER CODE END EXTI1_IRQn 1 */
}

/**
  * @brief This function handles EXTI line 2 interrupt.
  */
void EXTI2_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI2_IRQn 0 */
	uint8_t read_status3;
	read_status3=HAL_GPIO_ReadPin(GPIOC, hall_sensor3_Pin);
						if(read_status3==GPIO_PIN_SET){
							counter_back_sx++;
							Memory_first_hall[index3].tmps=TC;
							Memory_first_hall[index3].read_value=1; /*RISING*/
						}else if (read_status3==GPIO_PIN_RESET){
							Memory_first_hall[index3].tmps=TC;
							Memory_first_hall[index3].read_value=0; /*FALLING*/
						}

					index3++;

					if(counter_back_sx == n_dentini){


					/*RPM_front_sx=n_dentini/(n_tot_dentini*(Memory_first_hall[index1].tmps - Memory_first_hall[index1-5].tmps));  */
					 ang_speed_back_sx=teta/(timeconversion(Memory_third_hall[index3].tmps)- timeconversion(Memory_third_hall[index3-10].tmps));  /* non dovrebbere essere 10 al posto di 5, dal momento che salvo anche il tempo di falling)*/
					/*TODO: SALVARE IN MEMORIA*/
					}
  /* USER CODE END EXTI2_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_2);

  /* USER CODE BEGIN EXTI2_IRQn 1 */

  /* USER CODE END EXTI2_IRQn 1 */
}

/**
  * @brief This function handles EXTI line 4 interrupt.
  */
void EXTI4_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI4_IRQn 0 */
uint8_t read_status4;
read_status4=HAL_GPIO_ReadPin(GPIOA, hall_sensor4_Pin);
					if(read_status4==GPIO_PIN_SET){
						counter_back_dx++;
						Memory_forth_hall[index4].tmps=TC;
						Memory_forth_hall[index4].read_value=1; /*RISING*/
					}else if (read_status4==GPIO_PIN_RESET){
						Memory_forth_hall[index4].tmps=TC;
						Memory_forth_hall[index4].read_value=0; /*FALLING*/
					}

				index4++;

				if(counter_back_dx == n_dentini){


				/*RPM_front_sx=n_dentini/(n_tot_dentini*(Memory_first_hall[index1].tmps - Memory_first_hall[index1-5].tmps));  */
				 ang_speed_back_dx=teta/(timeconversion(Memory_forth_hall[index4].tmps)- timeconversion(Memory_forth_hall[index4-10].tmps));  /* non dovrebbere essere 10 al posto di 5, dal momento che salvo anche il tempo di falling)*/

				}
  /* USER CODE END EXTI4_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_4);
  /* USER CODE BEGIN EXTI4_IRQn 1 */

  /* USER CODE END EXTI4_IRQn 1 */
}

/**
  * @brief This function handles TIM4 global interrupt.
  */
void TIM4_IRQHandler(void)
{
  /* USER CODE BEGIN TIM4_IRQn 0 */

  /* USER CODE END TIM4_IRQn 0 */
  HAL_TIM_IRQHandler(&htim4);
  /* USER CODE BEGIN TIM4_IRQn 1 */

  /* USER CODE END TIM4_IRQn 1 */
}

/* USER CODE BEGIN 1 */
float timeconversion (Orario times){
	float time=0;
	time = 60*times.minuti + times.secondi + times.millis/1000;
	return time;
}
/* USER CODE END 1 */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
