#ifndef __IIC_KEY_H__
#define __IIC_KEY_H__ 0

#include "stm32f10x_conf.h"

#define TIME 10

#define IIC_SDA_1 GPIO_SetBits(GPIOB,GPIO_Pin_13)
#define IIC_SDA_0 GPIO_ResetBits(GPIOB,GPIO_Pin_13)

#define IIC_CLK_1 GPIO_SetBits(GPIOB,GPIO_Pin_14)
#define IIC_CLK_0 GPIO_ResetBits(GPIOB,GPIO_Pin_14)


void IIC_Bus_Init(void);

void IIC_Start(void);
void IIC_Stop(void);
void IIC_WriteByte(u8 Data);
u8 IIC_ReadByte(void);
void IIC_SendWord(u8 add1, u8 add2, u8 byte1, u8 byte2);
u8 IIC_KeyGet(void);
u8 Key_Recode(u8 old_code);

#endif

