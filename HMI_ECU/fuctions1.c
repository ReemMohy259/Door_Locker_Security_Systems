/******************************************************************************
 * Module: HMI_ECU
 *
 * File Name: functions.h
 *
 * Description: Source file for the HMI_ECU
 *
 * Author: Reem Mohy
 *******************************************************************************/

#include "mc1.h"

/*******************************************************************************
                        Functions Definitions
 *******************************************************************************/


/*
 * Description:
 * Function to get the password from user by keypad.
 */
void get_password(uint8 *a_str)
{
	uint8 i = 0;

	for(i=0;i<ARR_SIZE-1;i++)  /*Password consists of 5 characters*/
	{
		a_str[i] = KEYPAD_getPressedKey();
		LCD_displayCharacter('*');
		_delay_ms(500);
	}
	while(KEYPAD_getPressedKey() != ENTER_BUTTON);  /*Wait until enter button is pressed*/

	_delay_ms(300);

	a_str[ARR_SIZE-1] = '#';   /*In ordered to received correct string by UART*/
	a_str[ARR_SIZE] = '\0';   /*Put Null inside the array to become a string*/
}

/*
 * Description:
 * Function that takes two passwords.
 * Send them by UART to control_ECU to check if they are the same.
 * Return byte that describe if password are correct or not.
 */
uint8 check_createdPassword(uint8 *a_str1,uint8 *a_str2)
{
	UART_sendByte(READY);
	UART_sendString(a_str1);
	UART_sendString(a_str2);

	while(UART_receiveByte() != READY);   /*Wait until the control_ECU check the two passwords*/

	return UART_receiveByte();     /*Read the byte received from control_ECU*/
}

/*
 * Description:
 * Function that takes the passwords typed in main operation step.
 * It takes our current step and the number of trials we have.
 * Send it by UART to control_ECU to check if it is correct.
 * Return byte that describe if password are correct or not.
 */
uint8 check_mainOptionPassword(uint8 *a_str,uint8 trials,uint8 step)
{
	/*Ask the user to write the password*/
	LCD_clearScreen();
	LCD_displayStringRowColumn(0,0,"PLZ Enter Pass:");
	LCD_displayStringRowColumn(1,0,"[ ]:");
	LCD_moveCursor(1,1);
	LCD_intgerToString(trials+1);

	LCD_moveCursor(1,4);  /*Set the display screen before calling the function*/
	get_password(a_str);  /*Get the password*/

	/*Send the password to control_ECU to compare it with one saved in EEPROM*/
	UART_sendByte(READY);

	/*Switch on the current step in the operation*/
	switch (step)
	{
	case OPEN_DOOR:
		UART_sendByte(OPEN_DOOR);
		break;

	case CHANGE_PASS:
		UART_sendByte(CHANGE_PASS);
		break;
	}

	UART_sendString(a_str);    /*Send the password to the control_ECU*/

	while(UART_receiveByte() != READY);   /*Wait until the control_ECU check the password*/

	return UART_receiveByte();   /*Read the byte received from control_ECU*/
}
