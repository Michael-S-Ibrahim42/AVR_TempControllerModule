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

#include "bit_handle.h"
#include "data_types.h"
#include "ADC.h"

extern volatile s16 g_DutyCycle;
extern volatile s16 g_Out_Voltage;
extern volatile u16 g_PWM2V_POTValue;
extern volatile s16 g_CurrentTemp;

void PWM2V_Call_Timer(void){
	g_PWM2V_POTValue = ADC_Read(ADC_CH0);
	g_PWM2V_POTValue = (g_PWM2V_POTValue * 5UL) / 1023UL;
}
