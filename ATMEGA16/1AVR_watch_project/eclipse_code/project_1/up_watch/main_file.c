/*
 * main_file.c
 *
 *  Created on: Jul 7, 2018
 *      Author: ABDO
 */

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

char g_intrrupt=0;
char sec_flag=0;
char stop_flag=0;




ISR(TIMER0_COMP_vect)
{
	g_intrrupt+=1;
	if(g_intrrupt==4)
	{
		sec_flag=1;
		g_intrrupt=0;
	}

}
ISR(INT0_vect){
	stop_flag=1;
}

void INIT_TIMER0_CMP_MODE(int value){
	TCNT0=0;
	OCR0=value;
	TIMSK |=(1<<OCIE0);

	TCCR0 =(1<<FOC0)|(1<<WGM01)|(1<<CS02)|(1<<CS00);
}


void set_input_output_pins(){
	DDRC  = (DDRC&0XF0)|(0X0F);
	PORTC = (PORTC&0XF0);
	DDRA  = (DDRA&0XE0)|(0X1F);
	PORTC =(PORTC&0XE0);
	DDRD &=~(1<<PD2);
	PORTD|=(1<<PD2);
	GICR |=(1<<INT0);
	MCUCR|=(1<<ISC01);
	MCUCR&=~(1<<ISC00);
}

void up_clokc(char* nine , char* zero){
	if(*nine==10)
	{
		*nine=0;
		*zero+=1;
	}
}
void up_clokc_ten(char* seven , char* zero){
	if(*seven==7)
	{
		*seven=0;
		*zero+=1;
	}
}
int main()
{
	SREG  |= (1<<7);
	set_input_output_pins();
	INIT_TIMER0_CMP_MODE(250);
	char sec=0,ten_sec=0,min=0,ten_min=0,hour=0,ten_hour=0;
	while(1)
	{
		if(sec_flag)
		{
			sec+=1;
			sec_flag=0;
		}
		if (stop_flag)
		{
			sec=0;
			ten_sec=0;
			min=0;
			ten_min=0;hour=0;
			ten_hour=0;
			stop_flag=0;
		}

		up_clokc(&sec,&ten_sec);
		up_clokc_ten(&ten_sec,&min);
		up_clokc(&min,&ten_min);
		up_clokc_ten(&ten_min,&hour);
		up_clokc(&hour,&ten_hour);

		PORTA=1;
		PORTC=(PORTC&0XF0)|(sec&0X0F);
		_delay_ms(3);
		PORTA=2;
		PORTC=(PORTC&0XF0)|(ten_sec&0X0F);
		_delay_ms(3);
		PORTA=4;
		PORTC=(PORTC&0XF0)|(min&0X0F);
		_delay_ms(3);
		PORTA=8;
		PORTC=(PORTC&0XF0)|(ten_min&0X0F);
		_delay_ms(3);
		PORTA=16;
		PORTC=(PORTC&0XF0)|(hour&0X0F);
		_delay_ms(3);
		PORTA=32;
		PORTC=(PORTC&0XF0)|(ten_hour&0X0F);
		_delay_ms(3);
   }
}
