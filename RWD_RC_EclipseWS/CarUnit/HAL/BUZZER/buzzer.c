/*	____________________________________________________________________________
  |																			    |
  | Module: BUZZER															    |
  |																			    |
  | File Name: buzzer.c														    |
  |																			    |
  | Description: Source file for the buzzer								        |
  |																			    |
  | Author: Youssif Hossam													    |
  |_____________________________________________________________________________|
*/

#include "buzzer.h"
#include "../../MCAL/GPIO/gpio.h"
/*______________________________________________________________________________
 |                               Functions Definitions                          |
 |______________________________________________________________________________|
 */

/*
 * Description :
 -> Setup the direction for the buzzer pin as output pin.
 */
void BUZZER_init(){

	GPIO_setupPinDirection(BUZZER_PORT_ID , BUZZER_PIN_ID , PIN_OUTPUT);
	GPIO_writePin(BUZZER_PORT_ID , BUZZER_PIN_ID , LOGIC_LOW);

}

/*
 * Description :
 -> Function to enable the Buzzer.
 */
void BUZZER_on(){

	GPIO_writePin(BUZZER_PORT_ID , BUZZER_PIN_ID , LOGIC_HIGH);

}

/*
 * Description :
 -> Function to disable the Buzzer.
 */
void BUZZER_off(){

	GPIO_writePin(BUZZER_PORT_ID , BUZZER_PIN_ID , LOGIC_LOW);

}
