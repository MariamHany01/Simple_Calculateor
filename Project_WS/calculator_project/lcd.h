/*
 * lcd.h
 *
 *  Created on: 4 Oct 2023
 *      Author: maria
 */

#ifndef LCD_H_
#define LCD_H_

#include"std_types.h"
/*************************************************************************************************
                                   important definitions
************************************************************************************************ */
#define LCD_DATA_BITS_MODE 4

/*to check over bits mood if not 8 or 4 */
#if (!((LCD_DATA_BITS_MODE==4)||((LCD_DATA_BITS_MODE==8))))
#error "moods are 8_bit and 4_bit only"
#endif


/*configurations for REFISTER SELECT PIN-> 1:write write command ,0:write data */
#define LCD_RS_PORT_ID  PORTA_ID
#define LCD_RS_PIN_ID   PIN1_ID

/*Configurations for the enable pin */
#define LCD_E_PORT_ID  PORTA_ID
#define LCD_E_PIN_ID   PIN2_ID

/*Configurations for the data path  pins */
#define LCD_DB_PORT_ID PORTA_ID

/*in case of 4 bits mood then we must specify which 4 bits in the port*/
#if (LCD_DATA_BITS_MODE == 4)

#define LCD_DB4_PIN_ID                 PIN3_ID
#define LCD_DB5_PIN_ID                 PIN4_ID
#define LCD_DB6_PIN_ID                 PIN5_ID
#define LCD_DB7_PIN_ID                 PIN6_ID

#endif


/* LCD Commands */
#define LCD_CLEAR_COMMAND                    0x01
#define LCD_GO_TO_HOME                       0x02
#define LCD_TWO_LINES_EIGHT_BITS_MODE        0x38
#define LCD_TWO_LINES_FOUR_BITS_MODE         0x28
#define LCD_TWO_LINES_FOUR_BITS_MODE_INIT1   0x33
#define LCD_TWO_LINES_FOUR_BITS_MODE_INIT2   0x32
#define LCD_CURSOR_OFF                       0x0C
#define LCD_CURSOR_ON                        0x0E
#define LCD_SET_CURSOR_LOCATION              0x80

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*description:
 * 1.set the direction of the pins using gpio driver
 * 2.set the mood of bit using the its command
 * turn off cursor
 * clear the screen
 */
void LCD_init(void );

/*description:
 * 1.set RS=1
 * 2.enable=0
 * 3.delay with tas:1ms
 * 4.enable=1
 * 5.delay with tpw:1ms
 * 6.write the command (in case of the 4_bit write
 *  it on 2 steps from MSB to LSB and deal with it as writing 2
 *   commands so disable then enable then disable again )
 * 6.enable =0
 * 7.delay 1ms
 */
void LCD_sendCommand(uint8 command);

/*description:
 * 1.set RS=1
 * 2.enable=0
 * 3.delay with tas:1ms
 * 4.enable=1
 * 5.delay with tpw:1ms
 * 6.write the character (in case of the 4_bit write
 *  it on 2 steps from MSB to LSB and deal with it as writing 2
 *   commands so disable then enable then disable again )
 * 6.enable =0
 * 7.delay 1ms
 */
void LCD_sendCharacter(uint8 character);

/*description :
 * write a string as an array of characters
 */
void LCD_displayString(const char*str);

/*description:
 * we have command that take the address of the place you want to place the cursor in
and setting the 9th bit  */
void LCD_moveCursor(uint8 row ,uint8 col);

/*description: display a string in certain row and col */
void LCD_displayStringRowColumn(uint8 row ,uint8 col, const char*str);

/*send clear screen command */
void LCD_clearScreen(void);

/*description:convert the integer to string in case of accepting an int value from
 * another source ex:sensor  */
void LCD_integerToString(uint16 data );

#endif /* LCD_H_ */
