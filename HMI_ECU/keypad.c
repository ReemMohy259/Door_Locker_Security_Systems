/******************************************************************************
 * Module: KEYPAD
 *
 * File Name: keypad.c
 *
 * Description: Source file for the Keypad driver
 *
 * Author: Reem Mohy
 *******************************************************************************/
#include "keypad.h"
#include "gpio.h"
#include <util/delay.h>

/*******************************************************************************
 *                      Functions Prototypes(Private)                          *
 *******************************************************************************/

#ifndef STANDARD_KEYPAD

#if(NUM_OF_COLUMNS == 3)
/*
 * Function responsible for mapping the switch number in the keypad to
 * its corresponding functional number in the proteus for 4x3 keypad
 */
static uint8 KEYPAD_4x3_adjustKeyNumber(uint8 a_buttonNum);

#elif(NUM_OF_COLUMNS == 4)
/*
 * Function responsible for mapping the switch number in the keypad to
 * its corresponding functional number in the proteus for 4x4 keypad
 */
static uint8 KEYPAD_4x4_adjustKeyNumber(uint8 a_buttonNumber);

#endif

#endif   /*STANDARD_KEYPAD*/

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*
 * Description:
 * Get the number of the pressed button.
 */
uint8 KEYPAD_getPressedKey(void)
{
	uint8 row,col;

	/*Setup all rows and columns as input pins*/
	GPIO_setupPinDirection(KEYPAD_ROW_PORT_ID,KEYPAD_FIRST_ROW_PIN_ID,PIN_INPUT);
	GPIO_setupPinDirection(KEYPAD_ROW_PORT_ID,KEYPAD_FIRST_ROW_PIN_ID+1,PIN_INPUT);
	GPIO_setupPinDirection(KEYPAD_ROW_PORT_ID,KEYPAD_FIRST_ROW_PIN_ID+2,PIN_INPUT);
	GPIO_setupPinDirection(KEYPAD_ROW_PORT_ID,KEYPAD_FIRST_ROW_PIN_ID+3,PIN_INPUT);

	GPIO_setupPinDirection(KEYPAD_COLUMN_PORT_ID,KEYPAD_FIRST_COLUMN_PIN_ID,PIN_INPUT);
	GPIO_setupPinDirection(KEYPAD_COLUMN_PORT_ID,KEYPAD_FIRST_COLUMN_PIN_ID+1,PIN_INPUT);
	GPIO_setupPinDirection(KEYPAD_COLUMN_PORT_ID,KEYPAD_FIRST_COLUMN_PIN_ID+2,PIN_INPUT);

#if(NUM_OF_COLUMNS == 4)
	GPIO_setupPinDirection(KEYPAD_COLUMN_PORT_ID,KEYPAD_FIRST_COLUMN_PIN_ID+3,PIN_INPUT);

#endif

	while(1)
	{
		_delay_ms(50);
		for(row=0; row<NUM_OF_ROWS; row++)
		{
			/*Each time setup the only one row as output pin*/
			GPIO_setupPinDirection(KEYPAD_ROW_PORT_ID,KEYPAD_FIRST_ROW_PIN_ID+row,PIN_OUTPUT);

			/*Set/Clear the row output pin*/
			GPIO_writePin(KEYPAD_ROW_PORT_ID,KEYPAD_FIRST_ROW_PIN_ID+row,KEYPAD_BUTTON_PRESSED);

			/*Check if the button is pressed in every column*/
			for(col=0; col<NUM_OF_COLUMNS; col++)
			{
				if(GPIO_readPin(KEYPAD_COLUMN_PORT_ID,KEYPAD_FIRST_COLUMN_PIN_ID+col) == KEYPAD_BUTTON_PRESSED)
				{
#ifdef STANDARD_KEYPAD
					return ((row*NUM_OF_COLUMNS)+col+1);   /*return number of the pressed key*/
#elif(NUM_OF_COLUMNS == 3)
					return KEYPAD_4x3_adjustKeyNumber((row*NUM_OF_COLUMNS)+col+1);
#elif(NUM_OF_COLUMNS == 4)
					return KEYPAD_4x4_adjustKeyNumber((row*NUM_OF_COLUMNS)+col+1);
#endif
				}
			}
			/*Return this row to be input pin again*/
			GPIO_setupPinDirection(KEYPAD_ROW_PORT_ID,KEYPAD_FIRST_ROW_PIN_ID+row,PIN_INPUT);
		}
	}
}

#ifndef STANDARD_KEYPAD

#if(NUM_OF_COLUMNS == 3)
/*
 * Function responsible for mapping the switch number in the keypad to
 * its corresponding functional number in the proteus for 4x3 keypad
 */
static uint8 KEYPAD_4x3_adjustKeyNumber(uint8 a_buttonNum)
{
	uint8 pressedButton;

	/*Write the corresponding character to this key number*/
	switch(a_buttonNum)
	{
	case 10:
		pressedButton = '*';  //ASCII code of *
		break;

	case 11:
		pressedButton = 0;
		break;

	case 12:
		pressedButton = '#';  //ASCII code of #
		break;

	default:
		pressedButton = a_buttonNum;
		break;
	}

	return pressedButton;
}

#elif(NUM_OF_COLUMNS == 4)
/*
 * Function responsible for mapping the switch number in the keypad to
 * its corresponding functional number in the proteus for 4x4 keypad
 */
static uint8 KEYPAD_4x4_adjustKeyNumber(uint8 a_buttonNumber)
{
	uint8 keypad_button = 0;
	switch(a_buttonNumber)
	{
		case 1: keypad_button = 7;
				break;
		case 2: keypad_button = 8;
				break;
		case 3: keypad_button = 9;
				break;
		case 4: keypad_button = '%'; // ASCII Code of %
				break;
		case 5: keypad_button = 4;
				break;
		case 6: keypad_button = 5;
				break;
		case 7: keypad_button = 6;
				break;
		case 8: keypad_button = '*'; /* ASCII Code of '*' */
				break;
		case 9: keypad_button = 1;
				break;
		case 10: keypad_button = 2;
				break;
		case 11: keypad_button = 3;
				break;
		case 12: keypad_button = '-'; /* ASCII Code of '-' */
				break;
		case 13: keypad_button = 13;  /* ASCII of Enter */
				break;
		case 14: keypad_button = 0;
				break;
		case 15: keypad_button = '='; /* ASCII Code of '=' */
				break;
		case 16: keypad_button = '+'; /* ASCII Code of '+' */
				break;
		default: keypad_button = a_buttonNumber;
				break;
	}
	return keypad_button;
}
#endif

#endif /* STANDARD_KEYPAD */
