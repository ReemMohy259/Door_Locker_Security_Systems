/*******************************************************************************
 * Module: UART
 *
 * File Name: uart.h
 *
 * Description: Header file for the UART AVR driver
 *
 * Author: Reem Mohy
 *******************************************************************************/

#ifndef UART_H_
#define UART_H_

#include "std_types.h"

/*******************************************************************************
                         Types Definition
 *******************************************************************************/

typedef uint32    Uart_BaudRate;

typedef enum{
	_5_bit,_6_bit,_7_bit,_8_bit,_9_bit = 7,
}Uart_BitData;

typedef enum{
	DISABLE,RESERVED,EVEN_PARITY,ODD_PARITY
}Uart_Parity;

typedef enum{
	ONE_STOP_BIT,TWO_STOP_BIT
}Uart_StopBit;

typedef struct{

	Uart_BitData  bit_data;
	Uart_Parity   parity;
	Uart_StopBit  stop_bit;
	Uart_BaudRate baud_rate;

}Uart_ConfigType;

/*******************************************************************************
                         Functions Prototypes
 *******************************************************************************/

/*
 * Description:
 * Function to initialize the UART device
 * 1.Setup the frame format (number of data bits, parity bit, number of stop bit).
 * 2.Enable the UART.
 * 3.Setup the baud rate
 */
void UART_init(const Uart_ConfigType* Config_Ptr);

/*
 * Description:
 * Send byte to another UART device.
 */
void UART_sendByte(const uint8 a_data);

/*
 * Description:
 * Receive byte from another UART device.
 */
uint8 UART_receiveByte(void);

/*
 * Description:
 * Send string to another UART device.
 */
void UART_sendString(const uint8* Str_Ptr);

/*
 * Description:
 * Receive string (until the special character '#') from another UART device.
 */
void UART_receiveString(uint8* Str_Ptr);

#endif /* UART_H_ */
