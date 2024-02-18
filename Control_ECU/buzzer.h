/******************************************************************************
 * Module: Buzzer
 *
 * File Name: buzzer.h
 *
 * Description: Header file for the AVR buzzer driver
 *
 * Author: Reem Mohy
 *******************************************************************************/

#ifndef BUZZER_H_
#define BUZZER_H_

/*******************************************************************************
                        Definitions
 *******************************************************************************/

#define BUZZER_PORT_ID               PORTD_ID
#define BUZZER_PIN_ID                PIN7_ID

/*******************************************************************************
                        Function Prototype
 *******************************************************************************/

/*
 * Description:
 * Setup the direction for the buzzer pin as output pin.
 * Initially the buzzer is turned off.
 */
void BUZZER_init(void);

/*
 * Description:
 * Enable the buzzer.
 */
void BUZZER_on(void);

/*
 * Description:
 * Disable the buzzer.
 */
void BUZZER_off(void);

#endif /* BUZZER_H_ */
