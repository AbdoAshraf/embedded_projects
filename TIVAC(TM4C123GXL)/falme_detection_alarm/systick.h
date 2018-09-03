

#include "C:/Keil/TM4C123Valvanoware/inc/tm4c123gh6pm.h"
#include "stdint.h"


void Systick_Init(void);

void Systick_Start(uint32_t load);

void Systick_Stop(void);

void Systick_Set_Call_Back( void (*task)(void));