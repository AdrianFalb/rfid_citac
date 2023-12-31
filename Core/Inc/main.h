/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
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
#include "stm32f3xx_hal.h"

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
#define PRICHOD_Pin GPIO_PIN_1
#define PRICHOD_GPIO_Port GPIOA
#define PRICHOD_EXTI_IRQn EXTI1_IRQn
#define ODCHOD_Pin GPIO_PIN_4
#define ODCHOD_GPIO_Port GPIOA
#define ODCHOD_EXTI_IRQn EXTI4_IRQn
#define SD_CS_Pin GPIO_PIN_8
#define SD_CS_GPIO_Port GPIOA
#define MFRC522_CS_Pin GPIO_PIN_9
#define MFRC522_CS_GPIO_Port GPIOA
#define DISPLAY_CS_PIN_Pin GPIO_PIN_10
#define DISPLAY_CS_PIN_GPIO_Port GPIOA
#define DISPLAY_CD_PIN_Pin GPIO_PIN_11
#define DISPLAY_CD_PIN_GPIO_Port GPIOA
#define DISPLAY_RESET_PIN_Pin GPIO_PIN_12
#define DISPLAY_RESET_PIN_GPIO_Port GPIOA

/* USER CODE BEGIN Private defines */
#define SD_SPI_HANDLE hspi1
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
