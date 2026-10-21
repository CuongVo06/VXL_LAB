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
// Hàm hiển thị số từ 0 đến 9 lên LED 7 đoạn (Anode chung)
void display7SEG(int num) {
    // Mảng mã hóa LED 7 đoạn cho các số từ 0 đến 9 (mức 0 là sáng, mức 1 là tắt cho các đoạn a, b, c, d, e, f, g)
    // Thứ tự chân tương ứng từ PB0 đến PB6 cho các đoạn: a, b, c, d, e, f, g
    const uint8_t seg_table[10][7] = {
        {0, 0, 0, 0, 0, 0, 1}, // Số 0: sáng a, b, c, d, e, f (g tắt)
        {1, 0, 0, 1, 1, 1, 1}, // Số 1: sáng b, c
        {0, 0, 1, 0, 0, 1, 0}, // Số 2: sáng a, b, d, e, g
        {0, 0, 0, 0, 1, 1, 0}, // Số 3: sáng a, b, c, d, g
        {1, 0, 0, 1, 1, 0, 0}, // Số 4: sáng b, c, f, g
        {0, 1, 0, 0, 1, 0, 0}, // Số 5: sáng a, c, d, f, g
        {0, 1, 0, 0, 0, 0, 0}, // Số 6: sáng a, c, d, e, f, g
        {0, 0, 0, 1, 1, 1, 1}, // Số 7: sáng a, b, c
        {0, 0, 0, 0, 0, 0, 0}, // Số 8: sáng tất cả
        {0, 0, 0, 0, 1, 0, 0}  // Số 9: sáng a, b, c, d, f, g
    };

    if (num < 0 || num > 9) return;

    // Xuất tín hiệu ra các chân PB0 đến PB6
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, seg_table[num][0] ? GPIO_PIN_SET : GPIO_PIN_RESET); // đoạn a
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, seg_table[num][1] ? GPIO_PIN_SET : GPIO_PIN_RESET); // đoạn b
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, seg_table[num][2] ? GPIO_PIN_SET : GPIO_PIN_RESET); // đoạn c
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, seg_table[num][3] ? GPIO_PIN_SET : GPIO_PIN_RESET); // đoạn d
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, seg_table[num][4] ? GPIO_PIN_SET : GPIO_PIN_RESET); // đoạn e
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, seg_table[num][5] ? GPIO_PIN_SET : GPIO_PIN_RESET); // đoạn f
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, seg_table[num][6] ? GPIO_PIN_SET : GPIO_PIN_RESET); // đoạn g
}
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
  int counter = 0; // Biến đếm ngược thời gian cho đèn giao thông

  while (1) {
      // Gọi hàm hiển thị giá trị đếm ngược lên LED 7 đoạn
      display7SEG(counter);

      // Xử lý logic chuyển trạng thái đèn giao thông 4 hướng
      // kết hợp giảm giá trị biến đếm ngược qua mỗi chu kỳ trễ 1 giây
      HAL_Delay(1000);

      counter--;
      if (counter < 0) {
          counter = 9; // Hoặc gán lại giá trị thời gian đếm ngược tùy theo chu kỳ đèn
      }
  }
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
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
                          |GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6, GPIO_PIN_RESET);

  /*Configure GPIO pins : PB0 PB1 PB2 PB3
                           PB4 PB5 PB6 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
                          |GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6;
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
