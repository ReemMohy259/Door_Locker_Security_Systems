/******************************************************************************
 * Module: HMI_ECU
 *
 * File Name: mc1.h
 *
 * Description: Header file for the HMI_ECU
 *
 * Author: Reem Mohy
 *******************************************************************************/


#ifndef MC1_H_
#define MC1_H_

#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "keypad.h"
#include "lcd.h"
#include "uart.h"
#include "timer1.h"

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

#define ENTER_BUTTON        '='

#define ARR_SIZE             6

/*******************************************************************************
                                Functions Prototype
 *******************************************************************************/

/*
 * Description:
 * Function to get the password from user by keypad.
 */
void get_password(uint8 *a_str);

/*
 * Description:
 * Function that takes two passwords.
 * Send them by UART to control_ECU to check if they are the same.
 * Return byte that describe if password are correct or not.
 */
uint8 check_createdPassword(uint8 *a_str1,uint8 *a_str2);

/*
 * Description:
 * Function that takes the passwords typed in main operation step.
 * It takes our current step and the number of trials we have.
 * Send it by UART to control_ECU to check if it is correct.
 * Return byte that describe if password are correct or not.
 */
uint8 check_mainOptionPassword(uint8 *a_str,uint8 trials,uint8 step);

#endif /* MC1_H_ */
