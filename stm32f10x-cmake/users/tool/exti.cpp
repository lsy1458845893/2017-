//
// Created by lsy on 17-6-13.
//

#include "exti.h"
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "same.h"

static callback_t fun[16];
static void *dat[16];

Exti::Exti(GPIO_TypeDef *port, uint16_t pin) : port(port), pin(pin) {
    NVIC_InitTypeDef nvic;
    GPIO_InitTypeDef gpio;

    RCC_INIT(port);

    gpio.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    gpio.GPIO_Pin = pin;
    GPIO_Init(port,&gpio);

    uint8_t ports, pins;

    if (port == GPIOA) ports = GPIO_PortSourceGPIOA;
    else if (port == GPIOB) ports = GPIO_PortSourceGPIOB;
    else if (port == GPIOC) ports = GPIO_PortSourceGPIOC;
    else if (port == GPIOD) ports = GPIO_PortSourceGPIOD;
    else if (port == GPIOE) ports = GPIO_PortSourceGPIOE;
    else if (port == GPIOF) ports = GPIO_PortSourceGPIOF;
    else if (port == GPIOG) ports = GPIO_PortSourceGPIOG;

    if (pin == GPIO_Pin_0) {
        cfg.EXTI_Line = EXTI_Line0;
        pins = GPIO_PinSource0;
        nvic.NVIC_IRQChannel = EXTI0_IRQn;
    } else if (pin == GPIO_Pin_1) {
        cfg.EXTI_Line = EXTI_Line1;
        pins = GPIO_PinSource1;
        nvic.NVIC_IRQChannel = EXTI1_IRQn;
    } else if (pin == GPIO_Pin_2) {
        cfg.EXTI_Line = EXTI_Line2;
        pins = GPIO_PinSource2;
        nvic.NVIC_IRQChannel = EXTI2_IRQn;
    } else if (pin == GPIO_Pin_3) {
        cfg.EXTI_Line = EXTI_Line3;
        pins = GPIO_PinSource3;
        nvic.NVIC_IRQChannel = EXTI3_IRQn;
    } else if (pin == GPIO_Pin_4) {
        cfg.EXTI_Line = EXTI_Line4;
        pins = GPIO_PinSource4;
        nvic.NVIC_IRQChannel = EXTI4_IRQn;
    } else if (pin == GPIO_Pin_5) {
        cfg.EXTI_Line = EXTI_Line5;
        pins = GPIO_PinSource5;
        nvic.NVIC_IRQChannel = EXTI9_5_IRQn;
    } else if (pin == GPIO_Pin_6) {
        cfg.EXTI_Line = EXTI_Line6;
        pins = GPIO_PinSource6;
        nvic.NVIC_IRQChannel = EXTI9_5_IRQn;
    } else if (pin == GPIO_Pin_7) {
        cfg.EXTI_Line = EXTI_Line7;
        pins = GPIO_PinSource7;
        nvic.NVIC_IRQChannel = EXTI9_5_IRQn;
    } else if (pin == GPIO_Pin_8) {
        cfg.EXTI_Line = EXTI_Line8;
        pins = GPIO_PinSource8;
        nvic.NVIC_IRQChannel = EXTI9_5_IRQn;
    } else if (pin == GPIO_Pin_9) {
        cfg.EXTI_Line = EXTI_Line9;
        pins = GPIO_PinSource9;
        nvic.NVIC_IRQChannel = EXTI9_5_IRQn;
    } else if (pin == GPIO_Pin_10) {
        cfg.EXTI_Line = EXTI_Line10;
        pins = GPIO_PinSource10;
        nvic.NVIC_IRQChannel = EXTI15_10_IRQn;
    } else if (pin == GPIO_Pin_11) {
        cfg.EXTI_Line = EXTI_Line11;
        pins = GPIO_PinSource11;
        nvic.NVIC_IRQChannel = EXTI15_10_IRQn;
    } else if (pin == GPIO_Pin_12) {
        cfg.EXTI_Line = EXTI_Line12;
        pins = GPIO_PinSource12;
        nvic.NVIC_IRQChannel = EXTI15_10_IRQn;
    } else if (pin == GPIO_Pin_13) {
        cfg.EXTI_Line = EXTI_Line13;
        pins = GPIO_PinSource13;
        nvic.NVIC_IRQChannel = EXTI15_10_IRQn;
    } else if (pin == GPIO_Pin_14) {
        cfg.EXTI_Line = EXTI_Line14;
        pins = GPIO_PinSource14;
        nvic.NVIC_IRQChannel = EXTI15_10_IRQn;
    } else if (pin == GPIO_Pin_15) {
        cfg.EXTI_Line = EXTI_Line15;
        pins = GPIO_PinSource15;
        nvic.NVIC_IRQChannel = EXTI15_10_IRQn;
    }


    cfg.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
    cfg.EXTI_Mode = EXTI_Mode_Interrupt;
    cfg.EXTI_LineCmd = ENABLE;


    nvic.NVIC_IRQChannelPreemptionPriority = 0x02; //抢占优先级 2,
    nvic.NVIC_IRQChannelSubPriority = 0x02; //子优先级 2
    nvic.NVIC_IRQChannelCmd = ENABLE;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

    GPIO_EXTILineConfig(ports, pins);

    EXTI_Init(&cfg);

    NVIC_Init(&nvic);
}

Exti::~Exti() {
    disable();
}

void Exti::set(callback_t _fun, void *_dat) {

    if (pin == GPIO_Pin_0) {
        fun[0] = _fun;
        dat[0] = _dat;
    } else if (pin == GPIO_Pin_1) {
        fun[1] = _fun;
        dat[1] = _dat;
    } else if (pin == GPIO_Pin_2) {
        fun[2] = _fun;
        dat[2] = _dat;
    } else if (pin == GPIO_Pin_3) {
        fun[3] = _fun;
        dat[3] = _dat;
    } else if (pin == GPIO_Pin_4) {
        fun[4] = _fun;
        dat[4] = _dat;
    } else if (pin == GPIO_Pin_5) {
        fun[5] = _fun;
        dat[5] = _dat;
    } else if (pin == GPIO_Pin_6) {
        fun[6] = _fun;
        dat[6] = _dat;
    } else if (pin == GPIO_Pin_7) {
        fun[7] = _fun;
        dat[7] = _dat;
    } else if (pin == GPIO_Pin_8) {
        fun[8] = _fun;
        dat[8] = _dat;
    } else if (pin == GPIO_Pin_9) {
        fun[9] = _fun;
        dat[9] = _dat;
    } else if (pin == GPIO_Pin_10) {
        fun[10] = _fun;
        dat[10] = _dat;
    } else if (pin == GPIO_Pin_11) {
        fun[11] = _fun;
        dat[11] = _dat;
    } else if (pin == GPIO_Pin_12) {
        fun[12] = _fun;
        dat[12] = _dat;
    } else if (pin == GPIO_Pin_13) {
        fun[13] = _fun;
        dat[13] = _dat;
    } else if (pin == GPIO_Pin_14) {
        fun[14] = _fun;
        dat[14] = _dat;
    } else if (pin == GPIO_Pin_15) {
        fun[15] = _fun;
        dat[15] = _dat;
    }
}

void Exti::onRising(callback_t fun, void *dat) {
    set(fun,dat);
    cfg.EXTI_Trigger = EXTI_Trigger_Rising;
    EXTI_Init(&cfg);
}

void Exti::onFalling(callback_t fun, void *dat) {
    set(fun,dat);
    cfg.EXTI_Trigger = EXTI_Trigger_Falling;
    EXTI_Init(&cfg);
}

void Exti::onRisingFalling(callback_t fun, void *dat) {
    set(fun,dat);
    cfg.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
    EXTI_Init(&cfg);
}

void Exti::enable(void) {
    cfg.EXTI_LineCmd = ENABLE;
    EXTI_Init(&cfg);
}

void Exti::disable(void) {
    cfg.EXTI_LineCmd = DISABLE;
    EXTI_Init(&cfg);
}

extern "C" void EXTI0_IRQHandler(void) {
    if (EXTI_GetITStatus(EXTI_Line0) != RESET) {
        if (fun[0])fun[0](dat[0]);
        EXTI_ClearITPendingBit(EXTI_Line0);
    }
}

extern "C" void EXTI1_IRQHandler(void) {
    if (EXTI_GetITStatus(EXTI_Line1) != RESET) {
        if (fun[1])fun[1](dat[1]);
        EXTI_ClearITPendingBit(EXTI_Line1);
    }
}

extern "C" void EXTI2_IRQHandler(void) {
    if (EXTI_GetITStatus(EXTI_Line2) != RESET) {
        if (fun[2])fun[2](dat[2]);
        EXTI_ClearITPendingBit(EXTI_Line2);
    }
}

extern "C" void EXTI3_IRQHandler(void) {
    if (EXTI_GetITStatus(EXTI_Line3) != RESET) {
        if (fun[3])fun[3](dat[3]);
        EXTI_ClearITPendingBit(EXTI_Line3);
    }
}

extern "C" void EXTI4_IRQHandler(void) {
    if (EXTI_GetITStatus(EXTI_Line4) != RESET) {
        if (fun[4])fun[4](dat[4]);
        EXTI_ClearITPendingBit(EXTI_Line4);
    }
}

extern "C" void EXTI9_5_IRQHandler(void) {
    if (EXTI_GetITStatus(EXTI_Line5) != RESET) {
        if (fun[5])fun[5](dat[5]);
        EXTI_ClearITPendingBit(EXTI_Line5);
    }
    if (EXTI_GetITStatus(EXTI_Line6) != RESET) {
        if (fun[6])fun[6](dat[6]);
        EXTI_ClearITPendingBit(EXTI_Line6);
    }
    if (EXTI_GetITStatus(EXTI_Line7) != RESET) {
        if (fun[7])fun[7](dat[7]);
        EXTI_ClearITPendingBit(EXTI_Line7);
    }
    if (EXTI_GetITStatus(EXTI_Line8) != RESET) {
        if (fun[8])fun[8](dat[8]);
        EXTI_ClearITPendingBit(EXTI_Line8);
    }
    if (EXTI_GetITStatus(EXTI_Line9) != RESET) {
        if (fun[9])fun[9](dat[9]);
        EXTI_ClearITPendingBit(EXTI_Line9);
    }
}

extern "C" void EXTI15_10_IRQHandler(void) {
    if (EXTI_GetITStatus(EXTI_Line10) != RESET) {
        if (fun[10])fun[10](dat[10]);
        EXTI_ClearITPendingBit(EXTI_Line10);
    }
    if (EXTI_GetITStatus(EXTI_Line11) != RESET) {
        if (fun[11])fun[11](dat[11]);
        EXTI_ClearITPendingBit(EXTI_Line11);
    }
    if (EXTI_GetITStatus(EXTI_Line12) != RESET) {
        if (fun[12])fun[12](dat[12]);
        EXTI_ClearITPendingBit(EXTI_Line12);
    }
    if (EXTI_GetITStatus(EXTI_Line13) != RESET) {
        if (fun[13])fun[13](dat[13]);
        EXTI_ClearITPendingBit(EXTI_Line13);
    }
    if (EXTI_GetITStatus(EXTI_Line14) != RESET) {
        if (fun[14])fun[14](dat[14]);
        EXTI_ClearITPendingBit(EXTI_Line14);
    }
    if (EXTI_GetITStatus(EXTI_Line15) != RESET) {
        if (fun[15])fun[15](dat[15]);
        EXTI_ClearITPendingBit(EXTI_Line15);
    }
}