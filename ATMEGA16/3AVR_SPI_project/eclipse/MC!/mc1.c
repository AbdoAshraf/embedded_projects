/*
 * mc1.c
 *
 *  Created on: Aug 2, 2018
 *      Author: ABDO
 */

#include "spi.h"

int main(void)
{
	SPI_initMaster(); /* Master Initialization */
	_delay_ms(50); /* delay until MC2 finish its initialization task */
	SPI_SendString("I am Micro1#");
    while(1)
    {

    }
}

