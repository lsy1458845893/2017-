//
// Created by lsy on 17-6-10.
//

#include <stm32f10x_gpio.h>
#include "iic.h"

#define SCL_L GPIO_ResetBits(SCL_FMY,SCL_PIN)
#define SDA_L GPIO_ResetBits(SDA_FMY,SDA_PIN)
#define SCL_H GPIO_SetBits(SCL_FMY,SCL_PIN)
#define SDA_H GPIO_SetBits(SDA_FMY,SDA_PIN)
#define READ_SDA GPIO_ReadInputDataBit(SDA_FMY,SDA_PIN)

void IIC::out(void) {
    GPIO_InitTypeDef pin;
    pin.GPIO_Speed = GPIO_Speed_50MHz;
    pin.GPIO_Mode = GPIO_Mode_Out_PP;
    pin.GPIO_Pin = SDA_PIN;
    GPIO_Init(SDA_FMY, &pin);
}

void IIC::in(void) {
    GPIO_InitTypeDef pin;
    pin.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    pin.GPIO_Pin = SDA_PIN;
    GPIO_Init(SDA_FMY, &pin);
}

void IIC::start(uint8_t dat) {
    out();
    SDA_H;
    SCL_H;
    delay();
    SDA_L;
    delay();
    SCL_L;
}

void IIC::stop(void) {
    out();
    SCL_H;
    delay();
    SDA_L;
    delay();
    SDA_H;
}

void IIC::write(uint8_t dat) {
    uint8_t c = 8;
    out();
    SCL_L;
    delay();
    while (c--) {
        if(dat &(1 << c)) SDA_H;
        else SDA_L;
        SCL_H;
        delay();
        SCL_L;
        delay();
    }
}

uint8_t IIC::read(void) {
    uint8_t dat = 0;
    uint8_t c = 8;
    in();
    delay();
    while (c--){
        SCL_L;
        delay();
        SCL_H;
        if (READ_SDA) dat |= 1 << c;
        delay();
    }
    return dat;
}











