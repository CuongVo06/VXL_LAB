/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

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
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

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
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  int counter = 0; // Biến đếm chu kỳ tổng (0 -> 13, tổng 14 giây cho một vòng giao thông ngã tư)

  while (1)
  {
      // Phân pha đèn giao thông 4 hướng (Bắc-Nam đi chung pha, Đông-Tây đi chung pha):
      // - Pha 1 (0s - 4s): Bắc-Nam ĐỎ | Đông-Tây XANH
      // - Pha 2 (5s - 6s): Bắc-Nam ĐỎ | Đông-Tây VÀNG
      // - Pha 3 (7s - 11s): Bắc-Nam XANH | Đông-Tây ĐỎ
      // - Pha 4 (12s - 13s): Bắc-Nam VÀNG | Đông-Tây ĐỎ

      if (counter < 5) {
          // --- PHA 1: Bắc-Nam ĐỎ | Đông-Tây XANH ---
          // North & South: RED ON
          HAL_GPIO_WritePin(NORTH_RED_GPIO_Port, NORTH_RED_Pin, GPIO_PIN_RESET);
          HAL_GPIO_WritePin(NORTH_YELLOW_GPIO_Port, NORTH_YELLOW_Pin, GPIO_PIN_SET);
          HAL_GPIO_WritePin(NORTH_GREEN_GPIO_Port, NORTH_GREEN_Pin, GPIO_PIN_SET);

          HAL_GPIO_WritePin(SOUTH_RED_GPIO_Port, SOUTH_RED_Pin, GPIO_PIN_RESET);
          HAL_GPIO_WritePin(SOUTH_YELLOW_GPIO_Port, SOUTH_YELLOW_Pin, GPIO_PIN_SET);
          HAL_GPIO_WritePin(SOUTH_GREEN_GPIO_Port, SOUTH_GREEN_Pin, GPIO_PIN_SET);

          // East & West: GREEN ON
          HAL_GPIO_WritePin(EAST_RED_GPIO_Port, EAST_RED_Pin, GPIO_PIN_SET);
          HAL_GPIO_WritePin(EAST_YELLOW_GPIO_Port, EAST_YELLOW_Pin, GPIO_PIN_SET);
          HAL_GPIO_WritePin(EAST_GREEN_GPIO_Port, EAST_GREEN_Pin, GPIO_PIN_RESET);

          HAL_GPIO_WritePin(WEST_RED_GPIO_Port, WEST_RED_Pin, GPIO_PIN_SET);
          HAL_GPIO_WritePin(WEST_YELLOW_GPIO_Port, WEST_YELLOW_Pin, GPIO_PIN_SET);
          HAL_GPIO_WritePin(WEST_GREEN_GPIO_Port, WEST_GREEN_Pin, GPIO_PIN_RESET);
      }
      else if (counter < 7) {
          // --- PHA 2: Bắc-Nam ĐỎ | Đông-Tây VÀNG ---
          // North & South: RED ON
          HAL_GPIO_WritePin(NORTH_RED_GPIO_Port, NORTH_RED_Pin, GPIO_PIN_RESET);
          HAL_GPIO_WritePin(NORTH_YELLOW_GPIO_Port, NORTH_YELLOW_Pin, GPIO_PIN_SET);
          HAL_GPIO_WritePin(NORTH_GREEN_GPIO_Port, NORTH_GREEN_Pin, GPIO_PIN_SET);

          HAL_GPIO_WritePin(SOUTH_RED_GPIO_Port, SOUTH_RED_Pin, GPIO_PIN_RESET);
          HAL_GPIO_WritePin(SOUTH_YELLOW_GPIO_Port, SOUTH_YELLOW_Pin, GPIO_PIN_SET);
          HAL_GPIO_WritePin(SOUTH_GREEN_GPIO_Port, SOUTH_GREEN_Pin, GPIO_PIN_SET);

          // East & West: YELLOW ON
          HAL_GPIO_WritePin(EAST_RED_GPIO_Port, EAST_RED_Pin, GPIO_PIN_SET);
          HAL_GPIO_WritePin(EAST_YELLOW_GPIO_Port, EAST_YELLOW_Pin, GPIO_PIN_RESET);
          HAL_GPIO_WritePin(EAST_GREEN_GPIO_Port, EAST_GREEN_Pin, GPIO_PIN_SET);

          HAL_GPIO_WritePin(WEST_RED_GPIO_Port, WEST_RED_Pin, GPIO_PIN_SET);
          HAL_GPIO_WritePin(WEST_YELLOW_GPIO_Port, WEST_YELLOW_Pin, GPIO_PIN_RESET);
          HAL_GPIO_WritePin(WEST_GREEN_GPIO_Port, WEST_GREEN_Pin, GPIO_PIN_SET);
      }
      else if (counter < 12) {
          // --- PHA 3: Bắc-Nam XANH | Đông-Tây ĐỎ ---
          // North & South: GREEN ON
          HAL_GPIO_WritePin(NORTH_RED_GPIO_Port, NORTH_RED_Pin, GPIO_PIN_SET);
          HAL_GPIO_WritePin(NORTH_YELLOW_GPIO_Port, NORTH_YELLOW_Pin, GPIO_PIN_SET);
          HAL_GPIO_WritePin(NORTH_GREEN_GPIO_Port, NORTH_GREEN_Pin, GPIO_PIN_RESET);

          HAL_GPIO_WritePin(SOUTH_RED_GPIO_Port, SOUTH_RED_Pin, GPIO_PIN_SET);
          HAL_GPIO_WritePin(SOUTH_YELLOW_GPIO_Port, SOUTH_YELLOW_Pin, GPIO_PIN_SET);
          HAL_GPIO_WritePin(SOUTH_GREEN_GPIO_Port, SOUTH_GREEN_Pin, GPIO_PIN_RESET);

          // East & West: RED ON
          HAL_GPIO_WritePin(EAST_RED_GPIO_Port, EAST_RED_Pin, GPIO_PIN_RESET);
          HAL_GPIO_WritePin(EAST_YELLOW_GPIO_Port, EAST_YELLOW_Pin, GPIO_PIN_SET);
          HAL_GPIO_WritePin(EAST_GREEN_GPIO_Port, EAST_GREEN_Pin, GPIO_PIN_SET);

          HAL_GPIO_WritePin(WEST_RED_GPIO_Port, WEST_RED_Pin, GPIO_PIN_RESET);
          HAL_GPIO_WritePin(WEST_YELLOW_GPIO_Port, WEST_YELLOW_Pin, GPIO_PIN_SET);
          HAL_GPIO_WritePin(WEST_GREEN_GPIO_Port, WEST_GREEN_Pin, GPIO_PIN_SET);
      }
      else {
          // --- PHA 4: Bắc-Nam VÀNG | Đông-Tây ĐỎ ---
          // North & South: YELLOW ON
          HAL_GPIO_WritePin(NORTH_RED_GPIO_Port, NORTH_RED_Pin, GPIO_PIN_SET);
          HAL_GPIO_WritePin(NORTH_YELLOW_GPIO_Port, NORTH_YELLOW_Pin, GPIO_PIN_RESET);
          HAL_GPIO_WritePin(NORTH_GREEN_GPIO_Port, NORTH_GREEN_Pin, GPIO_PIN_SET);

          HAL_GPIO_WritePin(SOUTH_RED_GPIO_Port, SOUTH_RED_Pin, GPIO_PIN_SET);
          HAL_GPIO_WritePin(SOUTH_YELLOW_GPIO_Port, SOUTH_YELLOW_Pin, GPIO_PIN_RESET);
          HAL_GPIO_WritePin(SOUTH_GREEN_GPIO_Port, SOUTH_GREEN_Pin, GPIO_PIN_SET);

          // East & West: RED ON
          HAL_GPIO_WritePin(EAST_RED_GPIO_Port, EAST_RED_Pin, GPIO_PIN_RESET);
          HAL_GPIO_WritePin(EAST_YELLOW_GPIO_Port, EAST_YELLOW_Pin, GPIO_PIN_SET);
          HAL_GPIO_WritePin(EAST_GREEN_GPIO_Port, EAST_GREEN_Pin, GPIO_PIN_SET);

          HAL_GPIO_WritePin(WEST_RED_GPIO_Port, WEST_RED_Pin, GPIO_PIN_RESET);
          HAL_GPIO_WritePin(WEST_YELLOW_GPIO_Port, WEST_YELLOW_Pin, GPIO_PIN_SET);
          HAL_GPIO_WritePin(WEST_GREEN_GPIO_Port, WEST_GREEN_Pin, GPIO_PIN_SET);
      }

      // Tăng biến đếm và reset chu kỳ sau 14 nhịp (14 giây)
      counter++;
      if (counter >= 14) {
          counter = 0;
      }

      // Lệnh delay duy nhất 1 giây ở cuối vòng lặp theo đúng yêu cầu
      HAL_Delay(1000);
  }
  /* USER CODE END WHILE */
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, NORTH_RED_Pin|NORTH_YELLOW_Pin|NORTH_GREEN_Pin|SOUTH_RED_Pin
                          |SOUTH_YELLOW_Pin|SOUTH_GREEN_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, EAST_RED_Pin|EAST_YELLOW_Pin|EAST_GREEN_Pin|WEST_RED_Pin
                          |WEST_YELLOW_Pin|WEST_GREEN_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : NORTH_RED_Pin NORTH_YELLOW_Pin NORTH_GREEN_Pin SOUTH_RED_Pin
                           SOUTH_YELLOW_Pin SOUTH_GREEN_Pin */
  GPIO_InitStruct.Pin = NORTH_RED_Pin|NORTH_YELLOW_Pin|NORTH_GREEN_Pin|SOUTH_RED_Pin
                          |SOUTH_YELLOW_Pin|SOUTH_GREEN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : EAST_RED_Pin EAST_YELLOW_Pin EAST_GREEN_Pin WEST_RED_Pin
                           WEST_YELLOW_Pin WEST_GREEN_Pin */
  GPIO_InitStruct.Pin = EAST_RED_Pin|EAST_YELLOW_Pin|EAST_GREEN_Pin|WEST_RED_Pin
                          |WEST_YELLOW_Pin|WEST_GREEN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
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
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
