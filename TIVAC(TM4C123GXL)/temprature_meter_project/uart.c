#include "uart.h"

void Uart0_init(void){
	

	/*****************************************************************
	                        Configeur UART
	******************************************************************/
	//Enable the UART module using the RCGCUART register (see page 344)
	SYSCTL_RCGCUART_R |= (1<<0);
	//Enable the clock to the appropriate GPIO module via the RCGCGPIO register (see page 340).
	//To find out which GPIO port to enable, refer to Table 23-5 on page 1351.
	SYSCTL_RCGCGPIO_R |= (1<<0);
	/*****************************************************************
	                        Configeur Port A
	******************************************************************/
	SYSCTL_RCGC0_R |= (1<<0);
	GPIO_PORTA_AFSEL_R |= (1<<0) | (1<<1);
	GPIO_PORTA_AMSEL_R &= ~(1<<0);
	GPIO_PORTA_AMSEL_R &= ~(1<<1);
	GPIO_PORTA_DEN_R |= (1<<0) | (1<<1);
	GPIO_PORTA_PCTL_R |= (1<<0) | (1<<4);
	
	/*****************************************************************
	                        Configeur BAUD RATE 
	******************************************************************/
	 //Disable the UART by clearing the UARTEN bit in the UARTCTL register
	 UART0_CTL_R &= ~(1<<0);
	 // Write the integer portion of the BRD to the UARTIBRD register.
	 UART0_IBRD_R = 104;
	 //Write the fractional portion of the BRD to the UARTFBRD register.
	 UART0_FBRD_R = 11;
	 //Write the desired serial parameters to the UARTLCRH register
	 UART0_LCRH_R = (0X03<<5);
	 UART0_LCRH_R |=(1<<4);
	 //Configure the UART clock source by writing to the UARTCC register.
	 UART0_CC_R  =0X0;
	 //Enable the UART by setting the UARTEN bit in the UARTCTL register
	 UART0_CTL_R = (1<<9) | (1<<8) | (1<<0);
}

void Uart0_Send_Byte(uint8_t data){
	while ((UART0_FR_R &(1<<5))) {}
   UART0_DR_R=data;		
}

uint8_t Uart0_recive_byte(void){
	while ((UART0_FR_R & (1<<4))) {}
		return (uint8_t)(UART0_DR_R & 0X00FF);
}
void Uart0_Send_string(char *S){
	uint8_t i=0;
	while(S[i] != '\0' )
		Uart0_Send_Byte(S[i++]);
}


