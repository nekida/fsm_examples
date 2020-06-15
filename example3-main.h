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
#include "stm32f7xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

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
#define att_Pin GPIO_PIN_12
#define att_GPIO_Port GPIOH
#define cs2_Pin GPIO_PIN_11
#define cs2_GPIO_Port GPIOD
#define rx_standby_Pin GPIO_PIN_12
#define rx_standby_GPIO_Port GPIOD
#define tx_standby_Pin GPIO_PIN_13
#define tx_standby_GPIO_Port GPIOD
#define enable_t_r_Pin GPIO_PIN_6
#define enable_t_r_GPIO_Port GPIOC
#define enable_ph_Pin GPIO_PIN_7
#define enable_ph_GPIO_Port GPIOC
#define cs0_Pin GPIO_PIN_8
#define cs0_GPIO_Port GPIOC
#define cs1_Pin GPIO_PIN_9
#define cs1_GPIO_Port GPIOC
#define le_Pin GPIO_PIN_8
#define le_GPIO_Port GPIOA
/* USER CODE BEGIN Private defines */
#define ADDR										0x1E

#define CODE_FUNC_ECHO								11
#define CODE_FUNC_REQUEST_STATUS_PPM 	22
#define CODE_FUNC_INFORMATION					127

#define LEN_MSG_ECHO_RX		4
#define LEN_MSG_ECHO_TX		4
#define LEN_MSG_REQUEST_STATUS_PPM_RX	4
#define LEN_MSG_REQUEST_STATUS_PPM_TX	8
#define	LEN_MSG_INFORMATION_RX	37
#define LEN_MSG_INFORMATION_TX_OR_ERROR	5

#define FLAG_CMD_PPM						0x1
#define FLAG_RQST_PPM						0x2
#define FLAG_LEN_ERROR					0x4
#define FLAG_ECHO								0x8
#define FLAG_SPI2_REC						0x10
#define FLAG_SPI1_REC						0x20

#define ERROR_LEN								55	
#define ERROR_CRC								44	
#define ERROR_NONE							0
#define ERROR_PPM_ANSWER				66

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
