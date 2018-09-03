/*
 * mc2.c
 *
 *  Created on: Aug 2, 2018
 *      Author: ABDO
 */

#include "spi.h"
#include "lcd.h"

int main(void)
{
	uint8 str[20];
	init_lcd();
	/* Initialize Salve SPI */
	SPI_initSlave();
	/* Receive String from MC1 */
	SPI_ReceiveString(str);
	/* Display the received string on the LCD display */
	displayString_lcd(str);
    while(1)
    {

    }
}


