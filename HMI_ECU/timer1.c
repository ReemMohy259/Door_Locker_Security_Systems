/*************************************************************************************************
 * Module: 16-bit Timer
 *
 * File Name: timer1.c
 *
 * Description: Source file for the AVR Timer driver
 *
 * Author: Reem Mohy
*************************************************************************************************/
#include "timer1.h"
#include "common_macros.h"
#include <avr/io.h>   /*To use tumer1 registers*/
#include <avr/interrupt.h>

/*************************************************************************************************
                               Global Variables
*************************************************************************************************/

/*Hold the address of the call back function*/
static volatile void(*g_callBackPtr)(void) = NULL_PTR;

/*************************************************************************************************
                              Interrupt Service Routines
 *************************************************************************************************/
/*ISR of Timer1 overflow mode*/
ISR(TIMER1_OVF_vect)
{
	if(g_callBackPtr != NULL_PTR)
	{
		/* Call the Call Back function in the application using pointer to function*/
		(*g_callBackPtr)();
	}
}


/*ISR of Timer1 compare mode of channel A*/
ISR(TIMER1_COMPA_vect)
{
	if(g_callBackPtr != NULL_PTR)
	{
		/* Call the Call Back function in the application using pointer to function*/
		(*g_callBackPtr)();
	}
}


/*************************************************************************************************
                               Function Definitions
 *************************************************************************************************/

/*
 * Description:
 * Function to initialize the Timer driver
 */
void TIMER1_init(const Timer1_ConfigType * Config_Ptr)
{
	TCCR1A = (1<<FOC1A);

	/* put initial value of timer1 in TCNT1 */
	TCNT1 = Config_Ptr->initial_value;

	/* Insert first two bits of Timer1_Mode in first two bits in TCCR1A */
	TCCR1A = ( TCCR1A & 0xFC ) | ( Config_Ptr->mode & 0x03);

	/*Insert bit-3 and bit-2 of Timer1_Mode in bit-4 and bit-3 bit in TCCR1B */
	TCCR1A = (TCCR1A & 0xE7) | ( (Config_Ptr->mode & 0x0C) <<1);

	/*Insert timer1_prescalar value in first three bits of TCCR1A */
	TCCR1B = (TCCR1B & 0XF8) | ( Config_Ptr->prescaler & 0x07);

	/*
	 * put compare value of timer1 in OCR1A and enable OCIE1A for compare match
	 * interrupt, when working in CTC mode
	 */
	if(Config_Ptr->mode == COMPARE_MODE)
	{
		OCR1A = Config_Ptr->compare_value;

		SET_BIT (TIMSK, OCIE1A);
	}
	else if(Config_Ptr->mode == OVERFLOW_MODE)
	{
		/* Enable overflow interrupt enable when working in normal mode */
		SET_BIT(TIMSK, TOIE1);
	}
	else
	{
		/*Do Nothing */
	}
}
/*
 * Description:
 * Function to disable the Timer.
 */
void TIMER1_deInit(void)
{
	/* Clear All Timer1 Registers */
	TCCR1A = 0;
	TCCR1B = 0;
	TCNT1  = 0;
	OCR1A  = 0;
	TIMSK &= 0xC3;  /*Disable Timer1 interrupts*/
}

/*
 * Description:
 * Function to set the Call Back function address.
 */
void TIMER1_setCalleBack(void(*a_ptr)(void))
{
	/* Save the address of the Call back function in a global variable */
	g_callBackPtr = a_ptr;
}
