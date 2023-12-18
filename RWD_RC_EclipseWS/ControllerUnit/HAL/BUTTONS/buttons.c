/*
 * buttons.c
 *
 *  Created on: Nov 24, 2023
 *      Author: Youssif Hossam
 */


#include "buttons.h"
#include "../../MCAL/GPIO/gpio.h"

void BUTTONS_init(void){
	GPIO_setupPinDirection(BUTTONS_PB1_PORT_ID , BUTTONS_PB1_PIN_ID , PIN_INPUT);
	GPIO_setupPinDirection(BUTTONS_PB2_PORT_ID , BUTTONS_PB2_PIN_ID , PIN_INPUT);
	GPIO_setupPinDirection(BUTTONS_PB3_PORT_ID , BUTTONS_PB3_PIN_ID , PIN_INPUT);
	GPIO_setupPinDirection(BUTTONS_TS1_PORT_ID , BUTTONS_TS1_PIN_ID , PIN_INPUT);
	GPIO_setupPinDirection(BUTTONS_TS2_PORT_ID , BUTTONS_TS2_PIN_ID , PIN_INPUT);

	GPIO_writePin(BUTTONS_PB1_PORT_ID , BUTTONS_PB1_PIN_ID , LOGIC_HIGH);
	GPIO_writePin(BUTTONS_PB2_PORT_ID , BUTTONS_PB2_PIN_ID , LOGIC_HIGH);
	GPIO_writePin(BUTTONS_PB3_PORT_ID , BUTTONS_PB3_PIN_ID , LOGIC_HIGH);
	GPIO_writePin(BUTTONS_TS1_PORT_ID , BUTTONS_TS1_PIN_ID , LOGIC_HIGH);
	GPIO_writePin(BUTTONS_TS2_PORT_ID , BUTTONS_TS2_PIN_ID , LOGIC_HIGH);
}
uint8 BUTTONS_PB1_getStatus(void){
	if(!GPIO_readPin(BUTTONS_PB1_PORT_ID , BUTTONS_PB1_PIN_ID))
		return PRESSED;
	else
		return NOT_PRESSED;
}


uint8 BUTTONS_PB2_getStatus(void){
	if(!GPIO_readPin(BUTTONS_PB2_PORT_ID , BUTTONS_PB2_PIN_ID))
		return PRESSED;
	else
		return NOT_PRESSED;
}

uint8 BUTTONS_PB3_getStatus(void){
	if(!GPIO_readPin(BUTTONS_PB3_PORT_ID , BUTTONS_PB3_PIN_ID))
		return PRESSED;
	else
		return NOT_PRESSED;
}

uint8 BUTTONS_TS1_getStatus(void){
	if(!GPIO_readPin(BUTTONS_TS1_PORT_ID , BUTTONS_TS1_PIN_ID))
		return PRESSED;
	else
		return NOT_PRESSED;
}

uint8 BUTTONS_TS2_getStatus(void){
	if(!GPIO_readPin(BUTTONS_TS2_PORT_ID , BUTTONS_TS2_PIN_ID))
		return PRESSED;
	else
		return NOT_PRESSED;
}
