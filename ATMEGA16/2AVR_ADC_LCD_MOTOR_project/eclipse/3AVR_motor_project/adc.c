/*
 * adc.c
 *
 * Author: ABDO
 */

#include "adc.h"

void init_adc(void)
{
	ADMUX = 0;
	ADCSRA = (1<<ADEN) | (1<<ADPS1) | (1<<ADPS0);
}

uint16 readChannel_adc(uint8 channel_num)
{
	channel_num &= 0x07;
	ADMUX &= 0xE0;
	ADMUX = ADMUX | channel_num;
	SET_BIT(ADCSRA,ADSC);
	while(BIT_IS_CLEAR(ADCSRA,ADIF));
	SET_BIT(ADCSRA,ADIF);
	return ADC;
}
