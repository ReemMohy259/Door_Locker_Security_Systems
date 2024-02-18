/******************************************************************************
 * Module: TWI(I2C)
 *
 * File Name: twi.h
 *
 * Description: Source file for the TWI(I2C) AVR driver
 *
 * Author: Reem Mohy
 *******************************************************************************/
 
#include "twi.h"
#include "common_macros.h"
#include <avr/io.h>

/*
 * Description:
 * Function to initialize and enable the I2C module.
 */
void TWI_init(const TWI_ConfigType * Config_Ptr)
{
	/*Calculate the value of stored in bit rate register TWBR depending on prescaler and F_CPU and the chosen bit rate */
    TWBR = (uint8) (((F_CPU /(float32) Config_Ptr->bit_rate) - 16)  / (2 * (4^Config_Ptr->prescaler)));

    /*Insert the required value of prescaler bits (TWPS0:1) in TWSR register */
	TWSR = Config_Ptr->prescaler;
	
    /* Two Wire Bus address my address if any master device want to call me (used in case this MC is a slave device)
       General Call Recognition: Off */
    TWAR = Config_Ptr->address;
	
    TWCR = (1<<TWEN); /* enable TWI */
}

/*
 * Description:
 * Function that master send the start bit and start communication.
 */
void TWI_start(void)
{
    /* 
	 * Clear the TWINT flag before sending the start bit TWINT=1
	 * send the start bit by TWSTA=1
	 * Enable TWI Module TWEN=1 
	 */
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
    
    /* Wait for TWINT flag set in TWCR Register (start bit is send successfully) */
    while(BIT_IS_CLEAR(TWCR,TWINT));
}

/*
 * Description:
 * Function that master send the stop bit and end communication.
 */
void TWI_stop(void)
{
    /* 
	 * Clear the TWINT flag before sending the stop bit TWINT=1
	 * send the stop bit by TWSTO=1
	 * Enable TWI Module TWEN=1 
	 */
    TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
}

/*
 * Description:
 * Function to send byte to the I2C receiver.
 */
void TWI_writeByte(uint8 data)
{
    /* Put data On TWI data Register */
    TWDR = data;
    /* 
	 * Clear the TWINT flag before sending the data TWINT=1
	 * Enable TWI Module TWEN=1 
	 */ 
    TWCR = (1 << TWINT) | (1 << TWEN);

    /* Wait for TWINT flag set in TWCR Register(data is send successfully) */
    while(BIT_IS_CLEAR(TWCR,TWINT));
}

/*
 * Description:
 * Function to receive byte from the I2C sender.
 * Then the receiver send an acknowledge (ACK) to the sender.
 */
uint8 TWI_readByteWithACK(void)
{
	/* 
	 * Clear the TWINT flag before reading the data TWINT=1
	 * Enable sending ACK after reading or receiving data TWEA=1
	 * Enable TWI Module TWEN=1 
	 */ 
    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);

    /* Wait for TWINT flag set in TWCR Register (data received successfully) */
    while(BIT_IS_CLEAR(TWCR,TWINT));
    /* Read Data */
    return TWDR;
}

/*
 * Description:
 * Function to receive byte from the I2C.
 * But the receiver doesn't send an acknowledge (ACK) to the sender.
 */
uint8 TWI_readByteWithNACK(void)
{
	/* 
	 * Clear the TWINT flag before reading the data TWINT=1
	 * Enable TWI Module TWEN=1 
	 */
    TWCR = (1 << TWINT) | (1 << TWEN);

    /* Wait for TWINT flag set in TWCR Register (data received successfully) */
    while(BIT_IS_CLEAR(TWCR,TWINT));
    /* Read Data */
    return TWDR;
}

/*
 * Description:
 * Function to get the statues of I2C module from TWSR register.
 */
uint8 TWI_getStatus(void)
{
    uint8 status;

    /* masking to eliminate first 3 bits and get the last 5 bits (status bits) */
    status = TWSR & 0xF8;

    return status;
}
