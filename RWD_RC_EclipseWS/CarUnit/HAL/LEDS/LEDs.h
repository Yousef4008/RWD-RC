/*
 * R_LED.h
 *
 *  Created on: Nov 20, 2023
 *      Author: Youssif Hossam
 */

#ifndef HAL_LEDS_LEDS_H_
#define HAL_LEDS_LEDS_H_

#include "../../LIB/std_types.h"

#define G_LED_PORT_ID			PORTC_ID
#define G_LED_PIN_ID			PIN5_ID

#define R_LED_PORT_ID			PORTC_ID
#define R_LED_PIN_ID			PIN7_ID


void G_LED_init(void);

void R_LED_init(void);

void G_LED_on(void);

void G_LED_off(void);

void R_LED_on(void);

void R_LED_off(void);

#endif /* HAL_LEDS_LEDS_H_ */
