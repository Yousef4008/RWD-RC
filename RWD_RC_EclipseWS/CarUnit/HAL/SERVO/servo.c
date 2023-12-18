/*	____________________________________________________________________________
  |																			    |
  | Module: SERVO MOTOR														    |
  |																			    |
  | File Name: servo.c														    |
  |																			    |
  | Description: Source file for the servo motor						        |
  |																			    |
  | Author: Youssif Hossam													    |
  |_____________________________________________________________________________|
*/

#include "servo.h"
#include "../../MCAL/TIMER1/timer1.h"
#include "../../MCAL/GPIO/gpio.h"

/*______________________________________________________________________________
 |                               Functions Definitions                          |
 |______________________________________________________________________________|
 */

/*
 * Description :
 -> Setup the direction for the servo motor pins as output pin.
 */
void SERVO_init(void){

	GPIO_setupPinDirection(PORTD_ID , PIN5_ID , PIN_OUTPUT);
}

/*
 * Description :
 -> Setting the angle of the servo motor
 */
void SERVO_setDegree(uint16 compare_value){

	Timer1_ConfigType MyConfig = {0 , compare_value , 19999 , CLK_8_PRESCALER , FAST_PWM};
	Timer1_init(&MyConfig);

}
