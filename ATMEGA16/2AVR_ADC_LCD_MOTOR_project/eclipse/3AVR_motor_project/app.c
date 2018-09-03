/*
 * app.c
 * Author: ABDO
 */



#include "adc.h"
#include "lcd.h"

//external interrupt handler
ISR(INT1_vect)
{
	PORTB ^= 0x03;
}

//enable interrupts function
void INT1_Init(void)
{
	GICR  |= (1<<INT1);

    //INT1 with the raising edge
	MCUCR |= (1<<ISC11) | (1<<ISC10);
}

void Timer0_PWM_Init(unsigned char set_duty_cycle)
{

	TCNT0 = 0;

	OCR0  = set_duty_cycle;
	TCCR0 = (1<<WGM00) | (1<<WGM01) | (1<<COM01) | (1<<CS01);
}

int main(void)
{
	uint16 res_value;

	//global interrupt
	SREG  |= (1<<7);
	DDRD  &= (~(1<<PD3));
	DDRB  = DDRB | (1<<PB3);
	DDRB  |= (1<<PB0) | (1<<PB1);
	PORTB |= (1<<PB0);
	PORTB &= ~(1<<PB1);

	init_lcd();

	init_adc();

	INT1_Init();

	clearScreen();
	displayString_lcd("ADC Value = ");
    while(1)
    {
		LCD_goToRowColumn(0,12);
		res_value = readChannel_adc(0);
		LCD_intgerToString(res_value);
		Timer0_PWM_Init(res_value/4);
    }
}
