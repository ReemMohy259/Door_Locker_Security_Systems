/******************************************************************************
 * Module: UART
 *
 * File Name: uart.c
 *
 * Description: Source file for the UART AVR driver
 *
 * Author: Reem Mohy
 *******************************************************************************/

#include "uart.h"
#include "avr/io.h"  /*To use the UART Registers */
#include "common_macros.h" /*To use the macros like SET_BIT */

/*******************************************************************************
                        Functions Definitions
 *******************************************************************************/

/*
 * Description:
 * Function to initialize the UART device
 * 1.Setup the frame format (number of data bits, parity bit, number of stop bit).
 * 2.Enable the UART.
 * 3.Setup the baud rate
 */
void UART_init(const Uart_ConfigType* Config_Ptr)
{
	uint16 ubrrValue = 0;  /*To store the value of UART baud rate register*/

	/*U2X = 1 for double transmission speed mode*/
	UCSRA = (1<<U2X);

    /******************************** UCSRB ************************************
	 * RXCIE = 0 disable RX complete interrupt enable.
	 * TXCIE = 0 disable TX complete interrupt enable.
	 * UDRIE = 0 disable data register empty interrupt enable.
	 * RXEN  = 1 receiver enable.
	 * TXEN  = 1 transmitter enable.
	 * Setup the UCSZ2 bit for data bit mode.
	 * RXB8 & TXB8 not used for 8-bit data mode.
	 ***************************************************************************/
	UCSRB = (1<<RXEN) | (1<< TXEN);

	UCSRB = (UCSRB & 0xFB) | (Config_Ptr->bit_data & 0x04);

	/******************************** UCSRC ************************************
	 * URSEL = 1  must be one when writing the UCSRC.
	 * UMSEL = 0  for asynchronous operation.
	 * Setup the UCSZ1:0 bits for data bit mode.
	 * Setup the UPM1:0 bits to chose the parity bit.
	 * Setup the USB bit to chose the number of stop bits.
	 * UCPOL = 0  used with the Synchronous operation only
	 ***************************************************************************/
	UCSRC = (1<<URSEL) ;

	UCSRC = (UCSRC & 0xF9) | ((Config_Ptr->bit_data & 0x03)<<UCSZ0);

	UCSRC = (UCSRC & 0xCF) | ((Config_Ptr->parity & 0x03)<<UPM0);

	UCSRC = (UCSRC & 0xF7) | ((Config_Ptr->stop_bit & 0x01)<<USBS);



	/*Calculate the UBRR register value*/
	ubrrValue = (uint16)(((F_CPU / (Config_Ptr->baud_rate * 8UL))) - 1);

	/*First 8 bits from the BAUD_PRESCALE inside UBRRL and last 4 bits in UBRRH*/
	UBRRL = ubrrValue;
	UBRRH = ubrrValue>>8;
}

/*
 * Description:
 * Send byte to another UART device.
 */
void UART_sendByte(const uint8 a_data)
{
	/*UDRE flag is set when the Tx buffer (UDR) is empty and ready for transmitting a new byte*/
	while(BIT_IS_CLEAR(UCSRA,UDRE)); /*Wait until this flag is set to avoid Data Overrun Error*/

	UDR = a_data;  /*Put the data in UDR register and it clear the UDRE flag automatically*/
}

/*
 * Description:
 * Receive byte from another UART device.
 */
uint8 UART_receiveByte(void)
{
	/* RXC flag is set when the UART receive data completely*/
	while(BIT_IS_CLEAR(UCSRA,RXC)); /*Wait until this flag is set*/

	return UDR;  /*Read the received data and the flag will be cleared automatically*/
}

/*
 * Description:
 * Send string to another UART device.
 */
void UART_sendString(const uint8* Str_Ptr)
{
	uint8 i = 0;

	while(Str_Ptr[i] != '\0') /*Send the string until the \0 is reached*/
	{
		UART_sendByte(Str_Ptr[i]);
		i++;
	}
}

/*
 * Description:
 * Receive string (until the special character '#') from another UART device.
 */
void UART_receiveString(uint8* Str_Ptr)
{
	uint8 i = 0;

	Str_Ptr[i] = UART_receiveByte();  /*Receive the first byte*/

	while(Str_Ptr[i] != '#')  /*Receive the string until the # is reached*/
	{
		i++;
		Str_Ptr[i] = UART_receiveByte();
	}

	Str_Ptr[i]='\0';  /*After receiving the string replace # with \0*/
}
