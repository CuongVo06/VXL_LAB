/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Ex9 - Hiển thị chữ "A" chuẩn trên Ma trận LED 8x8
  ******************************************************************************
  */
/* USER CODE END Header */
#include "main.h"

/* USER CODE BEGIN PV */
TIM_HandleTypeDef htim2; // Giữ để tránh lỗi Linker

// --- SOFTWARE TIMER TEMPLATE ---
#define MAX_TIMERS 1
int timer_counter[MAX_TIMERS] = {0};
int timer_flag[MAX_TIMERS] = {0};

// --- MA TRẬN LED 8x8 ---
const int MAX_LED_MATRIX = 8;
int index_led_matrix = 0;

// Mảng 8 byte mã hóa chữ "A" chuẩn cho 8 Cột (PB8..PB15: Mức 0 = SÁNG, Mức 1 = TẮT)
uint8_t matrix_A[8] = {
    0x03, // Cột 0: Sáng Hàng 2, 3, 4, 5, 6, 7 (Bổ sung ô dưới cùng)
    0xF5, // Cột 1: Sáng Hàng 1, 3
    0xF6, // Cột 2: Sáng Hàng 0 (Đỉnh) và Hàng 3 (Thanh ngang)
    0xF6, // Cột 3: Sáng Hàng 0 (Đỉnh) và Hàng 3 (Thanh ngang)
    0xF6, // Cột 4: Sáng Hàng 0 (Đỉnh) và Hàng 3 (Thanh ngang)
    0xF6, // Cột 5: Sáng Hàng 0 (Đỉnh) và Hàng 3 (Thanh ngang)
    0xF5, // Cột 6: Sáng Hàng 1, 3
    0x03  // Cột 7: Sáng Hàng 2, 3, 4, 5, 6, 7 (Bổ sung ô dưới cùng)
};
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM2_Init(void);

void setTimer(int index, int duration);
void timerRun(void);
void updateLEDMatrix(int index);

/* USER CODE BEGIN 0 */
void setTimer(int index, int duration) {
    if (index >= 0 && index < MAX_TIMERS) {
        timer_counter[index] = duration;
        timer_flag[index] = 0;
    }
}

void timerRun(void) {
    for (int i = 0; i < MAX_TIMERS; i++) {
        if (timer_counter[i] > 0) {
            timer_counter[i]--;
            if (timer_counter[i] <= 0) {
                timer_flag[i] = 1;
            }
        }
    }
}

// Hàm quét từng Cột Ma trận LED
void updateLEDMatrix(int index) {
    // 1. TẮT TẤT CẢ CÁC CỘT (PA2, PA3, PA10..PA15 = 1 / SET)
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_10 | GPIO_PIN_11 |
                             GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15, GPIO_PIN_SET);

    // 2. Xuất dữ liệu Hàng ra PB8..PB15 (Bit 0 = SÁNG, Bit 1 = TẮT)
    uint8_t data = matrix_A[index];
    for (int i = 0; i < 8; i++) {
        if ((data >> i) & 0x01) {
            HAL_GPIO_WritePin(GPIOB, (GPIO_PIN_8 << i), GPIO_PIN_SET);   // 1 = TẮT
        } else {
            HAL_GPIO_WritePin(GPIOB, (GPIO_PIN_8 << i), GPIO_PIN_RESET); // 0 = SÁNG
        }
    }

    // 3. BẬT DUY NHẤT CỘT 'index' (PAx = 0 / RESET)
    switch (index) {
        case 0: HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2,  GPIO_PIN_RESET); break; // ENM0
        case 1: HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3,  GPIO_PIN_RESET); break; // ENM1
        case 2: HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_RESET); break; // ENM2
        case 3: HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_RESET); break; // ENM3
        case 4: HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_RESET); break; // ENM4
        case 5: HAL_GPIO_WritePin(GPIOA, GPIO_PIN_13, GPIO_PIN_RESET); break; // ENM5
        case 6: HAL_GPIO_WritePin(GPIOA, GPIO_PIN_14, GPIO_PIN_RESET); break; // ENM6
        case 7: HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_RESET); break; // ENM7
        default: break;
    }
}

// Trình ngắt Hardware Timer 2 - đếm lùi Software Timer
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
    if (htim->Instance == TIM2) {
        timerRun();
    }
}
/* USER CODE END 0 */

int main(void)
{
  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
  MX_TIM2_Init();

  /* USER CODE BEGIN 2 */
  HAL_TIM_Base_Start_IT(&htim2);

  // Khởi tạo quét Cột 0 đầu tiên
  updateLEDMatrix(index_led_matrix);

  // Đặt Software Timer 0 quét mỗi 20ms
  setTimer(0, 7);
  /* USER CODE END 2 */

  /* USER CODE BEGIN WHILE */
  while (1)
  {
      if (timer_flag[0] == 1) {
          setTimer(0, 7); // Cài lại 20ms
          index_led_matrix = (index_led_matrix + 1) % MAX_LED_MATRIX;
          updateLEDMatrix(index_led_matrix);
      }
  }
  /* USER CODE END WHILE */
}

void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) { Error_Handler(); }

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK) { Error_Handler(); }
}

static void MX_TIM2_Init(void)
{
  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 7999;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 9; // Ngắt 1ms
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK) { Error_Handler(); }

  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK) { Error_Handler(); }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK) { Error_Handler(); }

  // Kích hoạt Vector ngắt TIM2
  HAL_NVIC_SetPriority(TIM2_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(TIM2_IRQn);
}

static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_AFIO_CLK_ENABLE();

  // Giải phóng chân JTAG (PA13, PA14, PA15)
  __HAL_AFIO_REMAP_SWJ_DISABLE();

  // Khởi tạo các chân Cột: PA2, PA3, PA10..PA15
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_10|GPIO_PIN_11|
                           GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15, GPIO_PIN_SET);

  GPIO_InitStruct.Pin = GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_10|GPIO_PIN_11|
                        GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  // Khởi tạo các chân Hàng: PB8..PB15
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11|
                           GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15, GPIO_PIN_SET);

  GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11|
                        GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}

void Error_Handler(void) {
  __disable_irq();
  while (1) {}
}
