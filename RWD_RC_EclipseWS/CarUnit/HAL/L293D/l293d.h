/*	______________________________________________________________________________
   |																			  |
   | Module: L293D																  |
   |																			  |
   | File Name: l293d.h															  |
   |																			  |
   | Description: Header file for the ATmega32 L293D driver						  |
   |																			  |
   | Author: Youssif Hossam														  |
   |______________________________________________________________________________|
*/

#ifndef HAL_L293D_L293D_H_
#define HAL_L293D_L293D_H_

#include "../../LIB/std_types.h"

/*______________________________________________________________________________
 |                               		Definitions                        		|
 |______________________________________________________________________________|
 */

#define L293D_IN1_PORT_ID		PORTA_ID
#define L293D_IN1_PIN_ID		PIN1_ID

#define L293D_IN2_PORT_ID		PORTA_ID
#define L293D_IN2_PIN_ID		PIN6_ID

#define L293D_IN3_PORT_ID		PORTA_ID
#define L293D_IN3_PIN_ID		PIN3_ID

#define L293D_IN4_PORT_ID		PORTA_ID
#define L293D_IN4_PIN_ID		PIN4_ID

#define L293D_EN1_PORT_ID		PORTA_ID
#define L293D_EN1_PIN_ID		PIN0_ID

#define L293D_EN2_PORT_ID		PORTA_ID
#define L293D_EN2_PIN_ID		PIN4_ID

/*______________________________________________________________________________
 |                               Types Declaration                              |
 |______________________________________________________________________________|
 */

typedef enum {
	OFF , CW , A_CW
}DcMotor_State;

typedef enum {
	CHANNEL1_MODE = 1 , CHANNEL2_MODE , DUAL_CHANNEL_MODE
}L293D_ChannelMode;

/*______________________________________________________________________________
 |                               Functions Prototypes                           |
 |______________________________________________________________________________|
 */
/*
 * Description :
 -> Function responsible for initialize the L293D driver.
 -> Function take a structure containing the configuration parameters.
 */
void L293D_Init(L293D_ChannelMode ChannelMode);

/*
 * Description :
 -> Setup the rotation direction of the motor.
 -> The function take the channel and state (OFF , CW , A-CW) and the speed (0-100)
 */
void L293D_Rotate(uint8 Channel , DcMotor_State state);

#endif /* HAL_L293D_L293D_H_ */
