/*
 * ultrasoic.c
 *
 *  Created on: Mar 19, 2025
 */

#include "ultrasonic.h"

static uint16_t IC_Value1 = 0;  // 에코핀이 하이엣지 일때
static uint16_t IC_Value2 = 0;  // 에코핀이 로우엣지 일때
static uint16_t echoTime = 0;  //에코핀의 하이엣지와 로우엣지 사이의 시간(카운드 갯수)
static uint8_t captureFlag = 0;  //

uint8_t distance = 100;   // 거리



void HCRSC04_Trigger(void)
{
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, 0);
	delay_us(1);

	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, 1);
	delay_us(10);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, 0);


	__HAL_TIM_ENABLE_IT(&htim5, TIM_IT_CC1);

}


void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1)
	{
		if(captureFlag == 0)		// 아직 캡처 안 했으면
		{
			// 첫번째 밸류에 캡처 인터럽트가 발생하면 카운트 값을 가져옴
			IC_Value1 = HAL_TIM_ReadCapturedValue(&htim5, TIM_CHANNEL_1);
			captureFlag = 1;		//캡쳐 했다고 플래그 세움

			__HAL_TIM_SET_CAPTUREPOLARITY(&htim5, TIM_CHANNEL_1, TIM_INPUTCHANNELPOLARITY_FALLING);

		}

		else if(captureFlag == 1)			// 한번 캡처 했으면
		{
			IC_Value2 = HAL_TIM_ReadCapturedValue(&htim5, TIM_CHANNEL_1);
			__HAL_TIM_SET_COUNTER(&htim5, 0);


			if(IC_Value2 > IC_Value1)
			{
				echoTime = IC_Value2 - IC_Value1;


			}
			else if(IC_Value1 > IC_Value2)
			{

				echoTime = (0xfff - IC_Value1) + IC_Value2;



			}

			//
			distance = echoTime / 58;
			captureFlag = 0;

			__HAL_TIM_SET_CAPTUREPOLARITY(&htim5, TIM_CHANNEL_1, TIM_INPUTCHANNELPOLARITY_RISING);
			__HAL_TIM_DISABLE_IT(&htim5, TIM_IT_CC1);

		}


	}


}




//#define TRIG1_PIN GPIO_PIN_8  // 첫 번째 초음파 센서 트리거 핀
//#define TRIG2_PIN GPIO_PIN_9  // 두 번째 초음파 센서 트리거 핀
//#define TRIG3_PIN GPIO_PIN_10 // 세 번째 초음파 센서 트리거 핀
//
//#define ECHO1_PIN GPIO_PIN_6  // 첫 번째 초음파 센서 Echo 핀
//#define ECHO2_PIN GPIO_PIN_7  // 두 번째 초음파 센서 Echo 핀
//#define ECHO3_PIN GPIO_PIN_11 // 세 번째 초음파 센서 Echo 핀
//
//void triggerUltrasonic(GPIO_TypeDef *GPIOx, uint16_t TRIG_PIN) {
//    HAL_GPIO_WritePin(GPIOx, TRIG_PIN, GPIO_PIN_RESET);
//    delay_us(2);
//    HAL_GPIO_WritePin(GPIOx, TRIG_PIN, GPIO_PIN_SET);
//    delay_us(10);
//    HAL_GPIO_WritePin(GPIOx, TRIG_PIN, GPIO_PIN_RESET);
//}
//
//void measureDistance() {
//    // 각 초음파 센서를 개별적으로 트리거
//    triggerUltrasonic(GPIOA, TRIG1_PIN);
//    triggerUltrasonic(GPIOA, TRIG2_PIN);
//    triggerUltrasonic(GPIOA, TRIG3_PIN);
//
//    // Echo 핀을 통해 반사 신호를 개별적으로 감지
//    HAL_TIM_IC_Start_IT(&htim5, TIM_CHANNEL_1); // 센서 1
//    HAL_TIM_IC_Start_IT(&htim5, TIM_CHANNEL_2); // 센서 2
//    HAL_TIM_IC_Start_IT(&htim5, TIM_CHANNEL_3); // 센서 3
//}
//
//void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim) {
//    if(htim->Instance == TIM5) {
//        if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1) {
//            distance1 = HAL_TIM_ReadCapturedValue(&htim5, TIM_CHANNEL_1) / 58;
//        }
//        else if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_2) {
//            distance2 = HAL_TIM_ReadCapturedValue(&htim5, TIM_CHANNEL_2) / 58;
//        }
//        else if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_3) {
//            distance3 = HAL_TIM_ReadCapturedValue(&htim5, TIM_CHANNEL_3) / 58;
//        }
//    }
//}
