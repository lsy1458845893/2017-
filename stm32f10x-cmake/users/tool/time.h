//
// Created by lsy on 17-5-29.
//

#ifndef TEMPLATE_TIME_H
#define TEMPLATE_TIME_H

#include "stm32f10x.h"



typedef void (*callback_t)(void *dat);

class Time {

    TIM_TypeDef *TIMX;

public:

    Time(TIM_TypeDef *TIMX);

    void setPeriod(uint16_t us);

    void setCallback(callback_t cb,void *dat);

    void start(void);

    void stop(void);
};


#endif //TEMPLATE_TIMER_H
