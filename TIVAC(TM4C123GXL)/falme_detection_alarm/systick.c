
#include "systick.h"
void (*systick_task)(void);

static int count =0 ;
void SysTick_Handler(void) {
	systick_task();
}
void Systick_Init(void){
	NVIC_ST_CTRL_R &= ~(1<<0);
	NVIC_ST_RELOAD_R  = 0 ;
	NVIC_ST_CURRENT_R = 0 ;
	NVIC_ST_CTRL_R |= (1<<2) | (1<<1);;	
}


void Systick_Start(uint32_t load){
	NVIC_ST_RELOAD_R = load-1;
	NVIC_ST_CTRL_R |=(1<<0);	
}
void Systick_Stop(void){
	NVIC_ST_CTRL_R &= ~(1<<0);
}

void Systick_Set_Call_Back( void (*task)(void)){
	systick_task=task;
}


