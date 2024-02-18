/*******************************************************************************
 * Module: GPIO
 *
 * File Name: gpio.h
 *
 * Description: Header file for the AVR GPIO driver
 *
 * Author: Reem Mohy
 *******************************************************************************/

#ifndef GPIO_H_
#define GPIO_H_

#include "std_types.h"

/*******************************************************************************
 *                              Definitions
 *******************************************************************************/
#define NUM_OF_PORTS         4
#define NUM_OF_PINS_PER_PORT 8

#define PORTA_ID             0
#define PORTB_ID             1
#define PORTC_ID             2
#define PORTD_ID             3

#define PIN0_ID              0
#define PIN1_ID              1
#define PIN2_ID              2
#define PIN3_ID              3
#define PIN4_ID              4
#define PIN5_ID              5
#define PIN6_ID              6
#define PIN7_ID              7

/*******************************************************************************
 *                              Data Types Declaration
 *******************************************************************************/
typedef enum
{
	PIN_INPUT,PIN_OUTPUT
}GPIO_PinDirectionType;

typedef enum
{
	PORT_INPUT,PORT_OUTPUT=0XFF
}GPIO_PortDirectionType;

/*******************************************************************************
 *                              Functions Prototype
 *******************************************************************************/

/*
 * Description:
 * Setup the direction of the required pin input/output.
 * If input port number or pin number are not correct, the function will not handle the request.
 */
void GPIO_setupPinDirection(uint8 a_portNum,uint8 a_pinNum,GPIO_PinDirectionType a_direction);

/*
 * Description:
 * Write the value logic high or logic low on the required pin.
 * If input port number or pin number are not correct, the function will not handle the request.
 * If the pin is input , this function enable/disable the internal pull-up resistor.
 */
void GPIO_writePin(uint8 a_portNum,uint8 a_pinNum,uint8 a_value);

/*
 * Description:
 * Read and return the value for the required pin , it should be logic low/logic high.
 * If the input port number or pin number are not correct, The function will return Logic low.
 */
uint8 GPIO_readPin(uint8 a_portNum,uint8 a_pinNum);

/*
 * Description:
 * Setup the direction of the required port all pins input/output.
 * If the direction value is PORT_INPUT all pins in this port should be input pins.
 * If the direction value is PORT_OUTPUT all pins in this port should be output pins.
 * If the input port number is not correct, The function will not handle the request.
*/
void GPIO_setupPortDirection(uint8 a_portNum,GPIO_PortDirectionType a_direction);

/*
 * Description:
 * Write the value on the required port.
 * If any pin in the port is output pin the value will be written.
 * If any pin in the port is input pin this will activate/deactivate the internal pull-up resistor.
 * If the input port number is not correct, The function will not handle the request.
*/
void GPIO_writePort(uint8 a_portNum, uint8 a_value);

/*
 * Description:
 * Read and return the value of the required port.
 * If the input port number is not correct, The function will return ZERO value.
*/
uint8 GPIO_readPort(uint8 a_portNum);

#endif /* GPIO_H_ */
