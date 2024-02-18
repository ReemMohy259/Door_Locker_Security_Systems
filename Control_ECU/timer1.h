/*************************************************************************************************
 * Module: 16-bit Timer
 *
 * File Name: timer1.h
 *
 * Description: Header file for the AVR Timer driver
 *
 * Author: Reem Mohy
*************************************************************************************************/
#ifndef TIMER1_H_
#define TIMER1_H_

#include"std_types.h"

/*************************************************************************************************
                                Types Definition
*************************************************************************************************/
typedef enum{
	NO_CLOCK,F_CPU_1,F_CPU_8,F_CPU_64,F_CPU_256,F_CPU_1024
}Timer1_Prescaler;

typedef enum{
	OVERFLOW_MODE,COMPARE_MODE
}Timer1_Mode;

typedef struct{

	uint16 initial_value;
	uint16 compare_value;    /*It will be used in compare mode only*/
	Timer1_Prescaler prescaler;
	Timer1_Mode mode;

}Timer1_ConfigType;

/*************************************************************************************************
                                Function Prototype
 *************************************************************************************************/

/*
 * Description:
 * Function to initialize the Timer driver.
 */
void TIMER1_init(const Timer1_ConfigType* Config_Ptr);

/*
 * Description:
 * Function to disable the Timer.
 */
void TIMER1_deInit(void);

/*
 * Description:
 * Function to set the Call Back function address.
 */
void TIMER1_setCalleBack(void(*a_ptr)(void));

#endif /* TIMER1_H_ */
