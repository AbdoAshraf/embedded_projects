#include "tm4c123gh6pm.h"
#include "stdint.h"

/**************************************************************
*             function decleration                            *
***************************************************************/

void Uart0_init(void);
void Uart0_Send_Byte(uint8_t data);
uint8_t Uart0_recive_byte(void);
void Uart0_Send_string(char *S);





