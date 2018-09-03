#include "adc.h"
#include "uart.h"
#include <stdio.h>


void SystemInit(){}
	

int main(void){
	volatile uint16_t conv_value = 0;
	Uart0_init();
	ADC1_Init();
	ADC1_Sampler3_Init();
	while (1){
		if (Uart0_recive_byte()=='r')
		{
			uint16_t temp = (ADC1_FIFO3_value()*100*3)/(4096); //(temp*150*5)/(1023*1.5)
			char buffer[16] ;
			sprintf(buffer,"%d",temp);
			Uart0_Send_Byte('\n');
			Uart0_Send_string("temp=");
			Uart0_Send_string(buffer);
			conv_value=ADC1_FIFO3_value();
		}	
	}
}