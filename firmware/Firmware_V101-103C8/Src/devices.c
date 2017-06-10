/*
 * devices.c
 *
 *  Created on: Jun 7, 2017
 *      Author: Heethesh
 */

#include "stm32f1xx_hal.h"
#include "peripherals.h"
#include "devices.h"

// Configuration structure declarations
extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;

/* led -> LED Number, val -> Digital output value */
void toggleLED(int led, int val)
{
	if (led == 0) HAL_GPIO_WritePin(Red_LED_GPIO_Port, Red_LED_Pin, val);
	if (led == 1) HAL_GPIO_WritePin(Blue_LED_GPIO_Port, Blue_LED_Pin, val);
	if (led == 2) HAL_GPIO_WritePin(White_LED_GPIO_Port, White_LED_Pin, val);
}

/* LED sequence on reset */
void LED_StartupSequence()
{
	for (int i=0; i<3; i++)
	{
		toggleLED(WHITE, 1);
		HAL_Delay(100);
		toggleLED(WHITE, 0);
		toggleLED(RED, 1);
		HAL_Delay(100);
		toggleLED(RED, 0);
		toggleLED(BLUE, 1);
		HAL_Delay(100);
		toggleLED(BLUE, 0);
	}
}

/**********************************
 Function name	:	Motor1_SetPWM
 Functionality	:	Set PWM value for the motor
 Arguments		:	PWM Value (0-1000)
 Return Value	:	None
 Example Call	:	Motor1_SetPWM()
 ***********************************/
void Motor1_SetPWM(int pwm)
{
	__HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_4, pwm); // Motor 1
}

/**********************************
 Function name	:	Motor2_SetPWM
 Functionality	:	Set PWM value for the motor
 Arguments		:	PWM Value (0-1000)
 Return Value	:	None
 Example Call	:	Motor2_SetPWM()
 ***********************************/
void Motor2_SetPWM(int pwm)
{
	__HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_3, pwm); // Motor 2
}

/**********************************
 Function name	:	Motor3_SetPWM
 Functionality	:	Set PWM value for the motor
 Arguments		:	PWM Value (0-1000)
 Return Value	:	None
 Example Call	:	Motor3_SetPWM()
 ***********************************/
void Motor3_SetPWM(int pwm)
{
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_2, pwm); // Motor 3
}

/**********************************
 Function name	:	Motor4_SetPWM
 Functionality	:	Set PWM value for the motor
 Arguments		:	PWM Value (0-1000)
 Return Value	:	None
 Example Call	:	Motor4_SetPWM()
 ***********************************/
void Motor4_SetPWM(int pwm)
{
	__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_3, pwm); // Motor 4
}

/**********************************
 Function name	:	Motor5_SetPWM
 Functionality	:	Set PWM value for the motor
 Arguments		:	PWM Value (0-1000)
 Return Value	:	None
 Example Call	:	Motor5_SetPWM()
 ***********************************/
void Motor5_SetPWM(int pwm)
{
	__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_4, pwm); // Motor 5
}

/**********************************
 Function name	:	Motor6_SetPWM
 Functionality	:	Set PWM value for the motor
 Arguments		:	PWM Value (0-1000)
 Return Value	:	None
 Example Call	:	Motor6_SetPWM()
 ***********************************/
void Motor6_SetPWM(int pwm)
{
	__HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_4, pwm); // Motor 6
}

/**********************************
 Function name	:	PWM_Init
 Functionality	:	Start PWM Timers
					Motor 1 --> PB9  - TIM4 PWM CH4
					Motor 2 --> PB8  - TIM4 PWM CH3
					Motor 3 --> PA1  - TIM2 PWM CH2
					Motor 4 --> PB0  - TIM3 PWM CH3
					Motor 5 --> PB1  - TIM3 PWM CH4
					Motor 6 --> PA11 - TIM1 PWM CH4
 Arguments		:	None
 Return Value	:	None
 Example Call	:	PWM_Init()
 ***********************************/
void PWM_Init(void)
{
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_4);

#ifdef HEXCOPTER
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_4);
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_4);
#endif
}

/**********************************
 Function name	:	Devices_Init
 Functionality	:	To initialize all devices and peripherals
 Arguments		:	PWM Value (0-1000)
 Return Value	:	None
 Example Call	:	Devices_Init()
 ***********************************/
void Devices_Init(void)
{
	Peripherals_Init();
	PWM_Init();
	LED_StartupSequence();
}

