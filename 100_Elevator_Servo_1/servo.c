/*
 * servo.c
 *
 *  Created on: Mar 26, 2025
 *      Author: USER
 */

#include "servo.h"

static uint32_t servo_time =0;	//hal_gettick 저장
uint8_t servo_trigger =0;	// triger


typedef enum
{
	door_idle,			// 0
	open_door,			// 1
	door_wating,		// 2
	close_door			// 3

}DOORSTATE;

static DOORSTATE doorstate = door_idle;		// doorstate = 0 으로 초기화
static uint8_t servo_pos = 0;

void servo_update(void)
{

	switch(doorstate)
	{
		case door_idle:
		doorstate = open_door;				// 다음 case 실행을 위해 변경
		servo_pos = 0;						// servo = 0 초기화
		servo_time = HAL_GetTick();			// 시간저장
		break;

		case open_door:
		if(HAL_GetTick() - servo_time >= 20) 	// 20ms
		{
			TIM3->CCR1 = 50 + servo_pos;		// CCR1 = 50에서부터 1씩 증가,
			servo_pos++;

			servo_time = HAL_GetTick();
			if(servo_pos >= 74)					// servo_pos = 74가 되면
			{
				doorstate = door_wating;		// 다음 case 실행을 위해 변경
				servo_time = HAL_GetTick();		// 시간 저장
			}

			}
		break;

		case door_wating:
		if(HAL_GetTick() - servo_time<2000)			// 2초 딜레이
		{
			break;
		}
		servo_time = HAL_GetTick();
		doorstate =close_door;						// 다음 case 실행을 위해 변경
		break;

		case close_door:
		if(HAL_GetTick() - servo_time >= 20) 		//20ms
		{
			TIM3->CCR1 = 50 + servo_pos;			// servo_pos = 74 -- 감소
			servo_pos--;
			servo_time = HAL_GetTick();

			if(servo_pos == 0 )						// servo_pos가 0이 되면
			{
				servo_trigger =0;
				doorstate = door_idle;				// 다음case문 실행위해, 상태변경
			}
		}
		break;
	}


}


//void servo_open_door(void)
//{
//	TIM3->CCR1 = 30;
//	if(HAL_GetTick()-servo_time < 300) return;
//	servo_time = HAL_GetTick();
//
//
//
//}
//
//void servo_closed_door(void)
//{
//	TIM3->CCR1 = 127;
//	if(HAL_GetTick()-servo_time < 300)return;
//	servo_time = HAL_GetTick();
//	servo_trigger =0;
//
//}



