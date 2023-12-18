/*
 * R_LED.h
 *
 *  Created on: Nov 20, 2023
 *      Author: Youssif Hossam
 */

#ifndef HAL_LEDS_LEDS_H_
#define HAL_LEDS_LEDS_H_

#include "../../LIB/std_types.h"

#define G_LED_PORT_ID			PORTB_ID
#define G_LED_PIN_ID			PIN1_ID

#define R_LED_PORT_ID			PORTB_ID
#define R_LED_PIN_ID			PIN0_ID


void G_LED_init(void);

void R_LED_init(void);

void G_LED_on(void);

void G_LED_off(void);

void R_LED_on(void);

void R_LED_off(void);

#endif /* HAL_LEDS_LEDS_H_ */
