/*
 * buttons.h
 *
 *  Created on: Nov 24, 2023
 *      Author: Youssif Hossam
 */

#include "../../LIB/std_types.h"

#ifndef HAL_BUTTONS_BUTTONS_H_
#define HAL_BUTTONS_BUTTONS_H_

#define BUTTONS_PB1_PORT_ID			PORTA_ID
#define BUTTONS_PB1_PIN_ID			PIN1_ID

#define BUTTONS_PB2_PORT_ID			PORTA_ID
#define BUTTONS_PB2_PIN_ID			PIN3_ID

#define BUTTONS_PB3_PORT_ID			PORTA_ID
#define BUTTONS_PB3_PIN_ID			PIN7_ID

#define BUTTONS_TS1_PORT_ID			PORTC_ID
#define BUTTONS_TS1_PIN_ID			PIN2_ID

#define BUTTONS_TS2_PORT_ID			PORTC_ID
#define BUTTONS_TS2_PIN_ID			PIN3_ID

#define PRESSED			LOGIC_LOW
#define NOT_PRESSED		LOGIC_HIGH

void BUTTONS_init(void);

uint8 BUTTONS_PB1_getStatus(void);

uint8 BUTTONS_PB2_getStatus(void);

uint8 BUTTONS_PB3_getStatus(void);

uint8 BUTTONS_TS1_getStatus(void);

uint8 BUTTONS_TS2_getStatus(void);

#endif /* HAL_BUTTONS_BUTTONS_H_ */
