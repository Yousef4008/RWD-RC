/*	______________________________________________________________________________
   |																			  |
   | Module: ADC																  |
   |																			  |
   | File Name: adc.h															  |
   |																			  |
   | Description: Header file for the ATmega32 ADC driver							  |
   |																			  |
   | Author: Youssif Hossam														  |
   |______________________________________________________________________________|
*/

#ifndef MCAL_ADC_ADC_H_
#define MCAL_ADC_ADC_H_

#include "../../LIB/std_types.h"
/*______________________________________________________________________________
 |                               		Definitions                        		|
 |______________________________________________________________________________|
 */
#define ADC_MAXIMUM_VALUE    1023

/*______________________________________________________________________________
 |                               Types Declaration                              |
 |______________________________________________________________________________|
 */
typedef enum{

	PRESCALER_2 = 1,PRESCALER_4,PRESCALER_8,PRESCALER_16,PRESCALER_32,PRESCALER_64,PRESCALER_128

}ADC_Prescaler;

typedef enum{

	Ext_AREF, Ext_AVCC, Int_2_56V = 3

}ADC_ReferenceVolatge;

typedef struct{

ADC_ReferenceVolatge ref_volt;
ADC_Prescaler prescaler;

}ADC_ConfigType;

extern float32 ADC_RefVoltValue;

/*______________________________________________________________________________
 |                               Functions Prototypes                           |
 |______________________________________________________________________________|
 */

/*
 * Description :
 -> Function responsible for initialize the ADC driver.
 -> Function take a structure containing the configuration parameters.
 */
void ADC_init(const ADC_ConfigType * Config_Ptr);

/*
 * Description :
 -> Function responsible for read analog data from a certain ADC channel
 -> and convert it to digital using the ADC driver.
 */
uint16 ADC_readChannel(uint8 ch_num);


#endif /* MCAL_ADC_ADC_H_ */
