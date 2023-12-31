/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    spi.c
  * @brief   This file provides code for the configuration
  *          of the SPI instances.
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
/* Includes ------------------------------------------------------------------*/
#include "spi.h"

/* USER CODE BEGIN 0 */
SPI_HandleTypeDef hspi1;
/* USER CODE END 0 */

SPI_HandleTypeDef hspi1;

/* SPI1 init function */
void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 7;
  hspi1.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
  hspi1.Init.NSSPMode = SPI_NSS_PULSE_DISABLE;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

void HAL_SPI_MspInit(SPI_HandleTypeDef* spiHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(spiHandle->Instance==SPI1)
  {
  /* USER CODE BEGIN SPI1_MspInit 0 */

  /* USER CODE END SPI1_MspInit 0 */
    /* SPI1 clock enable */
    __HAL_RCC_SPI1_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**SPI1 GPIO Configuration
    PA5     ------> SPI1_SCK
    PA6     ------> SPI1_MISO
    PA7     ------> SPI1_MOSI
    */
    GPIO_InitStruct.Pin = GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF5_SPI1;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* USER CODE BEGIN SPI1_MspInit 1 */

  /* USER CODE END SPI1_MspInit 1 */
  }
}

void HAL_SPI_MspDeInit(SPI_HandleTypeDef* spiHandle)
{

  if(spiHandle->Instance==SPI1)
  {
  /* USER CODE BEGIN SPI1_MspDeInit 0 */

  /* USER CODE END SPI1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_SPI1_CLK_DISABLE();

    /**SPI1 GPIO Configuration
    PA5     ------> SPI1_SCK
    PA6     ------> SPI1_MISO
    PA7     ------> SPI1_MOSI
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7);

  /* USER CODE BEGIN SPI1_MspDeInit 1 */

  /* USER CODE END SPI1_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */
/**
 * @brief Function is used to transmit data through SPI bus.\n
 * @detials Function uses the predefined HAL_SPI_Transmit() function to transmit data.
 * @param[in] hspi -> pointer to SPI handle structure
 * @param[in] data -> pointer to data buffer, which is transmitted.
 * @param[in] size -> size of the data to be transmitted.
 */
void SPI_TransmitData(SPI_HandleTypeDef* hspi, uint8_t* data, uint16_t size)
{
	HAL_SPI_Transmit(hspi, data, size, 1000);
}

/**
 * @brief Function is used to receive data through SPI bus.\n
 * @detials Function uses the predefined HAL_SPI_TransmitReceive() function to transmit data dummy data and recieve data back.
 * @param[in] hspi -> pointer to SPI handle structure
 * @param[in] dataTx -> pointer to dummy data buffer, which is transmitted before reading data (needed because of the SPI specification)
 * @param[in] dataRx -> pointer to a buffer used to store read data
 * @param[in] size -> size of the data to be read.
 */
void SPI_RecieveData(SPI_HandleTypeDef* hspi, uint8_t* dataTx, uint8_t* dataRx, uint16_t size)
{
	HAL_SPI_TransmitReceive(hspi, dataTx, dataRx, size, 1000);
}

/**
 * @brief Function used to deselect a slave device connected to the SPI bus.\n
 * @detials Function is used to set the specified peripherals CS pin HIGH to select it and start communication.
 * @param[in] gpio_port -> pointer to the GPIO peripherals port
 * @param[in] gpioPin -> PIN number (from 0 to 15)
 */
void CS_DESELECT(GPIO_TypeDef * gpio_port, uint16_t gpioPin)
{
	HAL_GPIO_WritePin(gpio_port, gpioPin, GPIO_PIN_SET);
	HAL_Delay(2);
}

/**
 * @brief Function used to select a slave device connected to the SPI bus.\n
 * @detials Function is used to set the specified peripherals CS pin LOW to select it and start communication.
 * @param[in] gpio_port -> pointer to the GPIO peripherals port
 * @param[in] gpioPin -> PIN number (from 0 to 15)
 */
void CS_SELECT(GPIO_TypeDef * gpio_port, uint16_t gpioPin)
{
	HAL_GPIO_WritePin(gpio_port, gpioPin, GPIO_PIN_RESET);
	HAL_Delay(2);
}

/* USER CODE END 1 */
