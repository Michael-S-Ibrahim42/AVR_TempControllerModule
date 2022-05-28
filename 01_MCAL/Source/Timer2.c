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
#include "data_types.h"
#include <avr/io.h>
#include "Timer2.h"

void Timer2_Init(void){
	DDRD |= (1<<7);
	TCCR2 = (1<<COM21) | (1<<WGM20);
}
void Timer2_Start(void){
	TCCR2 |= (1<<CS21);
}
void Timer2_DC(u8 DutyCycle){
	Timer2_Stop();
	OCR2 = (255UL*DutyCycle)/100;	
	Timer2_Start();
}
void Timer2_Stop(void){
	TCCR2 &= ~(1<<CS21);
}