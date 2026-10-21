/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2026 STMicroelectronics.
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
#include "stm32f1xx_hal.h"

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
#define NORTH_RED_Pin GPIO_PIN_5
#define NORTH_RED_GPIO_Port GPIOA
#define NORTH_YELLOW_Pin GPIO_PIN_6
#define NORTH_YELLOW_GPIO_Port GPIOA
#define NORTH_GREEN_Pin GPIO_PIN_7
#define NORTH_GREEN_GPIO_Port GPIOA
#define EAST_RED_Pin GPIO_PIN_0
#define EAST_RED_GPIO_Port GPIOB
#define EAST_YELLOW_Pin GPIO_PIN_1
#define EAST_YELLOW_GPIO_Port GPIOB
#define EAST_GREEN_Pin GPIO_PIN_2
#define EAST_GREEN_GPIO_Port GPIOB
#define SOUTH_RED_Pin GPIO_PIN_8
#define SOUTH_RED_GPIO_Port GPIOA
#define SOUTH_YELLOW_Pin GPIO_PIN_9
#define SOUTH_YELLOW_GPIO_Port GPIOA
#define SOUTH_GREEN_Pin GPIO_PIN_10
#define SOUTH_GREEN_GPIO_Port GPIOA
#define WEST_RED_Pin GPIO_PIN_5
#define WEST_RED_GPIO_Port GPIOB
#define WEST_YELLOW_Pin GPIO_PIN_6
#define WEST_YELLOW_GPIO_Port GPIOB
#define WEST_GREEN_Pin GPIO_PIN_7
#define WEST_GREEN_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
