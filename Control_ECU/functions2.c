/******************************************************************************
 * Module: Control_ECU
 *
 * File Name: functions.c
 *
 * Description: Source file for the Control_ECU
 *
 * Author: Reem Mohy
 *******************************************************************************/

#include "mc2.h"

/*
 * Description:
 * Function that takes two passwords.
 * Return byte that describe if password are correct or not.
 */
uint8 check_createdPassword(uint8 *a_str1,uint8 *a_str2)
{
	uint8 i =0;
	for(i=0;i<ARR_SIZE;i++)
	{
		if(a_str1[i] != a_str2[i])
		{
			return INCORRECT_PASS;
		}
	}
	return CORRECT_PASS;

}

/*
 * Description:
 * Save the password in EEPROM.
 */
void EEPROM_write_Password(uint8 *a_str)
{
	uint8 i;
	for(i=0;i<ARR_SIZE;i++)
	{
		EEPROM_writeByte(0x0311+i,a_str[i]);
		_delay_ms(100);
	}
}

/*
 * Description:
 * Reads the password saved in EEPROM and returns it in an string.
 */
void EEPROM_read_Password(uint8 *a_str)
{
	uint8 EEPROM_Read_Byte;
	uint8 i;
	for(i=0;i<ARR_SIZE;i++)
	{
		EEPROM_readByte(0x0311+i,&EEPROM_Read_Byte);
		a_str[i]= EEPROM_Read_Byte;
		_delay_ms(100);
	}
}
