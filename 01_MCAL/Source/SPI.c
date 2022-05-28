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
#define F_CPU	8000000UL

#include "avr/io.h"
#include "util/delay.h"
#include "avr/interrupt.h"
#include "bit_handle.h"
#include "data_types.h"
#include "SPI.h"

void	SPI_Init(SPI_Mode mode){
	switch (mode)
	{
		case SPI_MASTER:
		setBits(SPI_DDR, ((1<<SPI_MOSI)|(1<<SPI_SCK)|(1<<SPI_SS)));
		clearBit(SPI_DDR, SPI_MISO);		
		setBit(SPCR, MSTR);
		break;
		case SPI_SLAVE:
		clearBits(SPI_DDR, ((1<<SPI_MOSI)|(1<<SPI_SCK)|(1<<SPI_SS)));
		setBit(SPI_DDR, SPI_MISO);
		clearBit(SPCR, MSTR);
		break;
	}
	setBit(SPCR, SPE);
}
u8		SPI_Transceve(u8 data){
	SPDR = data;
	while(!(SPSR&(1<<SPIF)));
	return SPDR;
}