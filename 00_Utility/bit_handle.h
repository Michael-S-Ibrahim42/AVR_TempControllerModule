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
#ifndef BIT_HANDLE_H_
#define BIT_HANDLE_H_

#define setBit(REG,BN)							((REG) |=  (1<<(BN)))
#define clearBit(REG,BN)						((REG) &= ~(1<<(BN)))
#define toggleBit(REG,BN)						((REG) ^=  (1<<(BN)))

#define setBits(REG,BM)							((REG) |=  (BM))
#define clearBits(REG,BM)						((REG) &= ~(BM))
#define toggleBits(REG,BM)						((REG) ^=  (BM))

#define setAllBits(REG)							((REG)  =  (0xFF))
#define clearAllBits(REG)						((REG)  =  (0x00))
#define toggleAllBits(REG)						((REG) ^=  (0xFF))

#define readBit(REG,BN)							(((REG)>>(BN))&0x01)

#endif /* BIT_HANDLE_H_ */