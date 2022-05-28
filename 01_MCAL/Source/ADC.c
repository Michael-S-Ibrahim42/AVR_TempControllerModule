/*                                        
*                                                       00      0  0000000  0 
*                                                       000     0     0     0 
*                                                       0 0     0     0     0 
*                                                       0  0    0     0     0 
*                                                       0   0   0     0     0 
*                                                       0   00  0     0     0 
*                                                       0    0  0     0     0 
*                                                       0     000     0     0 
*                                                       0      00     0     0                                                                      
*           Author          :   ************      Abdel Rahman Hamza Abdel Salam Motawea            **************  
*                               ************      Alaa Mohamed Abd El Qader Hussein                 **************      
*                               ************      Fatma Amr El-Sayed El-Sayed Abu El-Hassan         **************      
*                               ************      Michael Samir Barsoum Ibrahim                     **************  
*           Date            :               Sunday, 1st August, 2021                                           
*           Version         :               V01         
*/
#define F_CPU	8000000UL

#include "avr/io.h"
#include "util/delay.h"
#include "bit_handle.h"
#include "data_types.h"
#include "ADC.h"

void ADC_Init(void){
	clearBit(DDRA, PA0);
	setBit(PORTA, PA0);
	ADC_SelectR->Vref = ADC_VREF_VCC_INT;
	ADC_CtrlStatusR->prescalar = ADC_PRESC_128;
	ADC_CtrlStatusR->enable = 1;
}
u16 ADC_Read(ADC_Channel channel){
	ADC_SelectR->channel = channel;
	ADC_CtrlStatusR->start_conv = 1;
	while(ADC_CtrlStatusR->start_conv);
	return ADC_Data;
}