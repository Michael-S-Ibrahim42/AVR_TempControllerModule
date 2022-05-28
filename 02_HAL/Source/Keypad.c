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
#define F_CPU		8000000
#include "util/delay.h"
#include "data_types.h"
#include "bit_handle.h"
#include <avr/io.h>
#include "keypad.h"

#if (N_col == 3)
    static u8 KeyPad_4x3_adjustKeyNumber(u8 button_number);
#elif (N_col == 4)
    static u8 KeyPad_4x4_adjustKeyNumber(u8 button_number);
#endif


u8 Keypad_u8getTwokeys(void){
	u8 i,data = 0;
	for(i = 0 ; i<2 ; i++)
	{
		data = (data *10) + KeyPad_GetPressedKey();
		_delay_ms(100);
	}
	return data;
}
u8 KeyPad_GetPressedKey(void)
{
	u8 col,row;
	while(1)
	{
		for(col=0;col<N_col;col++) 
		{
			KEYPAD_PORT_DIR = (0b00010000<<col); 
			KEYPAD_PORT_OUT = (~(0b00010000<<col));
			for(row=0;row<N_row;row++)
			{
				if(!readBit(KEYPAD_PORT_IN,row))  
				{
					while(!readBit(KEYPAD_PORT_IN,row));
					#if (N_col == 3)
						return KeyPad_4x3_adjustKeyNumber((row*N_col)+col+1);
					#elif (N_col == 4)
						return KeyPad_4x4_adjustKeyNumber((row*N_col)+col+1);
					#endif
				}
			}
		}
	}
}

#if (N_col == 3) 
    static u8 KeyPad_4x3_adjustKeyNumber(u8 button_number)
    {
        switch(button_number)
        {
            case 10: return '*'; 
                    break;
            case 11: return 0;
                    break;		
            case 12: return '#'; 
                    break;
            default: return button_number;								 						
        }
    } 
#elif (N_col == 4)
    static u8 KeyPad_4x4_adjustKeyNumber(u8 button_number)
    {
        switch(button_number)
        {
            case 1: return 7; 
                    break;
            case 2: return 8; 
                    break;
            case 3: return 9; 
                    break;
            case 4: return '%'; 
                    break;
            case 5: return 4; 
                    break;
            case 6: return 5;
                    break;
            case 7: return 6; 
                    break;
            case 8: return '*'; 
                    break;		
            case 9: return 1; 
                    break;
            case 10: return 2; 
                    break;
            case 11: return 3; 
                    break;
            case 12: return '-'; 
                    break;
            case 13: return 13;  
                    break;			
            case 14: return 0; 
                    break;
            case 15: return '='; 
                    break;
            case 16: return '+'; 
                    break;
            default: return button_number;								 						
        }
    } 
#endif
