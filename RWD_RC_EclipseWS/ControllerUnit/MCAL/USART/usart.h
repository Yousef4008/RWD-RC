/*	____________________________________________________________________________
  |																			    |
  | Module: UART															    |
  |																			    |
  | File Name: uart.c														    |
  |																			    |
  | Description: Header file for the UART AVR driver					        |
  |																			    |
  | Author: Youssif Hossam													    |
  |_____________________________________________________________________________|
*/

#ifndef USART_H_
#define USART_H_

#include "../../LIB/std_types.h"

/*______________________________________________________________________________
 |                       	   Types Definitions                   		     	|
 |______________________________________________________________________________|
 */
typedef enum { FIVE_BIT_MODE , SIX_BIT_MODE  = 2 , SEVEN_BIT_MODE = 4, EIGHT_BIT_MODE = 6} UART_BitData;

typedef enum { DISABLED_PARITY , EVEN_PARITY = 32 , ODD_PARITY = 48 } UART_Parity;

typedef enum { ONE_STOP_BIT , TWO_STOP_BIT = 8} UART_StopBit;

typedef struct  {
	UART_BitData bit_data;
	UART_Parity parity;
	UART_StopBit stop_bit;
	uint32 baud_rate;
}UART_ConfigType;

/*______________________________________________________________________________
 |                               Functions Prototypes                           |
 |______________________________________________________________________________|
 */

/*
 * Description :
 -> Functional responsible for Initialize the UART device by:
    1. Setup the Frame format like number of data bits, parity bit type and number of stop bits.
    2. Enable the UART.
    3. Setup the UART baud rate.
 */
void UART_init(const UART_ConfigType * Config_Ptr);

/*
 * Description :
 -> Functional responsible for send byte to another UART device.
 */
void UART_sendByte(const uint8 data);

/*
 * Description :
 -> Functional responsible for receive byte from another UART device.
 */
uint8 UART_recieveByte(void);

/*
 * Description :
 -> Send the required string through UART to the other UART device.
 */
void UART_sendString(const uint8 *Str);

/*
 * Description :
 -> Receive the required string until the '#' symbol through UART from the other UART device.
 */
void UART_receiveString(uint8 *Str); // Receive until #

#endif /* UART_H_ */
