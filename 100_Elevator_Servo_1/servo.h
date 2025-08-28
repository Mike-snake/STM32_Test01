#ifndef INC_SERVO_H_
#define INC_SERVO_H_

#include "main.h"



void servo_open_door(void);
void servo_closed_door(void);
void servo_update(void);

extern uint8_t servo_trigger;	// 전역변수 선언




#endif /* INC_SERVO_H_ */
