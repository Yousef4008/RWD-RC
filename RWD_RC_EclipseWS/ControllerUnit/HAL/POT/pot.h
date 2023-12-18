/*	______________________________________________________________________________
   |																			  |
   | Module: POTENTIOMETER														  |
   |																			  |
   | File Name: pot.h															  |
   |																			  |
   | Description: Header file for the POT							  			  |
   |																			  |
   | Author: Youssif Hossam														  |
   |______________________________________________________________________________|
*/

#ifndef HAL_POT_POT_H_
#define HAL_POT_POT_H_

#include "../../LIB/std_types.h"
/*______________________________________________________________________________
 |                               		Definitions                        		|
 |______________________________________________________________________________|
 */

#define POT_VCC_PORT_ID			PORTA_ID
#define POT_VCC_PIN_ID			PIN0_ID

#define POT_VO_PIN_ID			PIN2_ID

#define POT_GND_PORT_ID			PORTA_ID
#define POT_GND_PIN_ID			PIN4_ID

/*______________________________________________________________________________
 |                               Functions Prototypes                           |
 |______________________________________________________________________________|
 */

/*
 * Description :
 -> Initialization of potentiometer pins as o/p
 */
void POT_init(void);

/*
 * Description :
 -> reading the percentage of Vo volt
 */
uint8 POT_readPercentage(void);

#endif /* HAL_POT_POT_H_ */
