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
#ifndef TEMP_CONV_H_
#define TEMP_CONV_H_

#define TC72_CONTROL_Read_REG    0x00
#define TC72_CONTROL_Write_REG   0x80
#define TC72_MSB_Temp_Write_REG  0x02

typedef enum
{
	TC72_CONTINUES = 0x04 , TC72_ONE_SHOOT = 0x15 , TC72_SHUTDOWN = 0x05
}TC72_CONVERSION;

void TC72_Init(void);
s8 TC72_Value(void);
void TC72_Stop(void);
void TC72_Call_Timer(void);

#endif /* TEMP_CONV_H_ */