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

#include "pot.h"
#include "../../MCAL/ADC/adc.h"
#include "../../MCAL/GPIO/gpio.h"

/*______________________________________________________________________________
 |                               Functions Definitions                          |
 |______________________________________________________________________________|
 */

/*
 * Description :
 -> Initialization of potentiometer pins as o/p
 */
void POT_init(void){

	GPIO_setupPinDirection(POT_VCC_PORT_ID, POT_VCC_PIN_ID , PIN_OUTPUT);
	GPIO_setupPinDirection(POT_GND_PORT_ID, POT_GND_PIN_ID , PIN_OUTPUT);
	GPIO_writePin(POT_VCC_PORT_ID, POT_VCC_PIN_ID ,LOGIC_HIGH);
	GPIO_writePin(POT_GND_PORT_ID, POT_GND_PIN_ID ,LOGIC_LOW);
	ADC_ConfigType  ADC_MyConfig = {Ext_AVCC , PRESCALER_128};
	ADC_init(&ADC_MyConfig);

}

/*
 * Description :
 -> reading the percentage of Vo volt
 */
uint8 POT_readPercentage(void){
	return (ADC_readChannel(POT_VO_PIN_ID))/10;
}


