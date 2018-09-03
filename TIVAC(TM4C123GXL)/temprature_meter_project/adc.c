#include "adc.h"
//void SystemInit(){}

uint8_t ADC_value=0 ;

void ADC1SS3_Handler(){
	ADC1_ISC_R |= (1<<3);
	ADC_value = ADC1_SSFIFO3_R;
}

void ADC1_Init(void){
	// Enable the ADC clock using the RCGCADC register (see page 352).
	SYSCTL_RCGCADC_R |= (1<<1);
	//Enable the clock to the appropriate GPIO modules via the RCGCGPIO register (see page 340).
	SYSCTL_RCGC2_R |= (1<<4);
	// Set the GPIO AFSEL bits for the ADC input pins (see page 671). To determine which GPIOs to
	//configure, see Table 23-4 on page 1344.
	GPIO_PORTE_AFSEL_R |= (1<<2);
	
	//Configure the AINx signals to be analog inputs by clearing the corresponding DEN bit in the
	//GPIO Digital Enable (GPIODEN) register (see page 682).
	GPIO_PORTE_DEN_R &= ~(1<<2);
	
	//Disable the analog isolation circuit for all ADC input pins that are to be used by writing a 1 to
	//the appropriate bits of the GPIOAMSEL register (see page 687) in the associated GPIO block.
	GPIO_PORTE_AMSEL_R |= (1<<2);
}

void ADC1_Sampler3_Init(void){
	//Ensure that the sample sequencer is disabled by clearing the corresponding ASENn bit in the
	//ADCACTSS register. Programming of the sample sequencers is allowed without having them
	//enabled. Disabling the sequencer during programming prevents erroneous execution if a trigger
	//event were to occur during the configuration process.
	ADC1_ACTSS_R &= ~(1<<3);
	
	//Configure the trigger event for the sample sequencer in the ADCEMUX register.
	ADC1_EMUX_R |= (0XF<<12);
	
	//For each sample in the sample sequence, configure the corresponding input source in the
	//ADCSSMUXn register.
	ADC1_SSMUX3_R  = 1 ;
	
	//For each sample in the sample sequence, configure the sample control bits in the corresponding
	//nibble in the ADCSSCTLn register. When programming the last nibble, ensure that the END bit
	//is set. Failure to set the END bit causes unpredictable behavior.
	ADC1_SSCTL3_R = (1<<2) | (1<<1);
	//Set avrage of sampling 
  ADC1_SAC_R=0X6;
	//If interrupts are to be used, set the corresponding MASK bit in the ADCIM register.
	ADC1_IM_R |=(1<<3);
	//Clear itrrupt ASC flag .
	ADC1_ISC_R |= (1<<3);
	// Enable ADC1(SS30 iterrupt.
	NVIC_EN1_R |= (1<<19);
	// Enable the SS3 module .
	ADC1_ACTSS_R |= (1<<3);
	//
		__enable_irq();
}

uint16_t ADC1_FIFO3_value(void){
	return  ADC_value;
}


/**
int main(){
	 ADC1_Init();
	 Sampler_Init();
}/****/