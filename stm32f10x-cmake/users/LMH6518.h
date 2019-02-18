//
// Created by lsy on 17-6-7.
//

#ifndef LMH6518_H
#define LMH6518_H


#define LMH6518_FAMLAY GPIOA
#define LMH6518_CLK GPIO_Pin_0
#define LMH6518_DAT GPIO_Pin_1
#define LMH6518_CS  GPIO_Pin_2


#define LMH6518_CLK_H GPIO_SetBits(LMH6518_FAMLAY, LMH6518_CLK)
#define LMH6518_DAT_H GPIO_SetBits(LMH6518_FAMLAY, LMH6518_DAT)
#define LMH6518_CS_H GPIO_SetBits(LMH6518_FAMLAY, LMH6518_CS)

#define LMH6518_CLK_L GPIO_ResetBits(LMH6518_FAMLAY, LMH6518_CLK)
#define LMH6518_DAT_L GPIO_ResetBits(LMH6518_FAMLAY, LMH6518_DAT)
#define LMH6518_CS_L GPIO_ResetBits(LMH6518_FAMLAY, LMH6518_CS)

void LMH6518_send_byte(u8 dat);

void LMH6518_send(u8 fullpower, u8 preamp, u8 filter, u8 attenuation);

void LMH6518_init(void);

#endif //TEMPLATE_LMH6518_H
