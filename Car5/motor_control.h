/*
 * motor_control.h
 *
 *  Created on: May 19, 2025
 */

#ifndef INC_MOTOR_CONTROL_H_
#define INC_MOTOR_CONTROL_H_

#include "main.h"

// L298N 모터 드라이버 제어를 위해
typedef enum
{
	LED_LOW = 0,
	LED_HIGH
}LED_STATE;


void MotorSpeed(uint16_t value);
void GoForward();
void GoBackward();
void TurnLeft();
void TurnRight();
void CarStop();



#endif /* INC_MOTOR_CONTROL_H_ */
