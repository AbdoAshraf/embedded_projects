#include "C:/Keil/TM4C123Valvanoware/inc/tm4c123gh6pm.h"
#include "stdint.h" 


void Init_PortF_triger(uint8_t bin_num);
void Init_PortB_triger(uint8_t bin_num);
void portf_set_call_back(void (*fun)(void));
void portb_set_call_back(void (*fun)(void));