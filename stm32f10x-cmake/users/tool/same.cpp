//
// Created by lsy on 17-6-9.
//

#include <stm32f10x_gpio.h>
#include "same.h"

void RCC_INIT(void *DEV) {

    if (DEV == AFIO)RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
    else if (DEV == GPIOA)RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    else if (DEV == GPIOB)RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    else if (DEV == GPIOC)RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    else if (DEV == GPIOD)RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
    else if (DEV == GPIOE)RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
    else if (DEV == GPIOF)RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF, ENABLE);
    else if (DEV == GPIOG)RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG, ENABLE);
    else if (DEV == ADC1)RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
    else if (DEV == ADC2)RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC2, ENABLE);
    else if (DEV == TIM1)RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
    else if (DEV == SPI1)RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
    else if (DEV == TIM8)RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);
    else if (DEV == USART1)RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
    else if (DEV == ADC3)RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC3, ENABLE);
    else if (DEV == TIM15)RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM15, ENABLE);
    else if (DEV == TIM16)RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM16, ENABLE);
    else if (DEV == TIM17)RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM17, ENABLE);
    else if (DEV == TIM9)RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM9, ENABLE);
    else if (DEV == TIM10)RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM10, ENABLE);
    else if (DEV == TIM11)RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM11, ENABLE);

    else if (DEV == TIM2) RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    else if (DEV == TIM3) RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
    else if (DEV == TIM4) RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
    else if (DEV == TIM5) RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
    else if (DEV == TIM6) RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);
    else if (DEV == TIM7) RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE);
    else if (DEV == TIM12) RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM12, ENABLE);
    else if (DEV == TIM13) RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM13, ENABLE);
    else if (DEV == TIM14) RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM14, ENABLE);
    else if (DEV == WWDG) RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG, ENABLE);
    else if (DEV == SPI2) RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);
    else if (DEV == SPI3) RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI3, ENABLE);
    else if (DEV == USART2) RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
    else if (DEV == USART3) RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
    else if (DEV == UART4) RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);
    else if (DEV == UART5) RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5, ENABLE);
    else if (DEV == I2C1) RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);
    else if (DEV == I2C2) RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2, ENABLE);
    else if (DEV == CAN1) RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);
    else if (DEV == CAN2) RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN2, ENABLE);
    else if (DEV == BKP) RCC_APB1PeriphClockCmd(RCC_APB1Periph_BKP, ENABLE);
    else if (DEV == PWR) RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
    else if (DEV == DAC) RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);
    else if (DEV == CEC) RCC_APB1PeriphClockCmd(RCC_APB1Periph_CEC, ENABLE);
}


void GPIO_INIT_OUT(GPIO_TypeDef *port,uint16_t pin){
    RCC_INIT(port);
    GPIO_InitTypeDef gpio;
    gpio.GPIO_Pin = pin;
    gpio.GPIO_Speed = GPIO_Speed_50MHz;
    gpio.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(port,&gpio);
}
void GPIO_INIT_IN(GPIO_TypeDef *port,uint16_t pin){
    RCC_INIT(port);
    GPIO_InitTypeDef gpio;
    gpio.GPIO_Pin = pin;
    gpio.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(port,&gpio);
}

