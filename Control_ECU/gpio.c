/*******************************************************************************
 * Module: GPIO
 *
 * File Name: gpio.c
 *
 * Description: Source file for the AVR GPIO driver
 *
 * Author: Reem Mohy
 *******************************************************************************/

#include <avr/io.h>  /*To use the IO port AVR registers */
#include "gpio.h"
#include "common_macros.h"  /*To use common macros in some operations*/


/*
 * Description:
 * Setup the direction of the required pin input/output.
 * If input port number or pin number are not correct, the function will not handle the request.
 */
void GPIO_setupPinDirection(uint8 a_portNum,uint8 a_pinNum,GPIO_PinDirectionType a_direction)
{
	/*
	 * Check if the input port number is greater than NUM_OF_PINS_PER_PORT value.
	 * Or if the input pin number is greater than NUM_OF_PINS_PER_PORT value.
	 * In this case the input is not valid port/pin number
	 */
	if((a_portNum >= NUM_OF_PORTS) || (a_pinNum >= NUM_OF_PINS_PER_PORT))
	{
		/*Do Nothing*/
	}
	else
	{
		/*Setup the pin direction as required*/
		switch(a_portNum)
		{
		case PORTA_ID:
			if(a_direction == PIN_OUTPUT)
			{
				SET_BIT(DDRA,a_pinNum);
			}
			else
			{
				CLEAR_BIT(DDRA,a_pinNum);
			}
			break;

		case PORTB_ID:
			if(a_direction == PIN_OUTPUT)
			{
				SET_BIT(DDRB,a_pinNum);
			}
			else
			{
				CLEAR_BIT(DDRB,a_pinNum);
			}
			break;

		case PORTC_ID:
			if(a_direction == PIN_OUTPUT)
			{
				SET_BIT(DDRC,a_pinNum);
			}
			else
			{
				CLEAR_BIT(DDRC,a_pinNum);
			}
			break;

		case PORTD_ID:
			if(a_direction == PIN_OUTPUT)
			{
				SET_BIT(DDRD,a_pinNum);
			}
			else
			{
				CLEAR_BIT(DDRD,a_pinNum);
			}
			break;
		}
	}
}

/*
 * Description:
 * Write the value logic high or logic low on the required pin.
 * If input port number or pin number are not correct, the function will not handle the request.
 * If the pin is input , this function enable/disable the internal pull-up resistor.
 */
void GPIO_writePin(uint8 a_portNum,uint8 a_pinNum,uint8 a_value)
{
	if((a_portNum >= NUM_OF_PORTS) || (a_pinNum >= NUM_OF_PINS_PER_PORT))
	{
		/*Do Nothing*/
	}
	else
	{
		/*Write the pin value as required*/
		switch(a_portNum)
		{
		case PORTA_ID:
			if(a_value == LOGIC_HIGH)
			{
				SET_BIT(PORTA,a_pinNum);
			}
			else
			{
				CLEAR_BIT(PORTA,a_pinNum);
			}
			break;

		case PORTB_ID:
			if(a_value == LOGIC_HIGH)
			{
				SET_BIT(PORTB,a_pinNum);
			}
			else
			{
				CLEAR_BIT(PORTB,a_pinNum);
			}
			break;

		case PORTC_ID:
			if(a_value == LOGIC_HIGH)
			{
				SET_BIT(PORTC,a_pinNum);
			}
			else
			{
				CLEAR_BIT(PORTC,a_pinNum);
			}
			break;

		case PORTD_ID:
			if(a_value == LOGIC_HIGH)
			{
				SET_BIT(PORTD,a_pinNum);
			}
			else
			{
				CLEAR_BIT(PORTD,a_pinNum);
			}
			break;
		}
	}
}

/*
 * Description:
 * Read and return the value for the required pin , it should be logic low/logic high.
 * If the input port number or pin number are not correct, The function will return Logic low.
 */
uint8 GPIO_readPin(uint8 a_portNum,uint8 a_pinNum)
{
	uint8 pinValue = LOGIC_LOW;

	/*
	 * Check if the input port number is greater than NUM_OF_PINS_PER_PORT value.
	 * Or if the input pin number is greater than NUM_OF_PINS_PER_PORT value.
	 * In this case the input is not valid port/pin number and return logic low.
	 */
	if((a_portNum >= NUM_OF_PORTS) || (a_pinNum >= NUM_OF_PINS_PER_PORT))
	{
		/*Do Nothing*/
	}
	else
	{
		switch(a_portNum)
		{
		case PORTA_ID:
			pinValue = GET_BIT(PINA,a_pinNum);
			break;

		case PORTB_ID:
			pinValue = GET_BIT(PINB,a_pinNum);
			break;

		case PORTC_ID:
			pinValue = GET_BIT(PINC,a_pinNum);
			break;

		case PORTD_ID:
			pinValue = GET_BIT(PIND,a_pinNum);
			break;
		}
	}

	return pinValue;
}

/*
 * Description:
 * Setup the direction of the required port all pins input/output.
 * If the direction value is PORT_INPUT all pins in this port should be input pins.
 * If the direction value is PORT_OUTPUT all pins in this port should be output pins.
 * If the input port number is not correct, The function will not handle the request.
 */
void GPIO_setupPortDirection(uint8 a_portNum,GPIO_PortDirectionType a_direction)
{
	/*
	 * Check if the input number is greater than NUM_OF_PORTS value.
	 * In this case the input is not valid and function will not handle the request.
	 */
	if(a_portNum >= NUM_OF_PORTS)
	{
		/*Do Nothing*/
	}
	else
	{
		/*Setup the port direction as required*/
		switch(a_portNum)
		{
		case PORTA_ID:
			DDRA = a_direction;
			break;

		case PORTB_ID:
			DDRB = a_direction;
			break;

		case PORTC_ID:
			DDRC = a_direction;
			break;

		case PORTD_ID:
			DDRD = a_direction;
			break;
		}
	}
}

/*
 * Description:
 * Write the value on the required port.
 * If any pin in the port is output pin the value will be written.
 * If any pin in the port is input pin this will activate/deactivate the internal pull-up resistor.
 * If the input port number is not correct, The function will not handle the request.
 */
void GPIO_writePort(uint8 a_portNum, uint8 a_value)
{
	/*
	 * Check if the input number is greater than NUM_OF_PORTS value.
	 * In this case the input is not valid and function will not handle the request.
	 */
	if(a_portNum >= NUM_OF_PORTS)
	{
		/*Do Nothing*/
	}
	else
	{
		/*Write the port value as required*/
		switch(a_portNum)
		{
		case PORTA_ID:
			PORTA = a_value;
			break;

		case PORTB_ID:
			PORTB = a_value;
			break;

		case PORTC_ID:
			PORTC = a_value;
			break;

		case PORTD_ID:
			PORTD = a_value;
			break;
		}
	}
}

/*
 * Description:
 * Read and return the value of the required port.
 * If the input port number is not correct, The function will return ZERO value.
 */
uint8 GPIO_readPort(uint8 a_portNum)
{
	uint8 pinValue = LOGIC_LOW;

	/*
	 * Check if the input number is greater than NUM_OF_PORTS value.
	 * In this case the input is not valid port number and return zero.
	 */
	if(a_portNum >= NUM_OF_PORTS)
	{
		/* Do Nothing */
	}
	else
	{
		/*Read the port value as required*/
		switch(a_portNum)
		{
		case PORTA_ID:
			pinValue = PINA;
			break;

		case PORTB_ID:
			pinValue = PINB;
			break;

		case PORTC_ID:
			pinValue = PINC;
			break;

		case PORTD_ID:
			pinValue = PIND;
			break;
		}
	}

	return pinValue;
}
