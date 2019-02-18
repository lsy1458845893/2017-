//
// Created by lsy on 17-6-7.
//

#include <stm32f10x_gpio.h>
#include "LMH6518.h"
#include "stm32f10x.h"


void LMH6518_send_byte(u8 dat) {
    int cursor = 8;
    while (cursor--) {
        LMH6518_CLK_L;
        if (dat & (1 << cursor))LMH6518_DAT_H;
        else
            LMH6518_DAT_L;
        LMH6518_CLK_H;
    }
}

void LMH6518_send(u8 fullpower, u8 preamp, u8 filter, u8 attenuation) {
    u16 dat = 0;
    if (fullpower)dat |= 1 << 10;
    if (preamp)dat |= 1 << 4;
    dat |= filter << 6;
    dat |= attenuation;
    LMH6518_CS_L;
    LMH6518_send_byte(0);
    LMH6518_send_byte(dat >> 8);
    LMH6518_send_byte(dat & 0xFF);
    LMH6518_CS_H;
}

void LMH6518_init(void) {
    GPIO_InitTypeDef pin;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

    pin.GPIO_Mode = GPIO_Mode_Out_PP;
    pin.GPIO_Speed = GPIO_Speed_50MHz;
    pin.GPIO_Pin = LMH6518_CS | LMH6518_CLK | LMH6518_DAT;

    GPIO_Init(LMH6518_FAMLAY,&pin);
}

