/******************************************************************************
 * Module: DC-Motor
 *
 * File Name: dc_motor.c
 *
 * Description: Source file for the DC-Motor driver
 *
 * Author: Reem Mohy
 *******************************************************************************/

#include "dc_motor.h"
#include "gpio.h"
#include "pwm.h"

/*
 *Description:
 * The Function responsible for setup the direction for the two motor pins through the GPIO driver.
 * Stop the DC-Motor at the beginning through the GPIO driver.
 */
void DcMotor_init(void)
{
	/*Setup two pins of L293D chip as output pin (PB0,PB1)*/
	GPIO_setupPinDirection(L293D_CHIP_IN1_PORT_ID,L293D_CHIP_IN1_PIN_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(L293D_CHIP_IN2_PORT_ID,L293D_CHIP_IN2_PIN_ID,PIN_OUTPUT);

	/*Initially stop the motor by writing logic low on two pins of L293D chip */
	GPIO_writePin(L293D_CHIP_IN1_PORT_ID,L293D_CHIP_IN1_PIN_ID,LOGIC_LOW);
	GPIO_writePin(L293D_CHIP_IN2_PORT_ID,L293D_CHIP_IN2_PIN_ID,LOGIC_LOW);
}

/*
 *Description:
 * The Function responsible for rotate the DC Motor CW/ or A-CW or stop the motor based on the state input state value.
 * Send the required duty cycle to the PWM driver based on the required speed value.
 */
void DcMotor_rotate(DcMotor_State a_state,uint8 a_speed)
{
	/*Send the required duty cycle to the PWM driver to control the speed of motor rotation*/
	PWM_Timer0_Start(a_speed);

	/*
	 * Rotate the motor as required based on state value
	 * Stop => IN1=0,IN2=0
	 * Clockwise => IN1=0,IN2=1
	 * Anti-clockwise => IN1=1,IN2=0
	 */
	switch(a_state)
	{

	case STOP:
		GPIO_writePin(L293D_CHIP_IN1_PORT_ID,L293D_CHIP_IN1_PIN_ID,LOGIC_LOW);
		GPIO_writePin(L293D_CHIP_IN2_PORT_ID,L293D_CHIP_IN2_PIN_ID,LOGIC_LOW);
		break;

	case CLOCK_WISE:
		GPIO_writePin(L293D_CHIP_IN1_PORT_ID,L293D_CHIP_IN1_PIN_ID,LOGIC_LOW);
		GPIO_writePin(L293D_CHIP_IN2_PORT_ID,L293D_CHIP_IN2_PIN_ID,LOGIC_HIGH);
		break;

	case ANTI_CLOCK_WISE:
			GPIO_writePin(L293D_CHIP_IN1_PORT_ID,L293D_CHIP_IN1_PIN_ID,LOGIC_HIGH);
			GPIO_writePin(L293D_CHIP_IN2_PORT_ID,L293D_CHIP_IN2_PIN_ID,LOGIC_LOW);
			break;
	}
}

