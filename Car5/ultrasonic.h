/*
 * ultrasonic.h
 *
 *  Created on: Mar 19, 2025
 */

#ifndef INC_ULTRASONIC_H_
#define INC_ULTRASONIC_H_


#include "main.h"
#include "tim.h"
#include "delay.h"

extern uint8_t distance;   // 거리

void HCRSC04_Trigger(void);


#endif /* INC_ULTRASONIC_H_ */
