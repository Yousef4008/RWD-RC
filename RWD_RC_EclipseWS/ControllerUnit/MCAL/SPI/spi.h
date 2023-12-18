 /*	____________________________________________________________________________
  |																			    |
  | Module: SPI																    |
  |																			    |
  | File Name: spi.h														    |
  |																			    |
  | Description: Header file for the SPI driver							        |
  |																			    |
  | Author: Youssif Hossam													    |
  |_____________________________________________________________________________|
*/

#ifndef MCAL_SPI_SPI_H_
#define MCAL_SPI_SPI_H_

#include "../../LIB/std_types.h"

#define SPI_DEFAULT_DATA_VALUE 0xFF
#define MASTER_MODE		LOGIC_HIGH
#define SLEVE_MODE		LOGIC_LOW


/*
 * Description :
 * Initialize the SPI device as Master.
 */
void SPI_init(uint8 mode);


uint8 SPI_sendReceiveByte(uint8 data);

/*
 * Description :
 * Send the required string through SPI to the other SPI device.
 */
void SPI_sendString(const uint8 *str);

/*
 * Description :
 * Receive the required string until the '#' symbol through SPI from the other SPI device.
 */
void SPI_receiveString(uint8 *str);

#endif /* MCAL_SPI_SPI_H_ */

