#include "pwm.h"


void PWM0A_Init(uint16_t period, uint16_t duty){
	 // activate PWM0
	SYSCTL_RCGCPWM_R |= 0x01;            
	//Enable the PWM clock by writing a value of 0x0010.0000 to the RCGC0 register in the System
	//Control module (see page 456).
	 SYSCTL_RCGC0_R |= (1<<20);
	//Enable the clock to the appropriate GPIO module via the RCGC2 register in the System Control
	//module (see page 464).
	 SYSCTL_RCGC2_R |= (1<<1) ;
	while((SYSCTL_PRGPIO_R&0x02) == 0){};
	//In the GPIO module, enable the appropriate pins for their alternate function using the
	//GPIOAFSEL register. To determine which GPIOs to configure, see Table 23-4 on page 1344.
	 GPIO_PORTB_AFSEL_R |= (1<<6) ;
	//Configure the PMCn fields in the GPIOPCTL register to assign the PWM signals to the appropriate
	//pins (see page 688 and Table 23-5 on page 1351).
	 GPIO_PORTB_PCTL_R |= (4<<24) ;
	// disable analog functionality on PB6	
	 GPIO_PORTB_AMSEL_R &= ~(1<<6);   
  // enable digital I/O on PB6		
   GPIO_PORTB_DEN_R |= (1<<6);             

  //  use PWM divider		
   SYSCTL_RCC_R = 0x00100000 |           
      (SYSCTL_RCC_R & (~0x000E0000)); 
  //  re-loading down-counting mode		
   PWM0_0_CTL_R = 0;    
  // low on LOAD, high on CMPA down		
   PWM0_0_GENA_R = 0xC8; 
  // PB6 goes low on LOAD
  // PB6 goes high on CMPA down
   PWM0_0_LOAD_R = period - 1;          
   PWM0_0_CMPA_R = duty - 1;             
   PWM0_0_CTL_R |= 0x00000001;
	// enable PB6/M0PWM0	
   PWM0_ENABLE_R |= 0x00000001;          
}

// change duty cycle of PB6
void PWM0A_Duty(uint16_t duty){
  PWM0_0_CMPA_R = duty - 1;          
}
void PWM0A_disable(void){
	PWM0_ENABLE_R &=~ 0x00000001; 
	//SYSCTL_RCGCPWM_R = 0x01;  
}

void PWM0A_enable(void){
	PWM0_ENABLE_R |= 0x00000001; 
	//SYSCTL_RCGCPWM_R = 0x01;  
}





