/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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
#include "tim.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stm32f4xx_hal.h"

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
/* USER CODE BEGIN PFP */
//static void MX_GPIO_Init(void);
//static void MX_TIM2_PWM_Init(void); // PWM 타이머 초기화 함수

// 모터 제어 함수
void motor_left_set_speed(uint16_t speed);
void motor_right_set_speed(uint16_t speed);
void motor_left_forward(void);
void motor_left_reverse(void);
void motor_left_stop(void);
void motor_right_forward(void);
void motor_right_reverse(void);
void motor_right_stop(void);

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* 모터 제어 함수 구현부 ----------------------------------------------------*/

/**
  * @brief 왼쪽 모터 속도 설정 (0 ~ 999)
  * @param speed: 0 (정지) ~ 999 (최대 속도)
  * @retval None
  */
void motor_left_set_speed(uint16_t speed)
{
  if (speed > 999) speed = 999;
  __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, speed); // CCR1 레지스터에 값 쓰기
}

/**
  * @brief 오른쪽 모터 속도 설정 (0 ~ 999)
  * @param speed: 0 (정지) ~ 999 (최대 속도)
  * @retval None
  */
void motor_right_set_speed(uint16_t speed)
{
  if (speed > 999) speed = 999;
  __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, speed); // CCR2 레지스터에 값 쓰기
}

/**
  * @brief 왼쪽 모터 전진
  * @retval None
  */
void motor_left_forward(void)
{
  HAL_GPIO_WritePin(L_MOTOR_IN1_PORT, L_MOTOR_IN1_PIN, GPIO_PIN_SET);
  HAL_GPIO_WritePin(L_MOTOR_IN2_PORT, L_MOTOR_IN2_PIN, GPIO_PIN_RESET);
}

/**
  * @brief 왼쪽 모터 후진
  * @retval None
  */
void motor_left_reverse(void)
{
  HAL_GPIO_WritePin(L_MOTOR_IN1_PORT, L_MOTOR_IN1_PIN, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(L_MOTOR_IN2_PORT, L_MOTOR_IN2_PIN, GPIO_PIN_SET);
}

/**
  * @brief 왼쪽 모터 정지 (브레이크)
  * @retval None
  */
void motor_left_stop(void)
{
  // L298N의 경우 IN1, IN2를 모두 LOW 또는 모두 HIGH로 하면 브레이크.
  // 또는 PWM을 0으로 해도 정지 효과. 여기서는 두 가지 모두 적용.
  HAL_GPIO_WritePin(L_MOTOR_IN1_PORT, L_MOTOR_IN1_PIN, GPIO_PIN_RESET); // 또는 GPIO_PIN_SET
  HAL_GPIO_WritePin(L_MOTOR_IN2_PORT, L_MOTOR_IN2_PIN, GPIO_PIN_RESET); // 또는 GPIO_PIN_SET
  motor_left_set_speed(0);
}

/**
  * @brief 오른쪽 모터 전진
  * @retval None
  */
void motor_right_forward(void)
{
  HAL_GPIO_WritePin(R_MOTOR_IN3_PORT, R_MOTOR_IN3_PIN, GPIO_PIN_SET);
  HAL_GPIO_WritePin(R_MOTOR_IN4_PORT, R_MOTOR_IN4_PIN, GPIO_PIN_RESET);
}

/**
  * @brief 오른쪽 모터 후진
  * @retval None
  */
void motor_right_reverse(void)
{
  HAL_GPIO_WritePin(R_MOTOR_IN3_PORT, R_MOTOR_IN3_PIN, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(R_MOTOR_IN4_PORT, R_MOTOR_IN4_PIN, GPIO_PIN_SET);
}

/**
  * @brief 오른쪽 모터 정지 (브레이크)
  * @retval None
  */
void motor_right_stop(void)
{
  HAL_GPIO_WritePin(R_MOTOR_IN3_PORT, R_MOTOR_IN3_PIN, GPIO_PIN_RESET); // 또는 GPIO_PIN_SET
  HAL_GPIO_WritePin(R_MOTOR_IN4_PORT, R_MOTOR_IN4_PIN, GPIO_PIN_RESET); // 또는 GPIO_PIN_SET
  motor_right_set_speed(0);
}


#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  * where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
}
#endif /* USE_FULL_ASSERT */


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
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */
  HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1); // 왼쪽 모터 PWM (ENA)
  HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2); // 오른쪽 모터 PWM (ENB)

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  // 1. 전진 (속도 500 / 999)
	      motor_left_forward();
	      motor_right_forward();
	      motor_left_set_speed(500);  // 0 ~ 999 범위의 속도 값
	      motor_right_set_speed(500);
	      HAL_Delay(2000); // 2초간 전진

	      // 2. 정지
	      motor_left_stop();
	      motor_right_stop();
	      HAL_Delay(1000); // 1초간 정지

	      // 3. 후진 (속도 300 / 999)
	      motor_left_reverse();
	      motor_right_reverse();
	      motor_left_set_speed(300);
	      motor_right_set_speed(300);
	      HAL_Delay(2000); // 2초간 후진

	      // 4. 정지
	      motor_left_stop();
	      motor_right_stop();
	      HAL_Delay(1000); // 1초간 정지

	      // 5. 좌회전 (왼쪽은 후진, 오른쪽은 전진, 속도 400)
	      motor_left_reverse();
	      motor_right_forward();
	      motor_left_set_speed(400);
	      motor_right_set_speed(400);
	      HAL_Delay(1500);

	      // 6. 정지
	      motor_left_stop();
	      motor_right_stop();
	      HAL_Delay(1000);
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
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

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 100;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
  {
    Error_Handler();
  }
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
