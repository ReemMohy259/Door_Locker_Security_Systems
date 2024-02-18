/******************************************************************************
 * Module: TWI(I2C)
 *
 * File Name: twi.h
 *
 * Description: Header file for the TWI(I2C) AVR driver.
 *
 * Author: Reem Mohy
 *******************************************************************************/ 

#ifndef TWI_H_
#define TWI_H_

#include "std_types.h"

/*******************************************************************************
                             Definitions
 *******************************************************************************/

/*I2C Status Bits in the TWSR Register*/
#define TWI_START         0x08   /*Start has been sent*/
#define TWI_REP_START     0x10   /*Repeated start*/
#define TWI_MT_SLA_W_ACK  0x18   /*Master transmit ( slave address + Write request ) to slave + ACK received from slave.*/
#define TWI_MT_SLA_R_ACK  0x40   /*Master transmit ( slave address + Read request ) to slave + ACK received from slave.*/
#define TWI_MT_DATA_ACK   0x28   /*Master transmit data and ACK has been received from Slave.*/
#define TWI_MR_DATA_ACK   0x50   /*Master received data and send ACK to slave.*/
#define TWI_MR_DATA_NACK  0x58   /*Master received data but doesn't send ACK to slave.*/

/*******************************************************************************
                          Types Definition
 *******************************************************************************/

typedef uint8       TWI_Address;

typedef enum{
	NORMAL_100K,FAST_400K,FAST_PLUS_1M,HIGH_SPEED_3M
}TWI_BaudRate;

typedef enum{
	ZERO,ONE,TWO,THREE
}TWI_PrescalerBits;

typedef struct{

 TWI_Address address;
 TWI_BaudRate bit_rate;
 TWI_PrescalerBits prescaler;

}TWI_ConfigType;

/*******************************************************************************
                        Functions Prototypes
 *******************************************************************************/

/*
 * Description:
 * Function to initialize and enable the I2C module.
 */
void TWI_init(const TWI_ConfigType * Config_Ptr);

/*
 * Description:
 * Function that master send the start bit and start communication.
 */
void TWI_start(void);

/*
 * Description:
 * Function that master send the stop bit and end communication.
 */
void TWI_stop(void);

/*
 * Description:
 * Function to send byte to the I2C receiver.
 */
void TWI_writeByte(uint8 data);

/*
 * Description:
 * Function to receive byte from the I2C sender.
 * Then the receiver send an acknowledge (ACK) to the sender.
 */
uint8 TWI_readByteWithACK(void);

/*
 * Description:
 * Function to receive byte from the I2C.
 * But the receiver doesn't send an acknowledge (ACK) to the sender.
 */
uint8 TWI_readByteWithNACK(void);

/*
 * Description:
 * Function to get the statues of I2C module from TWSR register.
 */
uint8 TWI_getStatus(void);

#endif /* TWI_H_ */
