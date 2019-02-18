//
// Created by lsy on 17-5-29.
//

#include "time.h"
#include "same.h"

#define HTIME_NUM 8
static void *data[HTIME_NUM];
static callback_t func[HTIME_NUM];

//Tout= ((arr+1)*(psc+1))/Tclk
Time::Time(TIM_TypeDef *TIMX) : TIMX(TIMX) {
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_INIT(TIMX);

    if (TIMX == TIM2) NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
    else if (TIMX == TIM3) NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
    else if (TIMX == TIM4) NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
    else if (TIMX == TIM5) NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;
    else if (TIMX == TIM6) NVIC_InitStructure.NVIC_IRQChannel = TIM6_IRQn;
    else if (TIMX == TIM7) NVIC_InitStructure.NVIC_IRQChannel = TIM7_IRQn;

    TIM_TimeBaseStructure.TIM_Period = 999;
    TIM_TimeBaseStructure.TIM_Prescaler = 71;
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

    TIM_TimeBaseInit(TIMX, &TIM_TimeBaseStructure);
    TIM_ITConfig(TIMX, TIM_IT_Update, ENABLE);
    NVIC_Init(&NVIC_InitStructure);
}

void Time::start(void) {
    TIM_Cmd(TIMX, ENABLE);
}

void Time::stop(void) {
    TIM_Cmd(TIMX, DISABLE);
}

void Time::setPeriod(uint16_t us) {
    TIMX->ARR = (uint16_t) (us - 1);
}

void Time::setCallback(callback_t cb, void *dat) {
    if (TIMX == TIM2) {
        func[2] = cb;
        data[2] = dat;
    } else if (TIMX == TIM3) {
        func[3] = cb;
        data[3] = dat;
    } else if (TIMX == TIM4) {
        func[4] = cb;
        data[4] = dat;
    } else if (TIMX == TIM5) {
        func[5] = cb;
        data[5] = dat;
    } else if (TIMX == TIM6) {
        func[6] = cb;
        data[6] = dat;
    } else if (TIMX == TIM7) {
        func[7] = cb;
        data[7] = dat;
    }
}


extern "C" void TIM2_IRQHandler(void) {
    if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) {
        if (func[2])func[2](data[2]);
        TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
    }
}

extern "C" void TIM3_IRQHandler(void) {
    if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) {
        if (func[3])func[3](data[3]);
        TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
    }
}

extern "C" void TIM4_IRQHandler(void) {
    if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET) {
        if (func[4])func[4](data[4]);
        TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
    }
}

extern "C" void TIM5_IRQHandler(void) {
    if (TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET) {
        if (func[5])func[5](data[5]);
        TIM_ClearITPendingBit(TIM5, TIM_IT_Update);
    }
}

extern "C" void TIM6_IRQHandler(void) {
    if (TIM_GetITStatus(TIM6, TIM_IT_Update) != RESET) {
        if (func[6])func[6](data[6]);
        TIM_ClearITPendingBit(TIM6, TIM_IT_Update);
    }
}

extern "C" void TIM7_IRQHandler(void) {
    if (TIM_GetITStatus(TIM7, TIM_IT_Update) != RESET) {
        if (func[7])func[7](data[7]);
        TIM_ClearITPendingBit(TIM7, TIM_IT_Update);
    }
}
