 /*	____________________________________________________________________________
  |																			    |
  | APP: Car Unit														 	    |
  |																			    |
  | File Name: APP.c														    |
  |																			    |
  | Description: Source file for the car unit							        |
  |																			    |
  | Author: Youssif Hossam 														|
  |_____________________________________________________________________________|
*/
#include "HAL/LEDS/LEDs.h"
#include "HAL/L293D/l293d.h"
#include "HAL/SERVO/servo.h"
#include "HAL/NRF/nrf.h"
#include "HAL/BUZZER/buzzer.h"
#include "MCAL/GPIO/gpio.h"
#include <util/delay.h>
#include <avr/io.h>
#include "LIB/common_macros.h"
#include "LIB/All_Project_Flags.h"

/*define the array of addresses for send and receive data from another part of NRF24L01*/
uint8 rx_address[] ={0xEE,0xDD,0xCC,0xBB,0xAA};
/*
 * this array to store in it the two byte used for sending and receive data,
 * this array consist of two elements :
 * 1- the first index with it is 8 bits used for storing the ADC value.
 * 2- the second byte was divided into 6 bits using as a flags.
 *
 */
uint8 rx_data[2] = {0,0};



int main(void){

	/*this variable for store in it the value of ADC to rotate the Servo-Motor*/
	uint16 degree = 0;

	/* setup the direction of red & green led ,active low led connection */
	G_LED_init();
	R_LED_init();

	SERVO_init();				/*Initialize Servo-Motor and set up it is pin */
	BUZZER_init();				/*Initialize the pin of the buzzer*/
	L293D_Init(CHANNEL1_MODE);	/*Initialize Dc-Motor and set up it is pin */

	/* Flashing the leds and buzzer for 0.5 second*/
	G_LED_on();
	R_LED_on();
	BUZZER_on();
	_delay_ms(500);
	G_LED_off();
	R_LED_off();
	BUZZER_off();

	/*Initialize NRF and give each device master at first*/
	NRF24_init();
	/*Initialize the NRF in the car as a receiver that receive from control unit*/
	NRF24_rxMode(rx_address , 10);

	while(1){

		NRF24_init();
		NRF24_rxMode(rx_address , 10);

		rx_data[0] = 50;
		rx_data[1] = 0;

		/*
		* this check if the data available on pipe one in NRF receiver if data available:
		*
		* 1- receive this data by NRF24_Receive function in array rx_data, now the data
		* 	  was received and stored in the rx_data array now it contains a two byte first
		* 	  one is the value of ADC passed from controller and the second is LSB 4 flags.
		*
		* 2- then rotate the servo-motor by the value stored in the (degree) variable, to
		* 	  rotate the motor(0 : 180)according to ADC value stored in degree variable.
		*
		* 3- check on the 3 flags in the second index in array rx_data this flags
		* 	  this flags responsible about dc-motor rotation forward or backward or
		* 	  start rotate or not.
		*
		* 4- check on the buzzer by check on the flag sent by the transmitter is this
		* 	  flag set to 1 the buzzer will turn on else it will turn off.
		*
		*/
		if(NRF24_isDataAvailable(1)){

			NRF24_receive(rx_data);		/*receive the  data*/
			R_LED_on();					/* Turning on the led indicating that the data is received*/

			/*
			 * this equation to store the real value of ADC then pass it to servo-motor
			 */
			degree = (uint16)(rx_data[0])*10 + 800;

			SERVO_setDegree(degree);	/*rotate the servo-motor*/

			/*check on the 3 flags (bit 0,1,2) of the motor to rotate */

			if((BIT_IS_SET(rx_data[1],PUSH_BUTTON_2)) && (BIT_IS_SET(rx_data[1],TOGGLE_SWITCH_UP))){
				G_LED_on();
				L293D_Rotate(1 , CW);
			}
			else if((BIT_IS_SET(rx_data[1],PUSH_BUTTON_2)) && (BIT_IS_SET(rx_data[1],TOGGLE_SWITCH_DOWN))){
				G_LED_on();
				L293D_Rotate(1 , A_CW);
			}
			else{
				L293D_Rotate(1 , OFF);
			}

			/*check on turn on buzzer or not*/
			if(BIT_IS_SET(rx_data[1],PUSH_BUTTON_3)){
				G_LED_on();
				BUZZER_on();
			}
			else
				BUZZER_off();

			if(BIT_IS_SET(rx_data[1],PUSH_BUTTON_1)){
				G_LED_on();
			}
			else{

			}
			G_LED_off();
		}
		else{
			R_LED_off();
		}/*End check of data*/

	}
	return 0;
}
