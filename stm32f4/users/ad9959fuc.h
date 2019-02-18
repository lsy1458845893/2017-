#ifndef __AD9959fuc_H
#define __AD9959fuc_H


#define Crystal  25000000
#define FRE_REF    8.5904963602764   //Ƶ�ʲο�


#define AD9959_CH0	0x10
#define AD9959_CH1	0x20
#define AD9959_CH2	0x40
#define AD9959_CH3	0x80
//port
#define AD9959_SDIO0    PGout(11)
#define AD9959_SDIO1    PGout(9)
#define AD9959_SDIO2    PGout(8)
#define AD9959_SDIO3    PGout(13)

#define AD9959_P0       PAout(14)
#define AD9959_P1       PAout(13)
#define AD9959_P2       PAout(12)
#define AD9959_P3       PAout(11)



#define AD9959_UP       PAout(8)
#define AD9959_CS       PDout(6)
#define AD9959_SCK      PDout(7)
#define AD9959_RST      PGout(7)

/**
 *  SD0:'E' 5
 *  SD1:'E' 6
 *  SD2:'E' 3
 *  SD3:'E' 4
 *  UP :'B' 5
 *  CS :'B' 4
 *  SCK:'B' 3
 *  RST:'E' 2
 *
 */

#define CSR  0x00    
#define FR1  0x01   
#define CFTW0 0x04   


void AD9959_Init(void);
void AD9959_Reset(void);
void AD9959_Update(void);
void AD9959_WRrg(u8 reg, u32 data,u8 temp);
void AD9959_Set_Fre(u8 Channel,double Freq);
void AD9959_Set_Amp(u8 Channel,u16 amp);


#endif


















