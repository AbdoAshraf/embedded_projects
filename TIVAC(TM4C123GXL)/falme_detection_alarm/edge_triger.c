#include "edge_triger.h"
void (*portf_call_back)(void) ;
void (*portb_call_back)(void) ;
void  GPIOF_Handler(void){
	 if(GPIO_PORTF_RIS_R&0x10){  // poll PF4
    GPIO_PORTF_ICR_R = 0x10;
    portf_call_back();
  }
}

void  GPIOB_Handler(void){
	 if(GPIO_PORTB_RIS_R&0x10){  // poll PB4
    GPIO_PORTB_ICR_R = 0x10;
    portb_call_back();
  }
}

void Init_PortF_triger(uint8_t bin_num){
	//activate clock for Port F 
	SYSCTL_RCGCGPIO_R |= (1<<5);  
  // unlock GPIO Port F
  //note that portf must be unlocked befor uesing	
  GPIO_PORTF_LOCK_R = 0x4C4F434B; 
	// commit the specified bin 
  GPIO_PORTF_CR_R  |= (1<<bin_num);
  GPIO_PORTF_DIR_R &= ~(1<<bin_num);         
  GPIO_PORTF_DEN_R |= (1<<bin_num);
  // pullups on 	
  GPIO_PORTF_PUR_R |= 0x11;     
  GPIO_PORTF_IS_R  &= ~(1<<bin_num);       
  GPIO_PORTF_IBE_R &= ~(1<<bin_num);      
  GPIO_PORTF_IEV_R &= ~(1<<bin_num);     
  GPIO_PORTF_ICR_R = (1<<bin_num);        
  GPIO_PORTF_IM_R |= (1<<bin_num);  
 // NVIC_PRI7_R = (NVIC_PRI7_R&0xFF00FFFF)|0x00A00000;	
  NVIC_EN0_R = 0x40000000;
}
void portf_set_call_back(void (*fun)(void)){
	portf_call_back = fun;
}

void Init_PortB_triger(uint8_t bin_num){
	//activate clock for Port B 
	SYSCTL_RCGCGPIO_R |= (1<<1);  
  GPIO_PORTB_DIR_R &= ~(1<<bin_num);         
  GPIO_PORTB_DEN_R |= (1<<bin_num);
  // pullups on 	/*
	//GPIO_PORTB_PUR_R |= (1<<bin_num);     
  GPIO_PORTB_IS_R  &= ~(1<<bin_num);       
  GPIO_PORTB_IBE_R &= ~(1<<bin_num);      
  GPIO_PORTB_IEV_R |=  (1<<bin_num);     
  GPIO_PORTB_ICR_R = (1<<bin_num);        
  GPIO_PORTB_IM_R |= (1<<bin_num);      
  NVIC_EN0_R = (1<<1);/**/
}

void portb_set_call_back(void (*fun)(void)){
	portb_call_back = fun;
}

