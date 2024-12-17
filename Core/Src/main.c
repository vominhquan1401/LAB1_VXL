/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
int hour_num = 3;
int minute_num = 59;
int second_num = 50;

int *hour = &hour_num;
int *minute = &minute_num;
int *second = &second_num;

void exercise1() {
	HAL_GPIO_TogglePin(GPIOA, LED_RED_Pin);
	HAL_Delay(2000);
	HAL_GPIO_TogglePin(GPIOA, LED_YELLOW_Pin);
}
void exercise2() {
	static uint8_t count = 0;
	if (count <= 5) {
		HAL_GPIO_WritePin(GPIOA, LED_RED_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, LED_YELLOW_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, LED_GREEN_Pin, GPIO_PIN_RESET);
	} else if (count <= 7) {
		HAL_GPIO_WritePin(GPIOA, LED_RED_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, LED_YELLOW_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, LED_GREEN_Pin, GPIO_PIN_RESET);
	} else if (count <= 10) {
		HAL_GPIO_WritePin(GPIOA, LED_RED_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, LED_YELLOW_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, LED_GREEN_Pin, GPIO_PIN_SET);
	} else {
		count = 0;
	}
	count++;
	HAL_Delay(1000);
}

void set_light(GPIO_TypeDef *GPIOx, uint16_t red, uint16_t yellow,
		uint16_t green, uint8_t state) {
	if (state == 0) {
		HAL_GPIO_WritePin(GPIOx, red, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOx, yellow | green,
				GPIO_PIN_RESET);
	} else if (state == 1) {
		HAL_GPIO_WritePin(GPIOx, yellow, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOx, red | green, GPIO_PIN_RESET);
	} else if (state == 2) {
		HAL_GPIO_WritePin(GPIOx, green, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOx, red | yellow, GPIO_PIN_RESET);
	}
}
void led_off() {
	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOA,
			LED_RED_Pin | LED_YELLOW_Pin | LED_GREEN_Pin | SEG_1_Pin | SEG_2_Pin
					| SEG_3_Pin | SEG_4_Pin | SEG_5_Pin | SEG_6_Pin,
			GPIO_PIN_SET);

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOB,
			LED_1_Pin | LED_2_Pin | LED_3_Pin | LED_11_Pin | LED_12_Pin
					| LED_4_Pin | LED_5_Pin | LED_6_Pin | LED_7_Pin | LED_8_Pin
					| LED_9_Pin | LED_10_Pin, GPIO_PIN_RESET);
}
void exercise3() {
	static uint8_t count = 0;
	static uint8_t state = 0;
	static uint8_t direction = 0;

	led_off();

	if (direction == 0) {
		set_light(GPIOC, LED_11_Pin, LED_12_Pin,
		LED_1_Pin, state);
	} else if (direction == 1) {
		set_light(GPIOC, LED_2_Pin, LED_3_Pin,
		LED_4_Pin, state);
	} else if (direction == 2) {
		set_light(GPIOC, LED_5_Pin, LED_6_Pin,
		LED_7_Pin, state);
	} else if (direction == 3) {
		set_light(GPIOC, LED_8_Pin, LED_9_Pin,
		LED_10_Pin, state);
	}

	if (count < 5) {
		state = 0;
	} else if (count < 7) {
		state = 1;
	} else if (count < 10) {
		state = 2;
	} else {
		count = 0;
		direction = (direction + 1) % 4;
	}
	count++;
}

void display7SEG(uint8_t num) {
	HAL_GPIO_WritePin(GPIOA, SEG_0_Pin |
	SEG_1_Pin | SEG_2_Pin | SEG_3_Pin | SEG_4_Pin | SEG_5_Pin | SEG_6_Pin,
			GPIO_PIN_SET);
	switch (num) {
	case 0:
		HAL_GPIO_WritePin(GPIOA,
				SEG_0_Pin | SEG_1_Pin | SEG_2_Pin | SEG_3_Pin | SEG_4_Pin
						| SEG_5_Pin,
				GPIO_PIN_RESET);
		break;
	case 1:
		HAL_GPIO_WritePin(GPIOA, SEG_1_Pin | SEG_2_Pin, GPIO_PIN_RESET);
		break;
	case 2:
		HAL_GPIO_WritePin(GPIOA,
				SEG_0_Pin | SEG_1_Pin | SEG_3_Pin | SEG_4_Pin | SEG_6_Pin,
				GPIO_PIN_RESET);
		break;
	case 3:
		HAL_GPIO_WritePin(GPIOA,
		SEG_0_Pin | SEG_1_Pin | SEG_2_Pin | SEG_3_Pin | SEG_6_Pin,
				GPIO_PIN_RESET);
		break;
	case 4:
		HAL_GPIO_WritePin(GPIOA,
		SEG_1_Pin | SEG_2_Pin | SEG_5_Pin | SEG_6_Pin, GPIO_PIN_RESET);
		break;
	case 5:
		HAL_GPIO_WritePin(GPIOA,
				SEG_0_Pin | SEG_2_Pin | SEG_3_Pin | SEG_5_Pin | SEG_6_Pin,
				GPIO_PIN_RESET);
		break;
	case 6:
		HAL_GPIO_WritePin(GPIOA,
		SEG_0_Pin | SEG_2_Pin | SEG_3_Pin | SEG_4_Pin | SEG_5_Pin
						| SEG_6_Pin,
				GPIO_PIN_RESET);
		break;
	case 7:
		HAL_GPIO_WritePin(GPIOA, SEG_0_Pin | SEG_1_Pin | SEG_2_Pin,
				GPIO_PIN_RESET);
		break;
	case 8:
		HAL_GPIO_WritePin(GPIOA,
				SEG_0_Pin | SEG_1_Pin | SEG_2_Pin | SEG_3_Pin | SEG_4_Pin
						| SEG_5_Pin | SEG_6_Pin, GPIO_PIN_RESET);
		break;
	case 9:
		HAL_GPIO_WritePin(GPIOA,
				SEG_0_Pin | SEG_1_Pin | SEG_2_Pin | SEG_3_Pin | SEG_5_Pin
						| SEG_6_Pin,
				GPIO_PIN_RESET);
		break;
	default:
		//HAL_GPIO_WritePin(SEG_PORT, SEG_A_Pin | SEG_B_Pin | SEG_C_Pin | SEG_D_Pin |SEG_E_Pin | SEG_F_Pin | SEG_G_Pin, GPIO_PIN_RESET);
		break;
	}
}
void exercise5() {
	static uint8_t count = 0;
	static uint8_t state1 = 0;
	static uint8_t state2 = 0;

	if (count < 5) { //  do 1 //xanh 2
		state1 = 0;
		state2 = 2;
	} else if (count < 7) { //vang 1 //xanh 2
		state1 = 1;
		state2 = 2;
	} else if (count < 12) { // xanh 1 // do 2
		state1 = 2;
		state2 = 0;
	} else if (count < 14) { // xanh 1 // vang 2
		state1 = 2;
		state2 = 1;
	} else {
		count = 0;
	}

	set_light(GPIOB, LED_11_Pin, LED_12_Pin, LED_1_Pin, state1);
	set_light(GPIOB, LED_5_Pin, LED_6_Pin, LED_7_Pin, state1);

	set_light(GPIOB, LED_2_Pin, LED_3_Pin, LED_4_Pin, state2);
	set_light(GPIOB, LED_8_Pin, LED_9_Pin, LED_10_Pin, state2);

	display7SEG(5 - count % 5);
	count++;
}

void exercise6() {
	HAL_GPIO_WritePin(GPIOC,
			LED_1_Pin | LED_2_Pin | LED_3_Pin | LED_4_Pin | LED_5_Pin
					| LED_6_Pin | LED_7_Pin | LED_8_Pin | LED_9_Pin | LED_10_Pin
					| LED_11_Pin | LED_12_Pin, GPIO_PIN_RESET);
}
void clearAllClock() {
	HAL_GPIO_WritePin(GPIOC,
			LED_1_Pin | LED_2_Pin | LED_3_Pin | LED_4_Pin | LED_5_Pin
					| LED_6_Pin | LED_7_Pin | LED_8_Pin | LED_9_Pin | LED_10_Pin
					| LED_11_Pin | LED_12_Pin, GPIO_PIN_SET);
}
void setNumberOnClock(int num) {
	switch (num) {
	case 0:
		HAL_GPIO_WritePin(GPIOB, LED_12_Pin, GPIO_PIN_SET);
		break;
	case 1:
		HAL_GPIO_WritePin(GPIOB, LED_1_Pin, GPIO_PIN_SET);
		break;
	case 2:
		HAL_GPIO_WritePin(GPIOB, LED_2_Pin, GPIO_PIN_SET);
		break;
	case 3:
		HAL_GPIO_WritePin(GPIOB, LED_3_Pin, GPIO_PIN_SET);
		break;
	case 4:
		HAL_GPIO_WritePin(GPIOB, LED_4_Pin, GPIO_PIN_SET);
		break;
	case 5:
		HAL_GPIO_WritePin(GPIOB, LED_5_Pin, GPIO_PIN_SET);
		break;
	case 6:
		HAL_GPIO_WritePin(GPIOB, LED_6_Pin, GPIO_PIN_SET);
		break;
	case 7:
		HAL_GPIO_WritePin(GPIOB, LED_7_Pin, GPIO_PIN_SET);
		break;
	case 8:
		HAL_GPIO_WritePin(GPIOB, LED_8_Pin, GPIO_PIN_SET);
		break;
	case 9:
		HAL_GPIO_WritePin(GPIOB, LED_9_Pin, GPIO_PIN_SET);
		break;
	case 10:
		HAL_GPIO_WritePin(GPIOB, LED_10_Pin, GPIO_PIN_SET);
		break;
	case 11:
		HAL_GPIO_WritePin(GPIOB, LED_11_Pin, GPIO_PIN_SET);
		break;
	default:
		break;
	}
}
void exercis9(int num) {
	switch (num) {
	case 0:
		HAL_GPIO_WritePin(GPIOB, LED_12_Pin, GPIO_PIN_RESET);
		break;
	case 1:
		HAL_GPIO_WritePin(GPIOB, LED_1_Pin, GPIO_PIN_RESET);
		break;
	case 2:
		HAL_GPIO_WritePin(GPIOB, LED_2_Pin, GPIO_PIN_RESET);
		break;
	case 3:
		HAL_GPIO_WritePin(GPIOB, LED_3_Pin, GPIO_PIN_RESET);
		break;
	case 4:
		HAL_GPIO_WritePin(GPIOB, LED_4_Pin, GPIO_PIN_RESET);
		break;
	case 5:
		HAL_GPIO_WritePin(GPIOB, LED_5_Pin, GPIO_PIN_RESET);
		break;
	case 6:
		HAL_GPIO_WritePin(GPIOB, LED_6_Pin, GPIO_PIN_RESET);
		break;
	case 7:
		HAL_GPIO_WritePin(GPIOB, LED_7_Pin, GPIO_PIN_RESET);
		break;
	case 8:
		HAL_GPIO_WritePin(GPIOB, LED_8_Pin, GPIO_PIN_RESET);
		break;
	case 9:
		HAL_GPIO_WritePin(GPIOB, LED_9_Pin, GPIO_PIN_RESET);
		break;
	case 10:
		HAL_GPIO_WritePin(GPIOB, LED_10_Pin, GPIO_PIN_RESET);
		break;
	case 11:
		HAL_GPIO_WritePin(GPIOB, LED_11_Pin, GPIO_PIN_RESET);
		break;
	default:
		break;
	}
}
void exercis10(int *hour, int *minute, int *second) {
	if (*second >= 60) {
		exercis9((*second - 5) / 5);
		(*second) = 0;
		(*minute)++;
	}
	setNumberOnClock((*second) / 5);
	if (*second / 5 != (*minute) / 5 + 1 && (*second) / 5 != (*hour) + 1) {
		exercis9(((*second) - 5) / 5);
	}


	if ((*minute) >= 60) {
		exercis9(((*minute) - 5) / 5);
		(*minute) = 0;
		(*hour)++;
	}
	setNumberOnClock((*minute) / 5);
	if (*minute / 5 != (*second) / 5 + 1 && (*second) / 5 != (*hour) + 1) {
		exercis9(((*minute) - 5) / 5);
	}


	if (*hour >= 12) {
		exercis9((*hour) - 1);
		(*hour) = 0;
		(*minute) = 0;
		*second = 0;
	}
	setNumberOnClock(*hour);
	if ((*hour) != (*minute) / 5 + 1 && (*hour) != (*second) / 5 + 1) {
		exercis9((*hour) - 1);
	}
	(*second)++;
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
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */
	clearAllClock();
	//led_off();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
		//exercise5();
		exercis10(hour, minute, second);
		HAL_Delay(100);
  }
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
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI_DIV2;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL16;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV8;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, LED_RED_Pin|LED_YELLOW_Pin|LED_GREEN_Pin|SEG_1_Pin
                          |SEG_2_Pin|SEG_3_Pin|SEG_4_Pin|SEG_5_Pin
                          |SEG_6_Pin|SEG_0_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, LED_1_Pin|LED_2_Pin|LED_3_Pin|LED_11_Pin
                          |LED_12_Pin|LED_4_Pin|LED_5_Pin|LED_6_Pin
                          |LED_7_Pin|LED_8_Pin|LED_9_Pin|LED_10_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : LED_RED_Pin LED_YELLOW_Pin LED_GREEN_Pin SEG_1_Pin
                           SEG_2_Pin SEG_3_Pin SEG_4_Pin SEG_5_Pin
                           SEG_6_Pin SEG_0_Pin */
  GPIO_InitStruct.Pin = LED_RED_Pin|LED_YELLOW_Pin|LED_GREEN_Pin|SEG_1_Pin
                          |SEG_2_Pin|SEG_3_Pin|SEG_4_Pin|SEG_5_Pin
                          |SEG_6_Pin|SEG_0_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : LED_1_Pin LED_2_Pin LED_3_Pin LED_11_Pin
                           LED_12_Pin LED_4_Pin LED_5_Pin LED_6_Pin
                           LED_7_Pin LED_8_Pin LED_9_Pin LED_10_Pin */
  GPIO_InitStruct.Pin = LED_1_Pin|LED_2_Pin|LED_3_Pin|LED_11_Pin
                          |LED_12_Pin|LED_4_Pin|LED_5_Pin|LED_6_Pin
                          |LED_7_Pin|LED_8_Pin|LED_9_Pin|LED_10_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
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
