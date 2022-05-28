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
#include "bit_handle.h"
#include "data_types.h"
#include "Timer0.h"
#include "LCD.h"
#include "string.h"

static void LCD_SendData(u8 u8Data);
static void LCD_GoToXY(u8 row, u8 col);
static void LCD_Latch(void);

void LCD_Init(void){
	setBits(LCD_DATA_DDR, LCD_DATA_MSK);
	setBit(LCD_CTRL_DDR, LCD_RS_PIN);
	setBit(LCD_CTRL_DDR, LCD_EN_PIN);
	Timer0_Delay(100);
	LCD_SendCMD(CMD_FUNCTION_SET_4BITS_2LINE);
	LCD_SendCMD(CMD_CFG);
	LCD_SendCMD(CMD_DISP_ON);
	LCD_SendCMD(CMD_ENTRY_MODE);
	LCD_Clear();
}
void LCD_Clear(void){
	LCD_SendCMD(CMD_CLEAR);
	Timer0_Delay(50);
}
void LCD_DispChar(u8 u8Char){
	LCD_SendData(u8Char);
}
void LCD_DispStr(u8* pu8Str){

}
void LCD_DispCharXY(u8 row, u8 col, u8 u8Char){
	LCD_GoToXY(row,col);
	LCD_DispChar(u8Char);
}
void LCD_DispStrXY(u8 row, u8 col, u8* pu8Str){
	LCD_GoToXY(row,col);
	LCD_DispStr(pu8Str);
}

void LCD_SendCMD(u8 u8CMD){
	clearBit(LCD_CTRL_PORT, LCD_RS_PIN);
	clearBits(LCD_DATA_PORT, LCD_DATA_MSK);
	setBits(LCD_DATA_PORT, (u8CMD & 0xF0)>>1);
	LCD_Latch();
	clearBits(LCD_DATA_PORT, LCD_DATA_MSK);
	setBits(LCD_DATA_PORT, (u8CMD<<3));
	LCD_Latch();
	_delay_us(40);
}
static void LCD_SendData(u8 u8Data){
	setBit(LCD_CTRL_PORT, LCD_RS_PIN);
	clearBits(LCD_DATA_PORT, LCD_DATA_MSK);
	setBits(LCD_DATA_PORT, (u8Data & 0xF0)>>1);
	LCD_Latch();
	clearBits(LCD_DATA_PORT, LCD_DATA_MSK);
	setBits(LCD_DATA_PORT, (u8Data<<3));
	LCD_Latch();
	_delay_us(40);
}
static void LCD_GoToXY(u8 row, u8 col){
	if (row == 1)
	{
		LCD_SendCMD((0x00|0x80) + col -1);
	}
	else
	{
		LCD_SendCMD((0x40|0x80) + col -1);
	}
}
static void LCD_Latch(void){
	setBit(LCD_CTRL_PORT, LCD_EN_PIN);
	_delay_us(1);
	clearBit(LCD_CTRL_PORT, LCD_EN_PIN);
}
void LCD_displayString(char *Str)
{
	u8 i = 0;
	while(Str[i] != '\0')
	{
		LCD_DispChar(Str[i]);
		i++;
	}
}
void LCD_displayStringRowColumn(u8 row,u8 col, char *Str)
{
	LCD_GoToXY(row,col);   
	LCD_displayString(Str);
}

void LCD_Displayint(int data)
{
	char arr[16];           
	itoa(data,arr,10);      
	LCD_displayString(arr);

}

void LCD_Welcome(void)
{
	LCD_displayStringRowColumn(1,10,"WELCOME");
	u8 i=0;
	u8 x = 0;
	while(x<3)  
	{
		for(i=0;i<9;i++)
		{
			LCD_SendCMD(0x18); 
			Timer0_Delay(100);
		}
		for(i=0;i<9;i++)
		{
			LCD_SendCMD(0x1C);   
			Timer0_Delay(100);
		}
		x++;
	}
	LCD_Clear();
}
void LCD_Idle(s8 set_temp, s8 crt_temp, u8 state)
{
	u8 sys_state;
	if(state == '*'){} 
	else
	{
		switch(state)     
		{
		case STANDBY:
			sys_state = "STANDBY  ";
			break;
		case OPERATION:
			sys_state = "OPERATION";
			break;
		case NORMAL:           
			sys_state = "NORMAL   ";
			break;
		case 3:
			sys_state = "ERROR    ";
			break;
		default:
			sys_state="STANDBY  ";
		}
		LCD_displayStringRowColumn(2,1,"STATE:");
		LCD_displayString(sys_state);              
	}
	LCD_displayStringRowColumn(1,1,"SET:");
	if (set_temp == '*'){} 
	else
	{
		LCD_Displayint(set_temp);             
	}
	LCD_displayStringRowColumn(1,10,"CRT:");
	if(crt_temp == '*'){} 
	else if (crt_temp == 0)
	{
		LCD_displayString("  ");
	}
	else
	{
		if(crt_temp / 100 == 0){
			LCD_Displayint(crt_temp);            
			LCD_displayString("  ");			
		}
		else if(crt_temp / 10 == 0){
			LCD_Displayint(crt_temp);             		
			LCD_displayString(" ");
		}
		else{
			LCD_Displayint(crt_temp);             
		}
	}
}
