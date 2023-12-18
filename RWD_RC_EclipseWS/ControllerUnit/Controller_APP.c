 /*	____________________________________________________________________________
  |																			    |
  | APP: Controller Unit												 	    |
  |																			    |
  | File Name: APP.c														    |
  |																			    |
  | Description: Source file for the controller unit							|
  |																			    |
  | Author: Youssif Hossam 														|
  |_____________________________________________________________________________|
*/

#include "HAL/NRF/nrf.h"
#include "MCAL/GPIO/gpio.h"
#include "HAL/POT/pot.h"
#include "HAL/LEDS/LEDs.h"
#include "HAL/BUTTONS/buttons.h"
#include <util/delay.h>
#include <avr/io.h>
#include "LIB/common_macros.h"
#include "LIB/All_Project_Flags.h"
/*define the array of addresses for send and receive data from another part of NRF24L01*/
uint8 tx_address[5] ={0xEE,0xDD,0xCC,0xBB,0xAA};
/*
 * this array to store in it the two byte used for sending and receive data,
 * this array consist of two elements :
 * 1- the first index with it is 8 bits used for storing the ADC value.
 * 2- the second byte was divided into 6 bits using as a flags.
 *
 */
uint8 tx_data[2] = {0,0};

int main(void){

	POT_init();			/*Initialization of Potentiometer*/
	BUTTONS_init();		/*Initialization of buttons (toggle & 3 push buttons) using internal pull up resistor*/

	/*Initialization of Leds*/
	G_LED_init();
	R_LED_init();

	/* Flashing the leds and buzzer for 0.5 second*/
	G_LED_on();
	R_LED_on();

	_delay_ms(500);

	R_LED_off();
	G_LED_off();

	/*Initialize NRF and give each device master at first*/
	NRF24_init();
	/*Initialize the NRF in the car as a receiver that receive from control unit*/
	NRF24_txMode(tx_address , 10);

	while(1){

		/*
		* store the value of ADC in the first index in tx_data array
		* the value from ADC divided by 10 to get a value from 0 to 10
		* to able to send it in unsigned char 8 bit
		*
		*/
		tx_data[0] = POT_readPercentage();

		/*
		* this check on toggle switch if the pin no.2 read zero you
		* should put 1 in the corresponding bit in flags variable:
		* 1- if read zero set this bit and send by using NRF_transmite
		* 2- else clear this bit.
		*
		*/
		if(BUTTONS_PB1_getStatus() == PRESSED){
			G_LED_on();
			SET_BIT(tx_data[1],PUSH_BUTTON_1);
		}
		else{
			CLEAR_BIT(tx_data[1],PUSH_BUTTON_1);
		}

		if(BUTTONS_PB2_getStatus() == PRESSED){
			G_LED_on();
			SET_BIT(tx_data[1],PUSH_BUTTON_2);
		}
		else{
			CLEAR_BIT(tx_data[1],PUSH_BUTTON_2);
		}

		if(BUTTONS_PB3_getStatus() == PRESSED){
			G_LED_on();
			SET_BIT(tx_data[1],PUSH_BUTTON_3);
		}
		else{
			CLEAR_BIT(tx_data[1],PUSH_BUTTON_3);
		}

		if(BUTTONS_TS1_getStatus() == PRESSED){
			SET_BIT(tx_data[1],TOGGLE_SWITCH_UP);
		}
		else{
			CLEAR_BIT(tx_data[1],TOGGLE_SWITCH_UP);
		}

		if(BUTTONS_TS2_getStatus() == PRESSED){
			SET_BIT(tx_data[1],TOGGLE_SWITCH_DOWN);
		}
		else{
			CLEAR_BIT(tx_data[1],TOGGLE_SWITCH_DOWN);
		}

		/*
		* now sent the array of data (tx_data) that consist of two bits:
		* 1- first index consist of one byte containing the ADC value.
		* 2- the second byte containing the 4 flags for motion the car
		* 	  forward, backward, start motion, and buzzer.
		*
		*/
		if(NRF_transmit(tx_data)){
			/*Flashing led indicating that transmission is completed successfully*/
			R_LED_on();
			_delay_ms(10);
			R_LED_off();
		}
		G_LED_off();
		_delay_ms(10);
	}
	return 0;
}
