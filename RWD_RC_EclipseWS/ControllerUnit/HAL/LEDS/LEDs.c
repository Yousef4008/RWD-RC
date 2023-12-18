/*
 * R_LED.c
 *
 *  Created on: Nov 20, 2023
 *      Author: Youssif Hossam
 */


#include "LEDs.h"
#include "../../MCAL/GPIO/gpio.h"

void G_LED_init(void){
	GPIO_setupPinDirection(G_LED_PORT_ID,G_LED_PIN_ID,PIN_OUTPUT);
	GPIO_writePin(G_LED_PORT_ID,G_LED_PIN_ID,LOGIC_HIGH);
}

void R_LED_init(void){
	GPIO_setupPinDirection(R_LED_PORT_ID,R_LED_PIN_ID,PIN_OUTPUT);
	GPIO_writePin(R_LED_PORT_ID,R_LED_PIN_ID,LOGIC_HIGH);
}

void G_LED_on(void){
	GPIO_writePin(G_LED_PORT_ID,G_LED_PIN_ID,LOGIC_LOW);
}

void G_LED_off(void){
	GPIO_writePin(G_LED_PORT_ID,G_LED_PIN_ID,LOGIC_HIGH);
}

void R_LED_on(void){
	GPIO_writePin(R_LED_PORT_ID,R_LED_PIN_ID,LOGIC_LOW);
}

void R_LED_off(void){
	GPIO_writePin(R_LED_PORT_ID,R_LED_PIN_ID,LOGIC_HIGH);
}
