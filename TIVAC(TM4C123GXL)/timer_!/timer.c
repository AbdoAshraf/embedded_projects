#include "timer.h"
void (*task)(void) ;

void TIMER1A_Handler(){
	TIMER1_ICR_R |= (1<<0);
	task();
}

// Outputs: none
/*
void Timer1_Init(void(*task)(void), uint32_t period){
  SYSCTL_RCGCTIMER_R |= 0x02;   // 0) activate TIMER1
  PeriodicTask = task;          // user function
  TIMER1_CTL_R = 0x00000000;    // 1) disable TIMER1A during setup
  TIMER1_CFG_R = 0x00000000;    // 2) configure for 32-bit mode
  TIMER1_TAMR_R = 0x00000002;   // 3) configure for periodic mode, default down-count settings
  TIMER1_TAILR_R = period-1;    // 4) reload value
  TIMER1_TAPR_R = 0;            // 5) bus clock resolution
  TIMER1_ICR_R = 0x00000001;    // 6) clear TIMER1A timeout flag
  TIMER1_IMR_R = 0x00000001;    // 7) arm timeout interrupt
  NVIC_PRI5_R = (NVIC_PRI5_R&0xFFFF00FF)|0x00008000; // 8) priority 4
// interrupts enabled in the main program after all devices initialized
// vector number 37, interrupt number 21
  NVIC_EN0_R = 1<<21;           // 9) enable IRQ 21 in NVIC
  TIMER1_CTL_R = 0x00000001;    // 10) enable TIMER1A
}
/**/
void timer1_init(uint32_t load){
	SYSCTL_RCGCTIMER_R |= (1<<1);
	TIMER1_CTL_R &= ~(1<<0);
	TIMER1_CFG_R = 0X04;
	TIMER1_TAMR_R |= (1<<1);
	TIMER1_TAILR_R = load-1;
	TIMER1_IMR_R |= (1<<0);
	TIMER1_ICR_R |= (1<<0);//
	NVIC_EN0_R |= (1<<21);
	TIMER1_CTL_R |=(1<<0);
	__enable_irq();
}

void timer1_set_call_cack(void (*call_back)(void)){
	task = call_back;
	
}