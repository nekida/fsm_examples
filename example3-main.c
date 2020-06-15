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
#include "i2c.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdio.h"
#include "crc16.h"
#include "state_machine.h"

/* USER CODE BEGIN 0 */
STATE_t state = STATE_IDLE;
volatile EVENT_t event = EVENT_NONE;

void (*const transition_table[STATE_MAX][EVENT_MAX])(void) = {
	[STATE_IDLE]			[EVENT_RQST_STATUS] 		= state_rqst_status,
	[STATE_IDLE]			[EVENT_INFORMATION_COMMAND]	= state_information_command,
	[STATE_IDLE]			[EVENT_ECHO]			= state_echo,
	[STATE_IDLE]			[EVENT_SEND_ANSWER]		= state_send_answer,
	[STATE_IDLE]			[EVENT_NONE]			= state_idle,
	[STATE_RQST_STATUS]		[EVENT_NONE]			= state_idle,
	[STATE_INFORMATION_COMMAND]	[EVENT_NONE]			= state_check_answer,
	[STATE_CHECK_ANSWER]		[EVENT_NONE]			= state_idle,
	[STATE_ECHO]			[EVENT_NONE]			= state_idle,
	[STATE_SEND_ANSWER]		[EVENT_NONE]			= state_idle
};
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */	
  /* USER CODE END 1 */

  /* Enable I-Cache---------------------------------------------------------*/
  SCB_EnableICache();

  /* Enable D-Cache---------------------------------------------------------*/
  SCB_EnableDCache();

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
  MX_USART1_UART_Init();
  MX_SPI1_Init();
  MX_I2C1_Init();
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */
  HAL_UART_Receive_IT(&huart1, &rx_byte, 1);	
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	transition_table[state][event]();
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}
