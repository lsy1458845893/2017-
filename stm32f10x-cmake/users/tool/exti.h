//
// Created by lsy on 17-6-13.
//

#ifndef TEMPLATE_EXTI_H
#define TEMPLATE_EXTI_H

#include "stm32f10x.h"

typedef void (*callback_t)(void *dat);

class Exti {
private:
    EXTI_InitTypeDef cfg;
    GPIO_TypeDef *port;
    uint16_t pin;

    void set(callback_t fun, void *dat);

public:
    Exti(GPIO_TypeDef *port,uint16_t pin);

    ~Exti();

    void onRising(callback_t fun, void *dat);

    void onFalling(callback_t fun, void *dat);

    void onRisingFalling(callback_t fun, void *dat);

    void enable(void);

    void disable(void);
};


#endif //TEMPLATE_EXTI_H
