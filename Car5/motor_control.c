/*
 * motor_control.c
 *
 *  Created on: May 19, 2025
 */

#include "motor_control.h"

void MotorSpeed(uint16_t value)
{
	TIM3->CCR1 = value;
	TIM3->CCR2 = value;
}

void GoForward()  // 전진
{
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, LED_LOW);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, LED_HIGH);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, LED_LOW);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, LED_HIGH);

}

void GoBackward()  // 후진
{
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, LED_HIGH);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, LED_LOW);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, LED_HIGH);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, LED_LOW);

}

void TurnLeft()  // 좌회전
{
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, LED_HIGH);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, LED_LOW);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, LED_LOW);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, LED_HIGH);

}

void TurnRight()  // 우회전
{
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, LED_LOW);
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, LED_HIGH);
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, LED_HIGH);
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, LED_LOW);

}

void CarStop()  // 정지
{
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, LED_HIGH);
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, LED_HIGH);
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, LED_HIGH);
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, LED_HIGH);

}

