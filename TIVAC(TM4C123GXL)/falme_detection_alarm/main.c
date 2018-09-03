#include "pwm.h" 
#include "edge_triger.h"
#include "systick.h"

void SystemInit(){}
// flame flag wihich changing by the call back triger function 
int8_t flame_flag=0 ;
// safe flag which changing by the call back switch triger function.
int8_t safe=0;
	
	
void portf_triger_task(void){
	safe=1;
}

void portb_triger_task(void){
  flame_flag=1;	
}
// Systick call back function
void alarm(void){
	static int8_t tone=0;
	static uint8_t count;
	PWM0A_Duty(30000);
	if (count++ == 20 )
	{
	  GPIO_PORTB_DATA_R ^= (1<<2);
		GPIO_PORTB_DATA_R ^= (1<<3);
		count=0;
		if(tone==0)
		{
			tone=1;
			PWM0A_Duty(40000);
		}
	}
}

// function that intialize the leds
void led_init(){
	SYSCTL_RCGCGPIO_R |= (1<<1);  
	GPIO_PORTB_DIR_R |= (1<<2) | (1<<3);
	GPIO_PORTB_DEN_R |= (1<<2)|(1<<3);
}

	

int main(void){
	led_init();
	Systick_Init();
	PWM0A_Init(60000, 30000);
	Systick_Set_Call_Back(&alarm);
	// intailze interrupt triger of PF4.
	Init_PortF_triger(4);
	// intailze interrupt triger of PB4.
	Init_PortB_triger(4);
	// set call back function of pB4
	portb_set_call_back(&portb_triger_task);
	// set call back function of pB4
	portf_set_call_back(&portf_triger_task);
	
	__enable_irq();
	while (1){
		if (flame_flag == 1 )
		{
			flame_flag=0;
			GPIO_PORTB_DATA_R |=(1<<2);
			PWM0A_enable();
			Systick_Start(0XFFFF);
		}
		if (safe == 1)
		{
			safe=0;
			Systick_Stop();
			GPIO_PORTB_DATA_R &=~(1<<3);
			GPIO_PORTB_DATA_R &=~(1<<2);
			PWM0A_Duty(0);
			
		}
	}
}