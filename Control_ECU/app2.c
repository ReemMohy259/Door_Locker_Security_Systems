/*
 ============================================================================
 Name        : app.c
 Author      : Reem Mohy
 Description : Application layer of control ECU
 Date        : 6/11/2022
 ============================================================================
 */

/*F_CPU = 8MHZ*/

#include "mc2.h"

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

/******************************************************************************************************************************************************************/

int main(void)
{
	uint8 pass1[ARR_SIZE+1];
	uint8 pass2[ARR_SIZE+1];
	uint8 check;
	uint8 savedPass[ARR_SIZE+1];
	uint8 receivedByte;
	uint8 trials = 0;

	/*UART configuration structure*/
	Uart_ConfigType s_UartConfig = { _8_bit,DISABLE,ONE_STOP_BIT,9600 };

	/*TWI configuration structure*/
	TWI_ConfigType s_TwiConfig = { 0b00000010,FAST_400K,ZERO};

	/*Timer1 configuration structure*/
	Timer1_ConfigType s_Timer1Config = { 0,23437,F_CPU_1024,COMPARE_MODE};

	UART_init(&s_UartConfig);
	TWI_init(&s_TwiConfig );
	DcMotor_init();
	BUZZER_init();

	sei();

	while(1)
	{
		/*
		 * If password entered wrong 3 consecutive time.
		 * Turn buzzer on for one minute.
		 */
		if(trials >= 3)
		{
			BUZZER_on();
			_delay_ms(10000);
			BUZZER_off();

			trials = 0;     /*Reset trials*/
		}

		while(UART_receiveByte()!= READY);  /*Wait until HMI_ECU send the two passwords*/

		/*Receive two passwords*/
		UART_receiveString(pass1);
		UART_receiveString(pass2);

		check = check_createdPassword(pass1,pass2);  /*Compare two passwords together*/
		_delay_ms(100);

		if(check == INCORRECT_PASS)
		{
			/*Send to HMI_ECU that two password didn't matched*/
			UART_sendByte(READY);
			UART_sendByte(INCORRECT_PASS);
		}
		else if(check == CORRECT_PASS)
		{
			/*Send to HMI_ECU that two password are matched*/
			UART_sendByte(READY);
			UART_sendByte(CORRECT_PASS);

			EEPROM_write_Password(pass1);      /*Save password in EEPROM*/

			EEPROM_read_Password(savedPass);   /*Read saved password from EEPROM and store it in another variable*/

			/*Start the system main options*/

			while(1)
			{
				while(UART_receiveByte()!= READY);  /*Wait until HMI_ECU send the password*/

				receivedByte = UART_receiveByte();  /*Receive the option step*/

				if(receivedByte == OPEN_DOOR)
				{
					/*Receive the password and compare it with one saved in EEPROM*/
					UART_receiveString(pass1);

					check = check_createdPassword(pass1,savedPass);

					if(check == INCORRECT_PASS)
					{
						trials++;						/*Increament the incorrect trials*/
						UART_sendByte(READY);
						UART_sendByte(INCORRECT_PASS);	 /*Send to HMI_ECU the that password is incorrect*/

						continue;
					}
					else if(check == CORRECT_PASS)
					{
						/************************COMMENT************************/
						/* code using timer1 was not working, but with delay it was working,
						 *
						 * I surrounded the code of timer1 with #if 0 and after it the same code using
						 * delay function
						 */
#if(0)
						UART_sendByte(READY);
						UART_sendByte(CORRECT_PASS);  /*Send to HMI_ECU the that password is correct*/

						UART_sendByte(OPEN_DOOR);

						TIMER1_init(& s_Timer1Config);
						TIMER1_setCalleBack(DcMotorControl);

						DcMotor_rotate(CLOCK_WISE,100);

						while(flag_1 != 1);  /*Wait 15 seconds*/

						DcMotor_rotate(STOP,0);

						while(flag_2 != 1);    /*Wait 3 seconds*/

						DcMotor_rotate(ANTI_CLOCK_WISE,100);
						while(flag_3 != 1);  /*Wait 15 seconds*/

						DcMotor_rotate(STOP,0);

						TIMER1_deInit();

						flag_1 = 0;
						flag_2 = 0;
						flag_3 = 0;

						trials = 0;   /*Reset the incorrect trials*/
						while(UART_receiveByte() != CONTINUE);
#endif

                        /* code using delay function */
						UART_sendByte(READY);
						UART_sendByte(CORRECT_PASS);  /*Send to HMI_ECU the that password is correct*/

						UART_sendByte(OPEN_DOOR);

						DcMotor_rotate(CLOCK_WISE,100);

						_delay_ms(15000);

						UART_sendByte(READY);

						DcMotor_rotate(STOP,100);
						_delay_ms(3000);

						UART_sendByte(READY);

						DcMotor_rotate(ANTI_CLOCK_WISE,100);
						_delay_ms(15000);

						UART_sendByte(READY);

						DcMotor_rotate(STOP,100);
						_delay_ms(3000);

						UART_sendByte(READY);

						trials = 0;   /*Reset the incorrect trials*/

						while(UART_receiveByte() != CONTINUE);
					}
				}

				else if(receivedByte == CHANGE_PASS)
				{
					/*Receive the password and compare it with one saved in EEPROM*/
					UART_receiveString(pass1);

					check = check_createdPassword(pass1,savedPass);

					if(check == INCORRECT_PASS)
					{
						trials++;						/*Increament the incorrect trials*/
						UART_sendByte(READY);
						UART_sendByte(INCORRECT_PASS);	 /*Send to HMI_ECU the that password is incorrect*/

						continue;
					}
					else if(check == CORRECT_PASS)
					{
						trials = 0;
						UART_sendByte(READY);
						UART_sendByte(CORRECT_PASS);	 /*Send to HMI_ECU the that password is correct*/

						break;    /*Repeat all steps again from the beginning of first while(1)*/
					}
				}
			}
		}
	}
}
