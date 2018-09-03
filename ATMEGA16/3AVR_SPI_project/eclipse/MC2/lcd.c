/*
 * lcd.c
 *
 *  Created on: Aug 2, 2018
 *      Author: ABDO
 */

#include "lcd.h"


void init_lcd(void)
{
	LCD_DATA_PORT_DIR = 0xFF;
	LCD_CTRL_PORT_DIR |= (1<<E) | (1<<RS) | (1<<RW);

	sendCommand_lcd(TWO_LINE_LCD_Eight_BIT_MODE);

	sendCommand_lcd(CURSOR_OFF);

	sendCommand_lcd(CLEAR_COMMAND);
}

void sendCommand_lcd(uint8 command)
{
	CLEAR_BIT(LCD_CTRL_PORT,RS);
	CLEAR_BIT(LCD_CTRL_PORT,RW);
	_delay_ms(1);
	SET_BIT(LCD_CTRL_PORT,E);
	_delay_ms(1);
	LCD_DATA_PORT = command;
	_delay_ms(1);
	CLEAR_BIT(LCD_CTRL_PORT,E);
	_delay_ms(1);
}

void displayCharacter_lcd(uint8 data)
{
	SET_BIT(LCD_CTRL_PORT,RS);
	CLEAR_BIT(LCD_CTRL_PORT,RW);
	_delay_ms(1);
	SET_BIT(LCD_CTRL_PORT,E);
	_delay_ms(1);
	LCD_DATA_PORT = data;
	_delay_ms(1);
	CLEAR_BIT(LCD_CTRL_PORT,E);
	_delay_ms(1);
}

void displayString_lcd(const char *Str)
{
	uint8 i = 0;
	while(Str[i] != '\0')
	{
		displayCharacter_lcd(Str[i]);
		i++;
	}

}

void LCD_goToRowColumn(uint8 row,uint8 col)
{
	uint8 Address;


	switch(row)
	{
		case 0:
				Address=col;
				break;
		case 1:
				Address=col+0x40;
				break;
		case 2:
				Address=col+0x10;
				break;
		case 3:
				Address=col+0x50;
				break;
	}

	sendCommand_lcd(Address | SET_CURSOR_LOCATION);
}

void displayStringRowColumn(uint8 row,uint8 col,const char *Str)
{
	LCD_goToRowColumn(row,col);
	displayString_lcd(Str);
}

void LCD_intgerToString(int data)
{
   char buff[16];
   itoa(data,buff,10);
   displayString_lcd(buff);
}

void clearScreen(void)
{
	sendCommand_lcd(CLEAR_COMMAND);
}




