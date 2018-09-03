/*
 * adc.h
 *
 *
 *  Author: ABDO
 */

#ifndef ADC_H_
#define ADC_H_

#include "micro_config.h"
#include "std_types.h"
#include "common_macros.h"


void ADC_Init(void);


uint16 ADC_readChannel(uint8 channel_num);

#endif /* ADC_H_ */
