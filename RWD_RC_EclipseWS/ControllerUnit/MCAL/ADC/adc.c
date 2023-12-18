/*	______________________________________________________________________________
   |																			  |
   | Module: ADC																  |
   |																			  |
   | File Name: adc.h															  |
   |																			  |
   | Description: Source file for the ATmega32 ADC driver							  |
   |																			  |
   | Author: Youssif Hossam														  |
   |______________________________________________________________________________|
 */

#include "adc.h"
#include "../../LIB/common_macros.h" /* To use the macros like SET_BIT */
#include <avr/io.h> /* To use the IO Ports Registers */
#include <util/delay.h>

float32 ADC_RefVoltValue;	/* Variable that sensors will use in its calculations */

/*______________________________________________________________________________
 |                               Functions Definitions                          |
 |______________________________________________________________________________|
 */

void ADC_init(const ADC_ConfigType * Config_Ptr){

		switch(Config_Ptr->ref_volt){
		case Ext_AVCC:
			ADC_RefVoltValue = 5;
			break;

		case Int_2_56V:
			ADC_RefVoltValue = 2.56;
			break;
		}
		/* ADMUX Register Bits Description:
		 -> REFS1:0 = 01 to choose the reference voltage
		 -> ADLAR   = 0 (right adjusted)
		 -> MUX4:0  = 00000 to choose channel 0 as initialization
		 */
		ADMUX = (ADMUX & 0x3F) | ((Config_Ptr->ref_volt)<<6);

		/* ADCSRA Register Bits Description:
		 -> ADEN    = 1 Enable ADC
		 -> ADIE    = 0 Disable ADC Interrupt
		 -> ADATE   = 0 Disable Auto Trigger
		 -> ADPS2:0  = selecting the prescaler.
		 */
		ADCSRA = (1<<ADEN) | ((ADCSRA & 0xF8) | (Config_Ptr->prescaler));

}

uint16 ADC_readChannel(uint8 ch_num){

	/* Choosing the correct channel by setting the channel number in MUX4:0 bits */
	ADMUX = (ADMUX & 0xE0)|(ch_num & 0x1F);

	SET_BIT(ADCSRA , ADSC);	/* Start conversion write '1' to ADSC */

	while(BIT_IS_CLEAR(ADCSRA,ADIF));	/* Wait for conversion to complete, ADIF becomes '1' */

	SET_BIT(ADCSRA,ADIF);	/* Clear ADIF by write '1' to it :) */

	return ADC;	/* Read the digital value from the data register */
}

