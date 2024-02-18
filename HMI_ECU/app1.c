/*
 ============================================================================
 Name        : app1.c
 Author      : Reem Mohy
 Description : Application layer of human interface ECU
 Date        : 6/11/2022
 ============================================================================
 */

/*F_CPU = 1MHZ*/

#include "mc1.h"

uint8 flag_1 = 0;
uint8 flag_2 = 0;
uint8 flag_3 = 0;

/*The call back function called by the timer ISR*/
void DcMotorControl(void)
{
	static uint8 tick = 0;
	tick++;

	if(tick == 5)
	{
		flag_1 = 1;
	}
	else if(tick == 6)
	{
		flag_2 = 1;
	}
	else if(tick == 11)
	{
		flag_3 = 1;
		tick = 0;
	}
}

/*******************************************************************************************************************************************************************/

int main(void)
{
	uint8 pass1[ARR_SIZE+1];
	uint8 pass2[ARR_SIZE+1];

	uint8 keyButton;
	uint8 receivedByte;
	uint8 trials = 0;


	/*UART configuration structure*/
	Uart_ConfigType s_UartConfig = { _8_bit,DISABLE,ONE_STOP_BIT,9600 };

	/*Timer1 configuration structure*/
	Timer1_ConfigType s_Timer1Config = { 0,2929,F_CPU_1024,COMPARE_MODE};

	UART_init(&s_UartConfig);
	LCD_init();



	//SREG |= (1<<7);
	sei();


	while(1)
	{
		do
		{
			/*Ask the user to write the required password*/
			LCD_clearScreen();
			LCD_displayString("PLZ Enter Pass:");
			LCD_moveCursor(1,0);  /*Set the display screen before calling the function*/
			get_password(pass1);  /*Get the first password*/

			/*Ask the user to re-enter the same password*/
			LCD_clearScreen();
			LCD_displayStringRowColumn(0,0,"PLZ Re-Enter the");
			LCD_displayStringRowColumn(1,0,"Same Pass:");
			LCD_moveCursor(1,10);  /*Set the display screen before calling the function*/
			get_password(pass2);  /*Get the second password*/

			/*Call the function to check if two passwords are matching or not*/
			receivedByte = check_createdPassword(pass1,pass2);

			_delay_ms(50);
		} while(receivedByte != CORRECT_PASS);   /*Wait until the user write two matched passwords*/

		_delay_ms(50);

		while(1)
		{

			/*
			 * If password entered wrong 3 consecutive time.
			 * Error message on LCD is displayed for one minute.
			 */
			if(trials >= 3)
			{
				LCD_clearScreen();
				LCD_displayStringRowColumn(0,5,"ERROR :(");
				_delay_ms(10000);

				trials = 0;		/*Reset trials*/
			}

			/*Display the main options*/
			LCD_clearScreen();
			LCD_displayStringRowColumn(0,0,"+ : Open Door");
			LCD_displayStringRowColumn(1,0,"- : Change Pass");

			keyButton = KEYPAD_getPressedKey();
			_delay_ms(500);

			if(keyButton == '+')  /*Open the door*/
			{
				receivedByte = check_mainOptionPassword(pass1,trials,OPEN_DOOR);

				if(receivedByte == INCORRECT_PASS)
				{
					trials++;   /*Increment the incorrect trials counter*/
					LCD_clearScreen();
					LCD_displayStringRowColumn(0,0,"Incorrect Pass");

					_delay_ms(1000);  /*Wait 1 second*/
					continue;   /*Repeat the same steps of main options*/
				}
				else if(receivedByte == CORRECT_PASS)
				{
/****************************	COMMENT ***************************************************************/
					/* code using timer1 was not working, but with delay it was working,
					 *
					 * I surrounded the code of timer1 with #if 0 and after it the same code using
					 * delay function
					 */

#if(0)
					while(UART_receiveByte() != OPEN_DOOR);  /*Wait until control_ECU send to open the door*/

					TIMER1_setCalleBack(DcMotorControl);
					/* start timer1 */
					TIMER1_init(& s_Timer1Config);


					LCD_clearScreen();
					LCD_displayStringRowColumn(0,0,"Door Unlocking");

					while(flag_1 != 1);     /*Wait 15 seconds*/

					LCD_clearScreen();
					LCD_displayStringRowColumn(0,0,"#Door Unlocked#");

					while(flag_2 != 1);     /*Wait 3 seconds*/

					LCD_clearScreen();
					LCD_displayStringRowColumn(0,0,"Door is locking");

					while(flag_3 != 1);     /*Wait 15 seconds*/

					TIMER1_deInit();

					/* reset all flags for next trial */
					flag_1 =0;
					flag_2 =0;
					flag_3 =0;

					trials = 0;   /*Reset the trials counter*/
					UART_sendByte(CONTINUE);
					continue;
#endif

                   /* code using delay function */
					while(UART_receiveByte() != OPEN_DOOR);  /*Wait until control_ECU send to open the door*/

					LCD_clearScreen();
					LCD_displayStringRowColumn(0,0,"Door is Unlocking");

					while(UART_receiveByte() != READY);
					_delay_ms(50);

					LCD_clearScreen();
					LCD_displayStringRowColumn(0,0,"#Door Unlocked#");

					while(UART_receiveByte() != READY);
					_delay_ms(50);

					LCD_clearScreen();
					LCD_displayStringRowColumn(0,0,"Door is locking");

					while(UART_receiveByte() != READY);
					_delay_ms(50);

					LCD_clearScreen();
					LCD_displayStringRowColumn(0,0,"#Door Locked#");

					while(UART_receiveByte() != READY);
					_delay_ms(50);

					trials = 0;   /*Reset the trials counter*/

					UART_sendByte(CONTINUE);

					continue;
				}
			}

			else if(keyButton == '-')  /*Change the password*/
			{
				receivedByte = check_mainOptionPassword(pass1,trials,CHANGE_PASS);

				if(receivedByte == INCORRECT_PASS)
				{
					trials++;   /*Increment the incorrect trials counter*/
					LCD_clearScreen();
					LCD_displayStringRowColumn(0,0,"Incorrect Pass");

					_delay_ms(1000);  /*Wait 1 second*/
					continue; /*Repeat the same steps of main options*/
				}
				else if(receivedByte == CORRECT_PASS)
				{
					trials = 0;

					break;    /*Repeat all steps again from the beginning of first while(1)*/
				}
			}
		}
	}
}
