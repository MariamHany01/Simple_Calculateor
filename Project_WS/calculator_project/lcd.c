/*
 * lcd.c
 *
 *  Created on: 4 Oct 2023
 *      Author: maria
 */
#include<util/delay.h>
#include"lcd.h"
#include "gpio.h"
#include"common_macros.h"/*for get bit macro*/

/**************************************************************************************************
                       functions definition
 *************************************************************************************************/

/*description:
 * 1.set the direction of the pins using gpio driver
 * 2.set the mood of bit using the its command
 * turn off cursor
 * clear the screen
 */
void LCD_init(void ){
	/* set the direction of main pins (enable ,RS)*/
	GPIO_setupPinDirection(LCD_RS_PORT_ID, LCD_RS_PIN_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_E_PORT_ID, LCD_E_PIN_ID, PIN_OUTPUT);

	_delay_ms(20);
	/*configuration of DB pins direction based on the mood */
	#if (LCD_DATA_BITS_MODE==4)
	GPIO_setupPinDirection(LCD_DB_PORT_ID,LCD_DB4_PIN_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_DB_PORT_ID,LCD_DB5_PIN_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_DB_PORT_ID,LCD_DB6_PIN_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_DB_PORT_ID,LCD_DB7_PIN_ID, PIN_OUTPUT);

	/* Send for 4 bit initialization of LCD  */
	LCD_sendCommand(LCD_TWO_LINES_FOUR_BITS_MODE_INIT1);
	LCD_sendCommand(LCD_TWO_LINES_FOUR_BITS_MODE_INIT2);

	LCD_sendCommand(LCD_TWO_LINES_FOUR_BITS_MODE );

	#elif(LCD_DATA_BITS_MODE==8)
	GPIO_setupPortDirection(LCD_DB_PORT_ID, PORT_OUTPUT);
	LCD_sendCommand(LCD_TWO_LINES_EIGHT_BITS_MODE  );

	#endif

	LCD_sendCommand(LCD_CURSOR_OFF); /* cursor off */
	LCD_sendCommand(LCD_CLEAR_COMMAND); /* clear LCD at the beginning */
}

/*description:
 * 1.set RS=0
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
void LCD_sendCommand(uint8 command){
	GPIO_writePin(LCD_RS_PORT_ID, LCD_RS_PIN_ID, LOGIC_LOW);/*RS=1*/
	GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_LOW);/*ENABLE=0*/

	_delay_ms(1);/*Tas delay time */

	GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_HIGH);/*ENABLE=1*/

	_delay_ms(1);/*Tpw delay time */

/* configurations to write command on 2 steps in case of 4 bits mood */
	#if(LCD_DATA_BITS_MODE==4)
	/*take the MSB (4_bits) */
	GPIO_writePin(LCD_DB_PORT_ID,LCD_DB4_PIN_ID ,READ_PIN(command,4));
	GPIO_writePin(LCD_DB_PORT_ID,LCD_DB5_PIN_ID ,READ_PIN(command,5));
	GPIO_writePin(LCD_DB_PORT_ID,LCD_DB6_PIN_ID ,READ_PIN(command,6));
	GPIO_writePin(LCD_DB_PORT_ID,LCD_DB7_PIN_ID ,READ_PIN(command,7));

	_delay_ms(1); /* delay for processing Tdsw = 100ns */

	GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_LOW);/*ENABLE=0*/

	_delay_ms(1);/*Tas delay time */

	GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_HIGH);/*ENABLE=1*/

	_delay_ms(1);/*Tpw delay time */

	GPIO_writePin(LCD_DB_PORT_ID,LCD_DB4_PIN_ID ,READ_PIN(command,0));
	GPIO_writePin(LCD_DB_PORT_ID,LCD_DB5_PIN_ID ,READ_PIN(command,1));
	GPIO_writePin(LCD_DB_PORT_ID,LCD_DB6_PIN_ID ,READ_PIN(command,2));
	GPIO_writePin(LCD_DB_PORT_ID,LCD_DB7_PIN_ID ,READ_PIN(command,3));

	_delay_ms(1); /* delay for processing Tdsw = 100ns */

	GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_LOW);/*ENABLE=0*/
	_delay_ms(1); /* delay for processing Th = 13ns */

	#elif(LCD_DATA_BITS_MODE==8)

	GPIO_writePort(LCD_DB_PORT_ID,command); /* out the required command to the data bus D0 --> D7 */
	_delay_ms(1); /* delay for processing Tdsw = 100ns */
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_LOW); /* Disable LCD E=0 */
	_delay_ms(1); /* delay for processing Th = 13ns */
	#endif
}

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
void LCD_sendCharacter(uint8 command){
	GPIO_writePin(LCD_RS_PORT_ID, LCD_RS_PIN_ID, LOGIC_HIGH);/*RS=1*/
	GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_LOW);/*ENABLE=0*/

	_delay_ms(1);/*Tas delay time */

	GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_HIGH);/*ENABLE=1*/

	_delay_ms(1);/*Tpw delay time */

/* configurations to write command on 2 steps in case of 4 bits mood */
	#if(LCD_DATA_BITS_MODE==4)
	/*take the MSB (4_bits) */
	GPIO_writePin(LCD_DB_PORT_ID,LCD_DB4_PIN_ID ,READ_PIN(command,4));
	GPIO_writePin(LCD_DB_PORT_ID,LCD_DB5_PIN_ID ,READ_PIN(command,5));
	GPIO_writePin(LCD_DB_PORT_ID,LCD_DB6_PIN_ID ,READ_PIN(command,6));
	GPIO_writePin(LCD_DB_PORT_ID,LCD_DB7_PIN_ID ,READ_PIN(command,7));

	_delay_ms(1); /* delay for processing Tdsw = 100ns */

	GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_LOW);/*ENABLE=0*/

	_delay_ms(1);/*Tas delay time */

	GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_HIGH);/*ENABLE=1*/

	_delay_ms(1);/*Tpw delay time */

	GPIO_writePin(LCD_DB_PORT_ID,LCD_DB4_PIN_ID ,READ_PIN(command,0));
	GPIO_writePin(LCD_DB_PORT_ID,LCD_DB5_PIN_ID ,READ_PIN(command,1));
	GPIO_writePin(LCD_DB_PORT_ID,LCD_DB6_PIN_ID ,READ_PIN(command,2));
	GPIO_writePin(LCD_DB_PORT_ID,LCD_DB7_PIN_ID ,READ_PIN(command,3));

	_delay_ms(1); /* delay for processing Tdsw = 100ns */

	GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_LOW);/*ENABLE=0*/
	_delay_ms(1); /* delay for processing Th = 13ns */

	#elif(LCD_DATA_BITS_MODE==8)

	GPIO_writePort(LCD_DB_PORT_ID,command); /* out the required command to the data bus D0 --> D7 */
	_delay_ms(1); /* delay for processing Tdsw = 100ns */
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_LOW); /* Disable LCD E=0 */
	_delay_ms(1); /* delay for processing Th = 13ns */
	#endif
}

/*description :
 * write a string as an array of characters
 */
void LCD_displayString(const char*str){
	uint8 i=0;
	while (str[i]!='\0'){
		LCD_sendCharacter(str[i]);
		i++;
	}
}

/*description:
 * we have command that take the address of the place you want to place the cursor in
and setting the 9th bit  */
void LCD_moveCursor(uint8 row ,uint8 col){
	uint8 adress ;
	switch (row){
	case 0:
		adress=col;
		break;
	case 1:
		adress=0X40+col;
		break;
	case 2:
		adress=0X10+col;
		break;
	case 3:
		adress=0X50+col;
		break;
	}
	LCD_sendCommand((LCD_SET_CURSOR_LOCATION)|adress);
}
/*description: display a string in certain row and col */
void LCD_displayStringRowColumn(uint8 row ,uint8 col, const char*str){
	LCD_moveCursor(row,col);
	LCD_displayString(str);
}

/*send clear screen command */
void LCD_clearScreen(void){
	LCD_sendCommand(LCD_CLEAR_COMMAND);
}

/*description:convert the integer to string in case of accepting an int value from
 * another source ex:sensor  */
void LCD_integerToString(uint16 data ){
	/*usng int to asci fn itoa which get the asci of each digit in an intger number
	 * and store it in an array of characters
	 */
	uint8 buff[16]; /*the array we store in the asci ,16->digits of int */
	   itoa(data,buff,10); /* Use itoa C function to convert the data to its corresponding ASCII value, 10 for decimal */
	   LCD_displayString(buff); /* Display the string */
}
