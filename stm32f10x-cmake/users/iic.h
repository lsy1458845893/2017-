//
// Created by lsy on 17-6-10.
//

#ifndef TEMPLATE_IIC_H
#define TEMPLATE_IIC_H

#include "stm32f10x.h"
#include "same.h"
#include <delay.h>

class IIC {
private:
    GPIO_TypeDef *SCL_FMY;
    uint16_t SCL_PIN;
    GPIO_TypeDef *SDA_FMY;
    uint16_t SDA_PIN;



    void delay(void) { delay_us(10); }

public:
    IIC(GPIO_TypeDef *SCL_FMY, uint16_t SCL_PIN, GPIO_TypeDef *SDA_FMY, uint16_t SDA_PIN) :
            SCL_FMY(SCL_FMY), SCL_PIN(SCL_PIN), SDA_FMY(SDA_FMY), SDA_PIN(SDA_PIN) {
        RCC_INIT(SCL_FMY);
        RCC_INIT(SDA_FMY);

        GPIO_InitTypeDef pin;
        pin.GPIO_Mode = GPIO_Mode_Out_PP;
        pin.GPIO_Speed = GPIO_Speed_50MHz;

        pin.GPIO_Pin = SCL_PIN;
        GPIO_Init(SCL_FMY, &pin);
        pin.GPIO_Pin = SDA_PIN;
        GPIO_Init(SDA_FMY, &pin);
    };

    void out(void);

    void in(void);

    void start(uint8_t dat);

    void stop(void);

    void write(uint8_t dat);

    uint8_t read(void);

    uint8_t wait_ack(void);

    void send_ack(void);

    void send_nack(void);
};


#endif //TEMPLATE_IIC_H
