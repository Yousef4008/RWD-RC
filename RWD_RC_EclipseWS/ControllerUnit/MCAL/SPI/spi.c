 /*	____________________________________________________________________________
  |																			    |
  | Module: SPI																    |
  |																			    |
  | File Name: spi.c														    |
  |																			    |
  | Description: Source file for the SPI driver							        |
  |																			    |
  | Author: Youssif Hossam													    |
  |_____________________________________________________________________________|
*/


#include <avr/io.h>
#include "spi.h"
#include "../GPIO/gpio.h"
#include "../../LIB/common_macros.h"

/*
 * Description :
 * Initialize the SPI device as Master.
 */
void SPI_init(uint8 mode){

	GPIO_setupPinDirection(PORTB_ID,PIN4_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(PORTB_ID,PIN5_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(PORTB_ID,PIN6_ID,PIN_INPUT);
	GPIO_setupPinDirection(PORTB_ID,PIN7_ID,PIN_OUTPUT);



	if(mode == MASTER_MODE)
		SPCR = (1<<SPE) | (1<<MSTR);
	else if (mode == SLEVE_MODE)
		SPCR = (1<<SPE);

	SPSR &= ~(1<<SPI2X);
}


/*
 * Description :
 * Send the required data through SPI to the other SPI device.
 * In the same time data will be received from the other device.
 */
uint8 SPI_sendReceiveByte(uint8 data){
	SPDR = data;
	while(BIT_IS_CLEAR(SPSR,SPIF));
	return SPDR;
}

/*
 * Description :
 * Send the required string through SPI to the other SPI device.
 */
void SPI_sendString(const uint8 *str){
	uint8 i = 0;

	/* Send the whole string */
	while(str[i] != '\0')
	{
		/*
		 * received_data contains the received data from the other device.
		 * It is a dummy data variable as we just need to send the string to other device.
		 */
		SPI_sendReceiveByte(str[i]);
		i++;
	}
	SPI_sendReceiveByte('#');
}

/*
 * Description :
 * Receive the required string until the '#' symbol through SPI from the other SPI device.
 */
void SPI_receiveString(uint8 *str){
	uint8 i = 0;

	/* Receive the first byte */
	str[i] = SPI_sendReceiveByte(SPI_DEFAULT_DATA_VALUE);

	/* Receive the whole string until the '#' */
	while(str[i] != '#')
	{
		i++;
		str[i] = SPI_sendReceiveByte(SPI_DEFAULT_DATA_VALUE);
	}

	/* After receiving the whole string plus the '#', replace the '#' with '\0' */
	str[i] = '\0';
}
