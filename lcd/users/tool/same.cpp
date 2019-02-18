//
// Created by lsy on 17-6-15.
//

#include "same.h"
#include "stm32f4xx_gpio.h"

void RCC_INIT(void *dev) {
    if (dev == GPIOA)RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
    else if (dev == GPIOB)RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
    else if (dev == GPIOC)RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
    else if (dev == GPIOD)RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
    else if (dev == GPIOE)RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
    else if (dev == GPIOF)RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
    else if (dev == GPIOG)RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);
    else if (dev == GPIOH)RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOH, ENABLE);
    else if (dev == GPIOI)RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOI, ENABLE);
    else if (dev == GPIOJ)RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOJ, ENABLE);
    else if (dev == GPIOK)RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOK, ENABLE);

    else if (dev == TIM2) RCC_AHB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    else if (dev == TIM3) RCC_AHB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
    else if (dev == TIM4) RCC_AHB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
    else if (dev == TIM5) RCC_AHB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
    else if (dev == TIM6) RCC_AHB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);
    else if (dev == TIM7) RCC_AHB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE);
    else if (dev == TIM12) RCC_AHB1PeriphClockCmd(RCC_APB1Periph_TIM12, ENABLE);
    else if (dev == TIM13) RCC_AHB1PeriphClockCmd(RCC_APB1Periph_TIM13, ENABLE);
    else if (dev == TIM14) RCC_AHB1PeriphClockCmd(RCC_APB1Periph_TIM14, ENABLE);

    else if (dev == USART2) RCC_AHB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
    else if (dev == USART3) RCC_AHB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
    else if (dev == UART4) RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);
    else if (dev == UART5) RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5, ENABLE);

    else if (dev == TIM1) RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
    else if (dev == TIM8) RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);
    else if (dev == USART1) RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
    else if (dev == USART6) RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART6, ENABLE);
    else if (dev == ADC) RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC, ENABLE);
    else if (dev == ADC1) RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
    else if (dev == ADC2) RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC2, ENABLE);
    else if (dev == ADC3) RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC3, ENABLE);
    else if (dev == SDIO) RCC_APB2PeriphClockCmd(RCC_APB2Periph_SDIO, ENABLE);
    else if (dev == SPI1) RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
    else if (dev == SPI4) RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI4, ENABLE);
    else if (dev == SYSCFG) RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
    else if (dev == TIM9) RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM9, ENABLE);
    else if (dev == TIM10) RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM10, ENABLE);
    else if (dev == TIM11) RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM11, ENABLE);
    else if (dev == SPI5) RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI5, ENABLE);
    else if (dev == SPI6) RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI6, ENABLE);
    else if (dev == SAI1) RCC_APB2PeriphClockCmd(RCC_APB2Periph_SAI1, ENABLE);
}

void GPIO_INIT_OUT(GPIO_TypeDef *port, uint16_t pin) {
    RCC_INIT(port);
    GPIO_InitTypeDef gpio;
    gpio.GPIO_Mode = GPIO_Mode_OUT;
    gpio.GPIO_Speed = GPIO_Speed_100MHz;
    gpio.GPIO_PuPd = GPIO_PuPd_NOPULL;
    gpio.GPIO_OType = GPIO_OType_PP;
    gpio.GPIO_Pin = pin;
    GPIO_Init(port, &gpio);
}

void GPIO_INIT_IN(GPIO_TypeDef *port, uint16_t pin) {
    RCC_INIT(port);
    GPIO_InitTypeDef gpio;
    gpio.GPIO_Mode = GPIO_Mode_IN;
    gpio.GPIO_PuPd = GPIO_PuPd_NOPULL;
    gpio.GPIO_Pin = pin;
    GPIO_Init(port, &gpio);
}
