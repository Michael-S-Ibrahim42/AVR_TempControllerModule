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
#ifndef SPI_H_
#define SPI_H_

#define SPI_PORT			PORTB
#define SPI_DDR				DDRB

#define SPI_SCK				PB7
#define SPI_MISO			PB6
#define SPI_MOSI			PB5
#define SPI_SS				PB4

#define SPI_DUMMY			0x00

typedef enum{
	SPI_SLAVE, SPI_MASTER
}SPI_Mode;

void	SPI_Init(SPI_Mode mode);
u8		SPI_Transceve(u8 data);

#endif /* SPI_H_ */