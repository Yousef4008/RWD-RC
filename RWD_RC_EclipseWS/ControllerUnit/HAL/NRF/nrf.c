 /*	____________________________________________________________________________
  |																			    |
  | Module: nRF24L01														    |
  |																			    |
  | File Name: nrf.c														    |
  |																			    |
  | Description: Source file for the nRF24L01 module					        |
  |																			    |
  | Author: Youssif Hossam													    |
  |_____________________________________________________________________________|
*/

#include "nrf.h"
#include "../../MCAL/GPIO/gpio.h"
#include "../../MCAL/SPI/spi.h"
#include <util/delay.h>

/*
 * Description :
 -> Setup the direction of the required pin input/output.
 -> Setup SPI as master and setup the module
 */
void NRF24_init(void){

	GPIO_setupPinDirection(CE_PORT_ID, CE_PIN_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(CSN_PORT_ID, CSN_PIN_ID, PIN_OUTPUT);

	NRF24_chipDisable();
	NRF24_CSN_unselect();

	SPI_init(MASTER_MODE);
	_delay_ms(100);

	NRF24_writeReg(CONFIG , 0x00);		// Will be configured later
	NRF24_writeReg(EN_AA, 0x00);		// No Auto Ack.
	NRF24_writeReg(EN_RXADDR, 0x00);	// Initially disable all pipes
	NRF24_writeReg(SETUP_AW, 0x03);		// 5 bytes Address field width
	NRF24_writeReg(SETUP_RETR, 0xF0);	// Disable Auto re transmission
	//NRF24_writeReg(SETUP_RETR, 0xF0);	// Wait 4000µS before re transmission
	NRF24_writeReg(RF_CH, 0x00);		// Will be setup during TX or RX
	NRF24_writeReg(RF_SETUP, 0x0E);		// 2Mbps -- 0dBm
	//NRF24_writeReg(STATUS, 0x70);		// Clearing RX_DR , RX_DR and RX_DR bits
	//NRF24_writeReg(DYNPD, 0x1F);		// Enabling Dynamic pipes size
	//NRF24_sendCmd(ACTIVATE);			// Activating NRF24L01
	//NRF24_sendCmd(0x73);				// Activation command must be followed by 0x73 command



	NRF24_chipEnable();
}

/*
 * Description :
 -> this function is for chip select
 */
static void NRF24_CSN_select(void){
	GPIO_writePin(CSN_PORT_ID, CSN_PIN_ID, LOGIC_LOW);
}

/*
 * Description :
 -> this function is for chip unselect
 */
static void NRF24_CSN_unselect(void){
	GPIO_writePin(CSN_PORT_ID, CSN_PIN_ID, LOGIC_HIGH);
}

/*
 * Description :
 -> module chip enable
 */
static void NRF24_chipEnable(void){
	GPIO_writePin(CE_PORT_ID, CE_PIN_ID, LOGIC_HIGH);
}

/*
 * Description :
 -> module chip disable
 */
static void NRF24_chipDisable(void){
	GPIO_writePin(CE_PORT_ID, CE_PIN_ID, LOGIC_LOW);
}

/*
 * Description :
 -> write a data on specific register on the module
 */
static void NRF24_writeReg(uint8 Reg, uint8 Data){

	uint8 buf[2];

	buf[0] = Reg|1<<5;
	buf[1] = Data;

	NRF24_CSN_select();

	SPI_sendReceiveByte(buf[0]);
	SPI_sendReceiveByte(buf[1]);

	NRF24_CSN_unselect();
}

/*
 * Description :
 -> write multiple of data on a specific register on the module
 */
static void NRF24_writeRegMulti(uint8 Reg, uint8 * Data , uint8 size){

	NRF24_CSN_select();

	SPI_sendReceiveByte(Reg | (1<<5) );

	for(int i = 0 ; i < size ; i++){
		SPI_sendReceiveByte(Data[i]);
	}

	NRF24_CSN_unselect();
}

/*
 * Description :
 -> read the value of data on specific register on the module
 */
static uint8 NRF24_readReg(uint8 Reg){

	uint8 data = 0;

	NRF24_CSN_select();

	SPI_sendReceiveByte(Reg);

	data = SPI_sendReceiveByte(0xFF);

	NRF24_CSN_unselect();

	return data;
}

/*
 * Description :
 -> sending a command to the module
 */
static void NRF24_sendCmd(uint8 cmd){

	NRF24_CSN_select();

	SPI_sendReceiveByte(cmd);

	NRF24_CSN_unselect();
}

/*
 * Description :
 -> sending the channel on specific address pipe
 */
void NRF24_txMode(uint8 * PipeAddress , uint8 channel){

	NRF24_chipDisable();

	NRF24_writeReg(RF_CH, channel);		// Selecting the channel
	NRF24_writeRegMulti(TX_ADDR, PipeAddress, 5);
	NRF24_writeReg(CONFIG, NRF24_readReg(CONFIG)|(1<<1));	// Powering up the device & TX selection

	NRF24_chipEnable();
}

/*
 * Description :
 -> transmitting the data over nRF module
 */
uint8 NRF_transmit(uint8 * Data ){
	uint8 FIFO_status = 0 ;
	NRF24_CSN_select();

	SPI_sendReceiveByte(W_TX_PAYLOAD);			// Command to send it before payload

		SPI_sendReceiveByte(Data[0]);				// Sending the payload itself
		SPI_sendReceiveByte(Data[1]);				// Sending the payload itself


	NRF24_CSN_unselect();

	_delay_ms(2);

	FIFO_status = NRF24_readReg(FIFO_STATUS);

	if ((FIFO_status&(1<<4)) && (!(FIFO_status&(1<<3))))	// Checking if the data was transmitted successfully
	{

		NRF24_sendCmd(FLUSH_TX);

		return 1;
	}

	return 0;
}

/*
 * Description :
 -> receiving the channel on specific address pipe
 */
void NRF24_rxMode(uint8 * PipeAddress , uint8 channel ){

	NRF24_chipDisable();

	NRF24_writeReg(RF_CH, channel);										// Selecting the channel
	NRF24_writeReg(EN_RXADDR, NRF24_readReg(EN_RXADDR)|(1<<1));			// Enable data pipe 1
	NRF24_writeRegMulti(RX_ADDR_P1, PipeAddress, 5);
	NRF24_writeReg(RX_PW_P1, 2);									// Selecting size of data pipe
	NRF24_writeReg(CONFIG, NRF24_readReg(CONFIG)| (0x03) );				// Powering up the device & RX selection

	NRF24_chipEnable();
}

/*
 * Description :
 -> checking if the data is available or not
 */
uint8 NRF24_isDataAvailable(uint8 pipeNum){

	uint8 statusReg = 0;

	statusReg = NRF24_readReg(STATUS);
	if((statusReg&(1<<6))&&(statusReg&(pipeNum<<1))){	// if the data on pipe number has arrived or not
		NRF24_writeReg(STATUS, (1<<6));		// Write 1 to clear RX_DR bit
		return 1;
	}
	return 0;
}

/*
 * Description :
 -> receiving the data over nRF module
 */
void NRF24_receive(uint8 *Data){
	NRF24_CSN_select();

	SPI_sendReceiveByte(R_RX_PAYLOAD);				// Command to send it before payload

	Data[0] = SPI_sendReceiveByte(0xFF);				// Receiving the payload itself
	Data[1] = SPI_sendReceiveByte(0xFF);				// Receiving the payload itself

	NRF24_CSN_unselect();

	_delay_ms(2);

	NRF24_sendCmd(FLUSH_RX);
}
