/*******************************************************************************
 * Module: LCD
 *
 * File Name: lcd.h
 *
 * Description: Header file for the LCD driver
 *
 * Author: Reem Mohy
 *******************************************************************************/


#ifndef LCD_H_
#define LCD_H_

#include "std_types.h"

/*******************************************************************************
 *                             Definitions
 *******************************************************************************/

/*LCD data bit mode configuration (4 or 8)*/
#define LCD_DATA_BIT_MODE  8

#if((LCD_DATA_BIT_MODE != 4) && (LCD_DATA_BIT_MODE !=8))

#error "Invalid Bit Mode (should be 4 or 8)"

#endif

/*LCD HW Ports and Pins connections to MC*/
#define LCD_RS_PORT_ID                     PORTD_ID
#define LCD_RS_PIN_ID                      PIN4_ID

#define LCD_E_PORT_ID                      PORTD_ID
#define LCD_E_PIN_ID                       PIN6_ID

#define LCD_DATA_PORT_ID                   PORTC_ID

#if(LCD_DATA_BIT_MODE == 4)

#define LCD_DB4_PIN_ID                     PIN3_ID
#define LCD_DB5_PIN_ID                     PIN4_ID
#define LCD_DB6_PIN_ID                     PIN5_ID
#define LCD_DB7_PIN_ID                     PIN6_ID

#endif

/*LCD Command Addresses*/
#define LCD_CLEAR_COMMAND                       0x01
#define LCD_GO_TO_HOME                          0x02
#define LCD_TWO_LINES_EIGHT_BITS_MODE           0x38
#define LCD_TWO_LINES_FOUR_BITS_MODE            0x28
#define LCD_TWO_LINES_FOUR_BITS_MODE_INIT1      0x33
#define LCD_TWO_LINES_FOUR_BITS_MODE_INIT2      0x32
#define LCD_CURSOR_OFF                          0x0C
#define LCD_CURSOR_ON                           0x0E
#define LCD_SET_CURSOR_LOCATION                 0x80

/********************************************************************************
 *                           Function Prototypes
 ********************************************************************************/

/*
 * Description:
 * Initialize the LCD.
 * Setup the LCD pins direction by use the GPIO driver.
 * Setup the LCD data mode 4-bits or 8-bits.
 */
void LCD_init(void);

/*
 * Description:
 * Send the required command to the LCD.
 */
void LCD_sendCommand(const uint8 a_command);

/*
 * Description:
 * Display the required character on the LCD screen.
 */
void LCD_displayCharacter(const uint8 a_data);

/*
 * Description:
 * Display the required String on the LCD screen.
 */
void LCD_displayString(const sint8 *a_str);

/*
 * Description:
 * Move the cursor to a specific row and column index on the screen.
 */
void LCD_moveCursor(uint8 a_row,uint8 a_col);

/*
 * Description :
 * Display the required string in a specified row and column index on the screen.
 */
void LCD_displayStringRowColumn(uint8 a_row,uint8 a_col,const sint8 *a_str);

/*
 * Description :
 * Display the required decimal value on the screen
 */
void LCD_intgerToString(int a_data);

/*
 * Description :
 * Send the clear screen command
 */
void LCD_clearScreen(void);

#endif /* LCD_H_ */
