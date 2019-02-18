#include <stm32f4xx_conf.h>
#include "device.hpp"

#include "stdio.h"

#include "ad9959fuc.h"

u8 AD9959_Value[4] = {0x00, 0x00, 0x00, 0x00};
u8 Reg_Len[25] = {1, 3, 2, 3, 4, 2, 3, 2, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
                  4};        //对应不同寄存器位数，1*8,2*8，3*8，或者4*8



void AD9959_Init(void) {
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_AHB1PeriphClockCmd(
            RCC_AHB1Periph_GPIOF |
            RCC_AHB1Periph_GPIOB |
            RCC_AHB1Periph_GPIOE, ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 |
                                  GPIO_Pin_6 | GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_5 |
                                  GPIO_Pin_6 | GPIO_Pin_3 | GPIO_Pin_4;
    GPIO_Init(GPIOE, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
    GPIO_Init(GPIOF, &GPIO_InitStructure);

    AD9959_Reset();

    delay_ms(10);

    AD9959_WRrg(FR1, 0xD00000, 1);//设置FR1寄存器默认值，必须在reset之后设置才有效

    delay_ms(10);

}

void AD9959_Reset(void) {
//	AD9959_RST = 0;
    GPIO_ResetBits(GPIOE, GPIO_Pin_2);
    delay_us(50);
//	AD9959_RST = 1;
    GPIO_SetBits(GPIOE, GPIO_Pin_2);
    delay_us(50);
//	AD9959_RST = 0;
    GPIO_ResetBits(GPIOE, GPIO_Pin_2);
}


//update the locked data
void AD9959_Update(void) {
//    AD9959_UP = 0;
    GPIO_ResetBits(GPIOB, GPIO_Pin_5);
    //delay_us(50);
//    AD9959_UP = 1;
    GPIO_SetBits(GPIOB, GPIO_Pin_5);
    //delay_us(50);
//    AD9959_UP = 0;
    GPIO_ResetBits(GPIOB, GPIO_Pin_5);
}


void AD9959_WRrg(u8 reg, u32 data, u8 temp) {
    u8 ControlValue = 0;
    u8 ValueToWrite = 0;
    u8 i, j, nbyte;
    nbyte = Reg_Len[reg];
    ControlValue = reg;    //Create the 8-bit header

//    AD9959_SCK = 0;
    GPIO_ResetBits(GPIOB, GPIO_Pin_3);
//    AD9959_CS = 0;                    //bring CS low
    GPIO_ResetBits(GPIOB, GPIO_Pin_4);
    for (i = 0; i < 8; i++)                //Write out the control word
    {
//        AD9959_SCK = 0;
        GPIO_ResetBits(GPIOB, GPIO_Pin_3);
        if (0x80 == (ControlValue & 0x80)) {
//            AD9959_SDIO0 = 1;        //Send one to SDIO0pin
            GPIO_SetBits(GPIOE, GPIO_Pin_5);
        } else {
//            AD9959_SDIO0 = 0;        //Send zero to SDIO0pin
            GPIO_ResetBits(GPIOE, GPIO_Pin_5);
        }
//        AD9959_SCK = 1;
        GPIO_SetBits(GPIOB, GPIO_Pin_3);
        ControlValue <<= 1;            //Rotate data
    }
//    AD9959_SCK = 0;
    GPIO_ResetBits(GPIOB, GPIO_Pin_3);

    for (j = 0; j < nbyte; j++)        //And then the data
    {
        ValueToWrite = ((data >> ((nbyte - 1 - j) * 8)) & 0xff);
        for (i = 0; i < 8; i++) {
//            AD9959_SCK = 0;
            GPIO_ResetBits(GPIOB, GPIO_Pin_3);
            if (0x80 == (ValueToWrite & 0x80)) {
//                AD9959_SDIO0 = 1;        //Send one to SDIO0pin
                GPIO_SetBits(GPIOE, GPIO_Pin_5);
            } else {
//                AD9959_SDIO0 = 0;        //Send zero to SDIO0pin
                GPIO_ResetBits(GPIOE, GPIO_Pin_5);
            }
//            AD9959_SCK = 1;
            GPIO_SetBits(GPIOB, GPIO_Pin_3);
            ValueToWrite <<= 1;            //Rotate data
        }
//        AD9959_SCK = 0;
        GPIO_ResetBits(GPIOB, GPIO_Pin_3);
    }
    if (temp == 1)
        AD9959_Update();
//    AD9959_CS = 1;                        //bring CS high again
    GPIO_SetBits(GPIOB, GPIO_Pin_4);
}

void AD9959_Set_Fre(u8 Channel, double Freq) {
    unsigned long Temp;
    Temp = (u32) (Freq * FRE_REF);

    AD9959_WRrg(CSR, Channel, 0);
    AD9959_WRrg(CFTW0, Temp, 0);


}

void AD9959_Set_Amp(u8 Channel, u16 amp) {
    u32 dat;
    dat = 0x00001000 + amp;
    //AD9959_WRrg(CSR,Channel,0);
    AD9959_WRrg(0x06, dat, 0);
}
