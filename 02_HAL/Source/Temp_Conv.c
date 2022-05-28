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
#define F_CPU		8000000UL
#include "avr/io.h"
#include "util/delay.h"
#include "avr/interrupt.h"
#include "bit_handle.h"
#include "data_types.h"

#include "SPI.h"
#include "LCD.h"
#include "Temp_Conv.h"
#include "Timer2.h"
#include "Timer0.h"

extern volatile s16 g_Out_Voltage;
extern state g_Mode;
extern volatile s16 g_CurrentTemp;
extern s16 g_SetTemp;

void TC72_Init(void)
{
	SPI_Init(SPI_MASTER);
	clearBit(SPCR, DORD);					
	clearBit(SPCR, CPOL); 					
	setBit(SPCR, CPHA);						
	setBit(SPI_PORT,SPI_SS);				
	_delay_us(1);                           
	SPI_Transceve(TC72_CONTROL_Write_REG);	
	_delay_us(1);                           
	SPI_Transceve(TC72_CONTINUES);		    
	_delay_us(1);                           
	clearBit(SPI_PORT,SPI_SS);				
	_delay_ms(1);
}
s8 TC72_Value(void)
{
	setBit(SPI_PORT,SPI_SS);				
	_delay_us(1);                           
	SPI_Transceve(TC72_MSB_Temp_Write_REG);	
	SPI_Transceve(SPI_DUMMY);		    
	_delay_us(1);                           
	clearBit(SPI_PORT,SPI_SS);				
	_delay_ms(1);
	return SPDR ;            
}
void TC72_Stop(void)
{
	setBit(SPI_PORT,SPI_SS);				
	_delay_us(1);                           
	SPI_Transceve(TC72_CONTROL_Write_REG);	
	_delay_us(1);                           
	SPI_Transceve(TC72_SHUTDOWN);		    
	_delay_us(1);                           
	clearBit(SPI_PORT,SPI_SS);				
	_delay_ms(1);                           
}
void TC72_Call_Timer(void)
{
	g_CurrentTemp = TC72_Value();
	LCD_Idle('*',g_CurrentTemp,'*');
	if(g_CurrentTemp - g_SetTemp > 10){
		g_Mode = ERROR;
		g_Out_Voltage = 0;
		LCD_Idle(g_SetTemp,'*',g_Mode);
		Timer2_Stop();
		Timer0_Stop();
		while(1);
	}	
}


