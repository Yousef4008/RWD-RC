/*	____________________________________________________________________________
  |																			    |
  | Module: BUZZER															    |
  |																			    |
  | File Name: buzzer.h														    |
  |																			    |
  | Description: Header file for the buzzer								        |
  |																			    |
  | Author: Youssif Hossam													    |
  |_____________________________________________________________________________|
*/

#ifndef HAL_BUZZER_BUZZER_H_
#define HAL_BUZZER_BUZZER_H_

#include "../../LIB/std_types.h"
/*______________________________________________________________________________
 |                               		Definitions                        		|
 |______________________________________________________________________________|
 */

#define BUZZER_PORT_ID			PORTC_ID
#define BUZZER_PIN_ID			PIN1_ID

/*______________________________________________________________________________
 |                               Functions Prototypes                           |
 |______________________________________________________________________________|
 */

/*
 * Description :
 -> Setup the direction for the buzzer pin as output pin.
 */
void BUZZER_init();

/*
 * Description :
 -> Function to enable the Buzzer.
 */
void BUZZER_on();

/*
 * Description :
 -> Function to disable the Buzzer.
 */
void BUZZER_off();

#endif /* HAL_BUZZER_BUZZER_H_ */
