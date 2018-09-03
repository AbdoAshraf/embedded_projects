#include "C:/Keil/TM4C123Valvanoware/inc/tm4c123gh6pm.h"
#include "stdint.h"

void timer1_init(uint32_t load);

void timer1_disable(void);

void timer1_set_call_cack(void (*call_back)(void));
