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
#include "avr/io.h"
#include "avr/interrupt.h"
#include "Timer0.h"

volatile static u32 overflows = 0;
volatile static u32 PeriodicCheck = 0;
volatile static u32 calcOverflows = 0;
void (*volatile TC_Temp)(void);
void (*volatile PWM2V_Temp)(void);
void (*volatile PWM2V_DC)(void);

void Timer0_Init(void){
	Timer0_Stop();
	clearBit(TCCR0,WGM00);
	setBit(TCCR0,WGM01);
	OCR0 = 39;
	Timer0_Start();
}
void Timer0_Start(void){
	setBit(TCCR0,CS00);
	setBit(TCCR0,CS02);
	clearBit(TCCR0,CS01);
}
void Timer0_Stop(void){
	clearBits(TCCR0,((1<<CS00)|(1<<CS01)|(1<<CS02)));
}
void Timer0_Delay(u16 Time_MS){	
	Timer0_Stop();
	overflows = 0;
	Time_MS /= 5;
	Timer0_Start();
	while(overflows < Time_MS){
		while((TIFR&(1<<TOV0)) == 0);
		TIFR = (1<<TOV0);
		overflows++;
	}
	Timer0_Stop();
}
void Timer0_PeriodicRead(void){
	Timer0_Stop();
	overflows = 0;
	calcOverflows = 20;
	setBit(TIMSK,OCIE0);
	sei();
	Timer0_Start();	
}
void Timer0_CallBack(void (*pfTemp)(void), void (*pfPOT)(void)){
	TC_Temp = pfTemp;
	PWM2V_Temp = pfPOT;
}
ISR(TIMER0_COMP_vect){
	overflows++;
	if(overflows == calcOverflows){
		overflows = 0;
		PeriodicCheck++;
		if(PeriodicCheck % 2 == 0){
			(*TC_Temp)();
		}
		if(PeriodicCheck % 5 == 0){
			(*PWM2V_Temp)();
		}
		if(PeriodicCheck == 10){
			PeriodicCheck = 0;
		}
	}
}