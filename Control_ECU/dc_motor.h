/******************************************************************************
 * Module: DC-Motor
 *
 * File Name: dc_motor.h
 *
 * Description: Header file for the DC-Motor driver
 *
 * Author: Reem Mohy
 *******************************************************************************/


#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_

#include "std_types.h"

/*******************************************************************************
 *                      Definitions
 *******************************************************************************/
#define L293D_CHIP_IN1_PORT_ID           PORTB_ID
#define L293D_CHIP_IN1_PIN_ID            PIN0_ID

#define L293D_CHIP_IN2_PORT_ID           PORTB_ID
#define L293D_CHIP_IN2_PIN_ID            PIN1_ID

#define L293D_CHIP_EN1_PORT_ID           PORTB_ID
#define L293D_CHIP_EN1_PIN_ID            PIN3_ID

/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/

/*
 * Description:
 * Enumeration responsible for configuration of DC-Motor state.
 */
typedef enum
{
	STOP,CLOCK_WISE,ANTI_CLOCK_WISE
}DcMotor_State;

/*******************************************************************************
 *                      Functions Prototypes
 *******************************************************************************/

/*
 *Description:
 * The Function responsible for setup the direction for the two motor pins through the GPIO driver.
 * Stop the DC-Motor at the beginning through the GPIO driver.
 */
void DcMotor_init(void);

/*
 *Description:
 * The Function responsible for rotate the DC Motor CW/ or A-CW or stop the motor based on the state input state value.
 * Send the required duty cycle to the PWM driver based on the required speed value.
 */
void DcMotor_rotate(DcMotor_State a_state,uint8 a_speed);

#endif /* DC_MOTOR_H_ */
