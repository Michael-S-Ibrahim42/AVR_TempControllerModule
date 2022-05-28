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

#ifndef LCD_H_
#define LCD_H_

/* CFG Start */
#define LCD_DATA_PORT		               	 PORTA
#define LCD_DATA_DDR			             DDRA
#define LCD_DATA_MSK			             0x78

#define LCD_CTRL_PORT			             PORTA
#define LCD_CTRL_DDR			             DDRA
#define LCD_EN_PIN				             PA2
#define LCD_RS_PIN				             PA1
/* CFG End */

/* Commands */
#define CMD_CLEAR				             0x01
#define CMD_ENTRY_MODE			             0x06
#define CMD_DISP_ON				             0x0C
#define CMD_CFG					             0x28
#define CMD_FUNCTION_SET_4BITS_2LINE         0x02

typedef struct{
	u8 :4;
	u8 HN:4;
}LCD_DATA_Struct;

#define LCD_DATA_REG		(*((volatile LCD_DATA_Struct*)(&LCD_DATA_PORT)))

typedef enum{
	STANDBY = 0, OPERATION, NORMAL, ERROR
}state;

/* Functions */
void LCD_Init(void);
void LCD_Clear(void);
void LCD_DispChar(u8 u8Char);
void LCD_DispStr(u8* pu8Str);
void LCD_DispCharXY(u8 row, u8 col, u8 u8Char);
void LCD_DispStrXY(u8 row, u8 col, u8* pu8Str);
void LCD_displayString(char *Str);
void LCD_displayStringRowColumn(u8 row,u8 col, char *Str);
void LCD_Displayint(int data);
void LCD_SendCMD(u8 u8CMD);
void LCD_Welcome(void);
void LCD_Idle(s8 set_temp, s8 crt_temp, u8 state);

#endif /* LCD_H_ */