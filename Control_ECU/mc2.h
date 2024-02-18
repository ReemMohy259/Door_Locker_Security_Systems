/******************************************************************************
 * Module: Control_ECU
 *
 * File Name: mc2.h
 *
 * Description: Header file for the Control_ECU
 *
 * Author: Reem Mohy
 *******************************************************************************/

#ifndef MC2_H_
#define MC2_H_

#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "uart.h"
#include "twi.h"
#include "timer1.h"
#include "dc_motor.h"
#include "buzzer.h"
#include "external_eeprom.h"

/*******************************************************************************
                                  Definitions
 *******************************************************************************/
#define READY               0x01
#define CORRECT_PASS        0x02
#define INCORRECT_PASS      0x03
#define OPEN_DOOR           0x04
#define CHANGE_PASS         0x05
#define CONTINUE            0x06
#define ERROR_BUZZER        0x07

#define ARR_SIZE             5

/*******************************************************************************
                                Functions Prototype
 *******************************************************************************/

/*
 * Description:
 * Function that takes two passwords.
 * Return byte that describe if password are correct or not.
 */
uint8 check_createdPassword(uint8 *a_str1,uint8 *a_str2);

/*
 * Description:
 * Save the password in EEPROM.
 */
void EEPROM_write_Password(uint8 *a_str);

/*
 * Description:
 * Reads the password saved in EEPROM and returns it in an string.
 */
void EEPROM_read_Password(uint8 *a_str);


#endif /* MC2_H_ */
