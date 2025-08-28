/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    gpio.h
  * @brief   This file contains all the function prototypes for
  *          the gpio.c file
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
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __GPIO_H__
#define __GPIO_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* USER CODE BEGIN Private defines */
#define L_MOTOR_PWM_PORT        GPIOA
#define L_MOTOR_PWM_PIN         GPIO_PIN_0  // TIM2_CH1 (예시)
#define R_MOTOR_PWM_PORT        GPIOA
#define R_MOTOR_PWM_PIN         GPIO_PIN_1  // TIM2_CH2 (예시)

#define L_MOTOR_IN1_PORT        GPIOB
#define L_MOTOR_IN1_PIN         GPIO_PIN_0
#define L_MOTOR_IN2_PORT        GPIOB
#define L_MOTOR_IN2_PIN         GPIO_PIN_1

#define R_MOTOR_IN3_PORT        GPIOB
#define R_MOTOR_IN3_PIN         GPIO_PIN_2
#define R_MOTOR_IN4_PORT        GPIOB
#define R_MOTOR_IN4_PIN         GPIO_PIN_3



/* USER CODE END Private defines */

void MX_GPIO_Init(void);

/* USER CODE BEGIN Prototypes */

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__ GPIO_H__ */

