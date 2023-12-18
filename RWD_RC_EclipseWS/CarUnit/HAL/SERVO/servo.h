/*	____________________________________________________________________________
  |																			    |
  | Module: SERVO MOTOR														    |
  |																			    |
  | File Name: servo.h														    |
  |																			    |
  | Description: Header file for the servo motor						        |
  |																			    |
  | Author: Youssif Hossam													    |
  |_____________________________________________________________________________|
*/

#ifndef HAL_SERVO_SERVO_H_
#define HAL_SERVO_SERVO_H_

#include "../../LIB/std_types.h"

/*______________________________________________________________________________
 |                               		Definitions                        		|
 |______________________________________________________________________________|
 */
#define SERVO_0_DEG		600

#define SERVO_90_DEG 	1500

#define SERVO_180_DEG	2400
/*______________________________________________________________________________
 |                               Functions Prototypes                           |
 |______________________________________________________________________________|
 */
void SERVO_init(void);
void SERVO_setDegree(uint16 degree);

#endif /* HAL_SERVO_SERVO_H_ */
