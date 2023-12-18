 /*	____________________________________________________________________________
  |																			    |
  | Module: nRF24L01														    |
  |																			    |
  | File Name: nrf.h														    |
  |																			    |
  | Description: Header file for the nRF24L01 module					        |
  |																			    |
  | Author: Youssif Hossam													    |
  |_____________________________________________________________________________|
*/

#ifndef HAL_NRF_NRF_H_
#define HAL_NRF_NRF_H_

#include "../../LIB/std_types.h"

/*______________________________________________________________________________
 |                               		Definitions                        		|
 |______________________________________________________________________________|
 */

#define CE_PORT_ID		PORTD_ID
#define CE_PIN_ID		PIN0_ID

#define CSN_PORT_ID		PORTB_ID
#define CSN_PIN_ID		PIN4_ID

#define CONFIG      0x00
#define EN_AA       0x01
#define EN_RXADDR   0x02
#define SETUP_AW    0x03
#define SETUP_RETR  0x04
#define RF_CH       0x05
#define RF_SETUP    0x06
#define STATUS      0x07
#define OBSERVE_TX  0x08
#define CD          0x09
#define RX_ADDR_P0  0x0A
#define RX_ADDR_P1  0x0B
#define RX_ADDR_P2  0x0C
#define RX_ADDR_P3  0x0D
#define RX_ADDR_P4  0x0E
#define RX_ADDR_P5  0x0F
#define TX_ADDR     0x10
#define RX_PW_P0    0x11
#define RX_PW_P1    0x12
#define RX_PW_P2    0x13
#define RX_PW_P3    0x14
#define RX_PW_P4    0x15
#define RX_PW_P5    0x16
#define FIFO_STATUS 0x17
#define DYNPD	    0x1C
#define FEATURE	    0x1D

/* Instruction Mnemonics */
#define R_REGISTER    0x00
#define W_REGISTER    0x20
#define REGISTER_MASK 0x1F
#define ACTIVATE      0x50
#define R_RX_PL_WID   0x60
#define R_RX_PAYLOAD  0x61
#define W_TX_PAYLOAD  0xA0
#define W_ACK_PAYLOAD 0xA8
#define FLUSH_TX      0xE1
#define FLUSH_RX      0xE2
#define REUSE_TX_PL   0xE3
#define NOP           0xFF

/*______________________________________________________________________________
 |                              Functions Prototypes            	            |
 |______________________________________________________________________________|
 */

/*
 * Description :
 -> Setup the direction of the required pin input/output.
 -> Setup SPI as master and setup the module
 */
void NRF24_init(void);

/*
 * Description :
 -> write a data on specific register on the module
 */
static void NRF24_writeReg(uint8 Reg, uint8 Data);

/*
 * Description :
 -> write multiple of data on a specific register on the module
 */
static void NRF24_writeRegMulti(uint8 Reg, uint8 * Data , uint8 size);

/*
 * Description :
 -> read the value of data on specific register on the module
 */
static uint8 NRF24_readReg(uint8 Reg);

/*
 * Description :
 -> sending a command to the module
 */
static void NRF24_sendCmd(uint8 cmd);

/*
 * Description :
 -> this function is for chip select
 */
static void NRF24_CSN_select(void);

/*
 * Description :
 -> this function is for chip unselect
 */
static void NRF24_CSN_unselect(void);

/*
 * Description :
 -> module chip enable
 */
static void NRF24_chipEnable(void);

/*
 * Description :
 -> module chip disable
 */
static void NRF24_chipDisable(void);

/*
 * Description :
 -> sending the channel on specific address pipe
 */
void NRF24_txMode(uint8 * PipeAddress , uint8 channel);

/*
 * Description :
 -> transmitting the data over nRF module
 */
uint8 NRF_transmit(uint8 * Data );

/*
 * Description :
 -> receiving the channel on specific address pipe
 */
void NRF24_rxMode(uint8 * PipeAddress , uint8 channel );

/*
 * Description :
 -> checking if the data is available or not
 */
uint8 NRF24_isDataAvailable(uint8 pipeNum);

/*
 * Description :
 -> receiving the data over nRF module
 */
void NRF24_receive(uint8 *Data );
#endif /* HAL_NRF_NRF_H_ */
