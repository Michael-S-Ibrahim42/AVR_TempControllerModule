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
#define  F_CPU		8000000
#include "data_types.h"
#include "bit_handle.h"
#include <avr/io.h>
#include <util/delay.h>
#include "LCD.h"
#include "Temp_Conv.h"
#include "Timer0.h"
#include "Timer2.h"
#include "Keypad.h"
#include "ADC.h"
#include "PWM2V.h"

state g_Mode;
volatile s16 g_CurrentTemp = 0;
volatile s16 g_DutyCycle = 0;
volatile s16 g_Out_Voltage = 0;
volatile u16 g_PWM2V_POTValue = 5;
volatile s16 g_SetTemp = 25;

int main(void)
{
	s8 loc_KeypadInput = 0;
	g_Mode = STANDBY;
	setBit(DDRD, PD7); // PWM Output Pin
	LCD_Init();
	Timer0_Init();
	Timer2_Init();
	TC72_Init();
	ADC_Init();
	Timer0_CallBack(TC72_Call_Timer, PWM2V_Call_Timer);
	LCD_Welcome();
	LCD_Idle(g_SetTemp, g_CurrentTemp,g_Mode); 
	Timer0_Delay(2000);
	while(KeyPad_GetPressedKey() != '#');
	g_Mode = OPERATION;
	LCD_Idle(g_SetTemp, g_CurrentTemp, g_Mode);	
	Timer0_PeriodicRead();
	Timer2_Start();
    g_CurrentTemp = TC72_Value();
    if((g_CurrentTemp - g_SetTemp) > 10){
        g_Mode = ERROR;
        g_Out_Voltage = 0;
        LCD_Idle(g_SetTemp,'*',g_Mode);
        Timer2_Stop();
        Timer0_Stop();
        while(1);//Infinite Loop
    }
    else if(((g_SetTemp - g_CurrentTemp) <= 5) && ((g_CurrentTemp - g_SetTemp) <= 5)){
        g_Mode = NORMAL;
        g_Out_Voltage = 0;
        LCD_Idle(g_SetTemp,'*',g_Mode);
    }
    else{
        g_Mode = OPERATION;
        LCD_Idle(g_SetTemp,'*',g_Mode);
        if(g_SetTemp > g_CurrentTemp){
            g_Out_Voltage = (((g_SetTemp - g_CurrentTemp)*5UL) / 100UL);
        }
        else{
            g_Out_Voltage = 0;
        }
    }
	while (1)
	{
		g_DutyCycle = ((((g_PWM2V_POTValue*2UL)/10UL) * g_Out_Voltage) * 100UL) / 10UL;
		Timer2_DC(g_DutyCycle);
		loc_KeypadInput = KeyPad_GetPressedKey();		
		if(loc_KeypadInput == '#'){
			if(g_Mode == OPERATION){
				g_Mode = STANDBY;
				Timer2_Stop();
				Timer0_Stop();
				LCD_Idle(g_SetTemp,0,g_Mode);
				while(KeyPad_GetPressedKey() != '#');
				g_Mode = OPERATION;
				LCD_Idle(g_SetTemp, 0, g_Mode);
				Timer0_PeriodicRead();
				Timer2_Start();
			}
		}
		else{
			loc_KeypadInput = (loc_KeypadInput*10) + KeyPad_GetPressedKey();
			g_SetTemp = loc_KeypadInput;
			LCD_Idle(g_SetTemp,'*',g_Mode);
			if((g_CurrentTemp - g_SetTemp) > 10){
				g_Mode = ERROR;
				g_Out_Voltage = 0;
				LCD_Idle(g_SetTemp,'*',g_Mode);
				Timer2_Stop(); 
				Timer0_Stop(); 
				while(1);//Infinite Loop		
			}
			else if(((g_SetTemp - g_CurrentTemp) <= 5) && ((g_CurrentTemp - g_SetTemp) <= 5)){
				g_Mode = NORMAL;
				g_Out_Voltage = 0;
				LCD_Idle(g_SetTemp,'*',g_Mode);
			}
			else{
				g_Mode = OPERATION;
				LCD_Idle(g_SetTemp,'*',g_Mode);
				if(g_SetTemp > g_CurrentTemp){
					g_Out_Voltage = (((g_SetTemp - g_CurrentTemp)*5UL) / 100UL);
				}
				else{
					g_Out_Voltage = 0;
				}				
			}
		}
	}
}