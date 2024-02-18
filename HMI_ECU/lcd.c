/*******************************************************************************
 * Module: LCD
 *
 * File Name: lcd.c
 *
 * Description: Source file for the LCD driver
 *
 * Author: Reem Mohy
 *******************************************************************************/

#include <util/delay.h>     /*To use delay function*/
#include "common_macros.h"  /*For commonly used macros in some operations*/
#include "gpio.h"           /*To use GPIO drivers functions*/
#include "lcd.h"


/*******************************************************************************
 *                      Functions Definitions
 *******************************************************************************/

/*
 * Description:
 * Initialize the LCD.
 * Setup the LCD pins direction by use the GPIO driver.
 * Setup the LCD data mode 4-bits or 8-bits.
 */
void LCD_init(void)
{
	/*Setup the direction of RS and E pins as output pins*/
	GPIO_setupPinDirection(LCD_RS_PORT_ID,LCD_RS_PIN_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_E_PORT_ID,LCD_E_PIN_ID,PIN_OUTPUT);

#if(LCD_DATA_BIT_MODE == 4)
	/*Setup the direction of data path (PA3 -> PA6) as output pins*/
	GPIO_setupPinDirection(LCD_DATA_PORT_ID,LCD_DB4_PIN_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_DATA_PORT_ID,LCD_DB5_PIN_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_DATA_PORT_ID,LCD_DB6_PIN_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_DATA_PORT_ID,LCD_DB7_PIN_ID,PIN_OUTPUT);

	_delay_ms(20);        /* LCD Power ON delay always > 15ms */

	/* Send for 4 bit initialization of LCD  */
	LCD_sendCommand(LCD_TWO_LINES_FOUR_BITS_MODE_INIT1);
	LCD_sendCommand(LCD_TWO_LINES_FOUR_BITS_MODE_INIT2);

	/* use 2-lines LCD + 4-bits Data Mode + 5*7 dot display Mode */
	LCD_sendCommand(LCD_TWO_LINES_FOUR_BITS_MODE);

#elif(LCD_DATA_BIT_MODE == 8)
	/* Setup the data port as output port */
	GPIO_setupPortDirection(LCD_DATA_PORT_ID,PORT_OUTPUT);

	/* use 2-lines LCD + 8-bits Data Mode + 5*7 dot display Mode */
	LCD_sendCommand(LCD_TWO_LINES_EIGHT_BITS_MODE);

#endif

	LCD_sendCommand(LCD_CURSOR_OFF);  /*Cursor OFF*/
	LCD_sendCommand(LCD_CLEAR_COMMAND);  /*Clear the screen at the beginning*/
}

/*
 * Description:
 * Send the required command to the LCD.
 */
void LCD_sendCommand(const uint8 a_command)
{
	GPIO_writePin(LCD_RS_PORT_ID,LCD_RS_PIN_ID,LOGIC_LOW);  /*Instruction Mode RS=0 */
	_delay_ms(1);    /* delay for processing Tas = 50ns */
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_HIGH);  /*Enable LCD E=1*/
	_delay_ms(1);    /* delay for processing Tpw - Tdws = 190ns */

#if(LCD_DATA_BIT_MODE == 4)
	/*Write first higher 4-bits in command (From bit 4 to bit 7) on (DB4->DB7)*/
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB4_PIN_ID,GET_BIT(a_command,4));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB5_PIN_ID,GET_BIT(a_command,5));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB6_PIN_ID,GET_BIT(a_command,6));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB7_PIN_ID,GET_BIT(a_command,7));

	_delay_ms(1);    /* delay for processing Tdsw = 100ns */
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_LOW);  /*Disable LCD E=0*/
	_delay_ms(1); /* delay for processing Th = 13ns */
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_HIGH);
	_delay_ms(1);    /* delay for processing Tpw - Tdws = 190ns */

	/*Write second lower 4-bits in command (From bit 0 to bit 3) on (DB4->DB7)*/
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB4_PIN_ID,GET_BIT(a_command,0));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB5_PIN_ID,GET_BIT(a_command,1));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB6_PIN_ID,GET_BIT(a_command,2));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB7_PIN_ID,GET_BIT(a_command,3));

#elif(LCD_DATA_BIT_MODE == 8)
	GPIO_writePort(LCD_DATA_PORT_ID,a_command);   /* Write the required command to the data bus D0 --> D7 */

#endif

	_delay_ms(1);    /* delay for processing Tdsw = 100ns */
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_LOW); /* Disable LCD E=0 */
	_delay_ms(1);    /* delay for processing Th = 13ns */
}

/*
 * Description:
 * Display the required character on the LCD screen.
 */
void LCD_displayCharacter(const uint8 a_data)
{
	GPIO_writePin(LCD_RS_PORT_ID,LCD_RS_PIN_ID,LOGIC_HIGH);  /*Display data Mode RS=1 */
	_delay_ms(1);    /* delay for processing Tas = 50ns */
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_HIGH);  /*Enable LCD E=1*/
	_delay_ms(1);    /* delay for processing Tpw - Tdws = 190ns */

#if(LCD_DATA_BIT_MODE == 4)
	/*Write first higher 4-bits in data (From bit 4 to bit 7) on (DB4->DB7)*/
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB4_PIN_ID,GET_BIT(a_data,4));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB5_PIN_ID,GET_BIT(a_data,5));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB6_PIN_ID,GET_BIT(a_data,6));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB7_PIN_ID,GET_BIT(a_data,7));

	_delay_ms(1);    /* delay for processing Tdsw = 100ns */
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_LOW);   /*Disable LCD E=0*/
	_delay_ms(1);    /* delay for processing Th = 13ns */
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_HIGH);   /*Enable LCD E=1*/
	_delay_ms(1);    /* delay for processing Tpw - Tdws = 190ns */

	/*Write second lower 4-bits in data (From bit 0 to bit 3) on (DB4->DB7)*/
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB4_PIN_ID,GET_BIT(a_data,0));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB5_PIN_ID,GET_BIT(a_data,1));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB6_PIN_ID,GET_BIT(a_data,2));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB7_PIN_ID,GET_BIT(a_data,3));


#elif(LCD_DATA_BIT_MODE == 8)
	GPIO_writePort(LCD_DATA_PORT_ID,a_data);   /*Display the required data on the data bus D0 --> D7 */

#endif

	_delay_ms(1);    /* delay for processing Tdsw = 100ns */
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_LOW); /* Disable LCD E=0 */
	_delay_ms(1);    /* delay for processing Th = 13ns */
}

/*
 * Description:
 * Display the required String on the LCD screen.
 */
void LCD_displayString(const sint8 *a_str)
{
	/*loop on the string until the end (Null character)*/
	while((*a_str) != '\0')
	{
		/*Display character by character*/
		LCD_displayCharacter(*a_str);
		a_str++;
	}
}

/*
 * Description:
 * Move the cursor to a specific row and column index on the screen.
 */
void LCD_moveCursor(uint8 a_row,uint8 a_col)
{
	uint8 memoryAddress;

	/*Calculate the required address in the LCD DDRAM*/
	switch(a_row)
	{
	case 0:
		memoryAddress = a_col;
		break;

	case 1:
		memoryAddress = a_col+0x40;
		break;

	case 2:
		memoryAddress = a_col+0x10;
		break;

	case 4:
		memoryAddress = a_col+0x50;
		break;
	}
	/*Move the cursor to the required address*/
	LCD_sendCommand(memoryAddress | LCD_SET_CURSOR_LOCATION);
}

/*
 * Description :
 * Display the required string in a specified row and column index on the screen.
 */
void LCD_displayStringRowColumn(uint8 a_row,uint8 a_col,const sint8 *a_str)
{
	LCD_moveCursor(a_row,a_col);  /*Move the cursor to the required location*/
	LCD_displayString(a_str);     /*Display the required string*/
}

/*
 * Description :
 * Display the required decimal value on the screen
 */
void LCD_intgerToString(int a_data)
{
	sint32 buff[16];  /*String to hold the ASCII result*/
	itoa(a_data,buff,10); /*C function to convert the decimal numbers to its ASCII value (10 for decimal base)*/
	LCD_displayString(buff);
}

/*
 * Description :
 * Send the clear screen command
 */
void LCD_clearScreen(void)
{
	/* Send clear display command */
	LCD_sendCommand(LCD_CLEAR_COMMAND);
}
