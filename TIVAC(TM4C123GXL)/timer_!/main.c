
#include "timer.h"
void SystemInit(){}
uint32_t count=0;	
static void task(void){
	if (count++ > 50*2 )
	{
		GPIO_PORTF_DATA_R ^= (1<<1) ^ (1<<2) ^ (1<<3);
		count=0;
	}
}

void Init_PortF(){
  char dumy ;
	SYSCTL_RCGC2_R |= (1<<5);
	dumy=1;
	GPIO_PORTF_LOCK_R = 0X4C4F434B;
	GPIO_PORTF_CR_R  = (1<<4) | (1<<3) | (1<<2) | (1<<1) | (1<<0);
	GPIO_PORTF_PCTL_R = 0X00;
	GPIO_PORTF_DIR_R |= (1<<1) | (1<<2) | (1<<3);
	GPIO_PORTF_DIR_R &= ~(1<<0);
	GPIO_PORTF_DIR_R &= ~(1<<4);
	GPIO_PORTF_PUR_R |= (1<<4) | (1<<0);
	GPIO_PORTF_DEN_R |= (1<<1) | (1<<2) | (1<<3);
	GPIO_PORTF_DEN_R =0xFF;
}

int main(void){
	Init_PortF();
	GPIO_PORTF_DATA_R |= (1<<2);
	timer1_set_call_cack(&task);
	timer1_init(0XFFFF);
	while(1){}
}