/*	______________________________________________________________________________
   |																			  |
   | Module: L293D																  |
   |																			  |
   | File Name: l293d.c															  |
   |																			  |
   | Description: Source file for the ATmega32 L293D driver						  |
   |																			  |
   | Author: Youssif Hossam														  |
   |______________________________________________________________________________|
 */

#include "l293d.h"
#include "../../MCAL/GPIO/gpio.h"
#include <avr/io.h>

/*______________________________________________________________________________
 |                               Functions Definitions                          |
 |______________________________________________________________________________|
 */

/*
 * Description :
 -> Function responsible for initialize the L293D driver.
 -> Function take a structure containing the configuration parameters.
 */
void L293D_Init(L293D_ChannelMode ChannelMode){
	switch(ChannelMode){
	case CHANNEL1_MODE:
		GPIO_setupPinDirection(L293D_IN1_PORT_ID , L293D_IN1_PIN_ID , PIN_OUTPUT);
		GPIO_setupPinDirection(L293D_IN2_PORT_ID , L293D_IN2_PIN_ID , PIN_OUTPUT);
		GPIO_setupPinDirection(L293D_EN1_PORT_ID , L293D_EN1_PIN_ID , PIN_OUTPUT);
		GPIO_writePin(L293D_IN1_PORT_ID , L293D_IN1_PIN_ID , LOGIC_LOW);
		GPIO_writePin(L293D_IN2_PORT_ID , L293D_IN2_PIN_ID , LOGIC_LOW);
		GPIO_writePin(L293D_EN1_PORT_ID , L293D_EN1_PIN_ID , LOGIC_LOW);
		break;
	case CHANNEL2_MODE:
		GPIO_setupPinDirection(L293D_IN3_PORT_ID , L293D_IN3_PIN_ID , PIN_OUTPUT);
		GPIO_setupPinDirection(L293D_IN4_PORT_ID , L293D_IN4_PIN_ID , PIN_OUTPUT);
		GPIO_setupPinDirection(L293D_EN2_PORT_ID , L293D_EN2_PIN_ID , PIN_OUTPUT);
		GPIO_writePin(L293D_IN3_PORT_ID , L293D_IN3_PIN_ID , LOGIC_LOW);
		GPIO_writePin(L293D_IN4_PORT_ID , L293D_IN4_PIN_ID , LOGIC_LOW);
		GPIO_writePin(L293D_EN2_PORT_ID , L293D_EN2_PIN_ID , LOGIC_LOW);

		break;
	case DUAL_CHANNEL_MODE:
		GPIO_setupPinDirection(L293D_IN1_PORT_ID , L293D_IN1_PIN_ID , PIN_OUTPUT);
		GPIO_setupPinDirection(L293D_IN2_PORT_ID , L293D_IN2_PIN_ID , PIN_OUTPUT);
		GPIO_setupPinDirection(L293D_IN3_PORT_ID , L293D_IN3_PIN_ID , PIN_OUTPUT);
		GPIO_setupPinDirection(L293D_IN4_PORT_ID , L293D_IN4_PIN_ID , PIN_OUTPUT);
		GPIO_setupPinDirection(L293D_EN1_PORT_ID , L293D_EN1_PIN_ID , PIN_OUTPUT);
		GPIO_setupPinDirection(L293D_EN2_PORT_ID , L293D_EN2_PIN_ID , PIN_OUTPUT);
		GPIO_writePin(L293D_IN1_PORT_ID , L293D_IN1_PIN_ID , LOGIC_LOW);
		GPIO_writePin(L293D_IN2_PORT_ID , L293D_IN2_PIN_ID , LOGIC_LOW);
		GPIO_writePin(L293D_IN3_PORT_ID , L293D_IN3_PIN_ID , LOGIC_LOW);
		GPIO_writePin(L293D_IN4_PORT_ID , L293D_IN4_PIN_ID , LOGIC_LOW);
		GPIO_writePin(L293D_EN1_PORT_ID , L293D_EN1_PIN_ID , LOGIC_LOW);
		GPIO_writePin(L293D_EN2_PORT_ID , L293D_EN2_PIN_ID , LOGIC_LOW);
		break;
	}

}

/*
 * Description :
 -> Setup the rotation direction of the motor.
 -> The function take the channel and state (OFF , CW , A-CW) and the speed (0-100)
 */
void L293D_Rotate(uint8 Channel , DcMotor_State state){

	/* Make a PWM of duty cycle based on the speed */
	GPIO_writePin(L293D_EN1_PORT_ID,L293D_EN1_PIN_ID,LOGIC_HIGH);

	/* Controling the direction based on the speed argument and the channel required */
	switch(Channel){
	case CHANNEL1_MODE:
		switch(state){
		case OFF:
			GPIO_writePin(L293D_IN1_PORT_ID,L293D_IN1_PIN_ID,LOGIC_LOW);
			GPIO_writePin(L293D_IN2_PORT_ID,L293D_IN2_PIN_ID,LOGIC_LOW);
			break;
		case CW:
			GPIO_writePin(L293D_IN1_PORT_ID,L293D_IN1_PIN_ID,LOGIC_HIGH);
			GPIO_writePin(L293D_IN2_PORT_ID,L293D_IN2_PIN_ID,LOGIC_LOW);
			break;
		case A_CW:
			GPIO_writePin(L293D_IN1_PORT_ID,L293D_IN1_PIN_ID,LOGIC_LOW);
			GPIO_writePin(L293D_IN2_PORT_ID,L293D_IN2_PIN_ID,LOGIC_HIGH);
			break;
		}
		break;
		case CHANNEL2_MODE:
			switch(state){
			case OFF:
				GPIO_writePin(L293D_IN3_PORT_ID,L293D_IN3_PIN_ID,LOGIC_LOW);
				GPIO_writePin(L293D_IN4_PORT_ID,L293D_IN4_PIN_ID,LOGIC_LOW);
				break;
			case CW:
				GPIO_writePin(L293D_IN3_PORT_ID,L293D_IN3_PIN_ID,LOGIC_HIGH);
				GPIO_writePin(L293D_IN4_PORT_ID,L293D_IN4_PIN_ID,LOGIC_LOW);
				break;
			case A_CW:
				GPIO_writePin(L293D_IN3_PORT_ID,L293D_IN3_PIN_ID,LOGIC_LOW);
				GPIO_writePin(L293D_IN4_PORT_ID,L293D_IN4_PIN_ID,LOGIC_HIGH);
				break;
			}
			break;
	}
}

