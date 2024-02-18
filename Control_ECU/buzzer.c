/******************************************************************************
 * Module: Buzzer
 *
 * File Name: buzzer.c
 *
 * Description: Source file for the AVR buzzer driver
 *
 * Author: Reem Mohy
 *******************************************************************************/

#include "buzzer.h"
#include "gpio.h"

/*******************************************************************************
                        Function Definition
 *******************************************************************************/

/*
 * Description:
 * Setup the direction for the buzzer pin as output pin.
 * Initially the buzzer is turned off.
 */
void BUZZER_init(void)
{
	/*Configure the buzzer pin as output pin*/
	GPIO_setupPinDirection(BUZZER_PORT_ID,BUZZER_PIN_ID,PIN_OUTPUT);
	/*Turn off the buzzer*/
	GPIO_writePin(BUZZER_PORT_ID,BUZZER_PIN_ID,LOGIC_LOW);
}

/*
 * Description:
 * Enable the buzzer.
 */
void BUZZER_on(void)
{
	/*Turn on the buzzer*/
	GPIO_writePin(BUZZER_PORT_ID,BUZZER_PIN_ID,LOGIC_HIGH);
}

/*
 * Description:
 * Disable the buzzer.
 */
void BUZZER_off(void)
{
	/*Turn off the buzzer*/
	GPIO_writePin(BUZZER_PORT_ID,BUZZER_PIN_ID,LOGIC_LOW);

}
