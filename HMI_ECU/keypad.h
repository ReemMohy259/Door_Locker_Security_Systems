/******************************************************************************
 * Module: KEYPAD
 *
 * File Name: keypad.h
 *
 * Description: Header file for the Keypad driver
 *
 * Author: Reem Mohy
 *******************************************************************************/


#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "std_types.h"

/*******************************************************************************
                                 Definitions
 *******************************************************************************/

/*Define the number of keypad rows and columns*/
#define NUM_OF_ROWS                    4
#define NUM_OF_COLUMNS                 4

/*Define the keypad port and pins*/
#define KEYPAD_ROW_PORT_ID             PORTA_ID
#define KEYPAD_FIRST_ROW_PIN_ID        PIN0_ID

#define KEYPAD_COLUMN_PORT_ID          PORTA_ID
#define KEYPAD_FIRST_COLUMN_PIN_ID     PIN4_ID

/*Define the logic of the button connection (Pull up/Pull down)*/
#define KEYPAD_BUTTON_PRESSED          LOGIC_LOW
#define KEYPAD_BUTTON_NOT_PRESSED      LOGIC_HIGH

/*******************************************************************************
                       Functions Prototypes (Public)
 *******************************************************************************/

/*
 * Description:
 * Get the number of the pressed button.
 */
uint8 KEYPAD_getPressedKey(void);

#endif /* KEYPAD_H_ */
