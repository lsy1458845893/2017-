


#include <stm32f4xx_conf.h>
#include "adc.h"
#include "same.h"
#include "stm32f4xx_adc.h"


Adc::Adc(ADC_TypeDef *ADCx) : ADCx(ADCx) {
    GPIO_InitTypeDef gpio;
    ADC_CommonInitTypeDef adc_common;
    ADC_InitTypeDef adc;
    uint32_t rcc;

    if (ADCx == ADC1)rcc = RCC_APB2Periph_ADC1;
    else if (ADCx == ADC2)rcc = RCC_APB2Periph_ADC2;
    else if (ADCx == ADC3)rcc = RCC_APB2Periph_ADC3;

    RCC_INIT(ADCx);

    adc_common.ADC_Mode = ADC_Mode_Independent;
    adc_common.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;
    adc_common.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
    adc_common.ADC_Prescaler = ADC_Prescaler_Div8;

    adc.ADC_Resolution = ADC_Resolution_12b;
    adc.ADC_ScanConvMode = DISABLE;
    adc.ADC_ContinuousConvMode = DISABLE;
    adc.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
    adc.ADC_DataAlign = ADC_DataAlign_Right;
    adc.ADC_NbrOfConversion = 16;

    RCC_APB2PeriphResetCmd(rcc, ENABLE);
    RCC_APB2PeriphResetCmd(rcc, DISABLE);

    ADC_CommonInit(&adc_common);

    ADC_Init(ADCx, &adc);

    ADC_Cmd(ADCx, ENABLE);
}

void Adc::openChannl(uint8_t ch) {
    GPIO_InitTypeDef gpio;
    gpio.GPIO_Mode = GPIO_Mode_AIN;
    gpio.GPIO_PuPd = GPIO_PuPd_NOPULL;
    static const struct {
        GPIO_TypeDef *port;
        uint16_t pin;
    } table[16] = {
            {.port = GPIOA, .pin = GPIO_Pin_0}, // 0   PA0   PA0
            {.port = GPIOA, .pin = GPIO_Pin_1}, // 1   PA1   PA1
            {.port = GPIOA, .pin = GPIO_Pin_2}, // 2   PA2   PA2
            {.port = GPIOA, .pin = GPIO_Pin_3}, // 3   PA3   PA3
            {.port = GPIOA, .pin = GPIO_Pin_4}, // 4   PA4   PA4
            {.port = GPIOA, .pin = GPIO_Pin_5}, // 5   PA5   PA5
            {.port = GPIOA, .pin = GPIO_Pin_6}, // 6   PA6   PA6
            {.port = GPIOA, .pin = GPIO_Pin_7}, // 7   PA7   PA7
            {.port = GPIOB, .pin = GPIO_Pin_0}, // 8   PB0   PB0
            {.port = GPIOB, .pin = GPIO_Pin_1}, // 9   PB1   PB1
            {.port = GPIOC, .pin = GPIO_Pin_0}, // 10  PC0   PC0
            {.port = GPIOC, .pin = GPIO_Pin_1}, // 11  PC1   PC1
            {.port = GPIOC, .pin = GPIO_Pin_2}, // 12  PC2   PC2
            {.port = GPIOC, .pin = GPIO_Pin_13}, // 13  PC13  PC13
            {.port = GPIOC, .pin = GPIO_Pin_4}, // 14  PC4   PC4
            {.port = GPIOC, .pin = GPIO_Pin_5}, // 15  PC5   PC5
    };
    if (ADCx == ADC1 || ADCx == ADC2) {
        RCC_INIT(table[ch].port);
        gpio.GPIO_Pin = table[ch].pin;
        GPIO_Init(table[ch].port, &gpio);
    } else if (ADCx == ADC3) {
        if (0 <= ch && ch <= 3) {
            RCC_INIT(table[ch].port);
            gpio.GPIO_Pin = table[ch].pin;
            GPIO_Init(table[ch].port, &gpio);
        } else if (4 <= ch && ch <= 7) {
            RCC_INIT(GPIOF);
            gpio.GPIO_Pin = table[ch + 2].pin;
            GPIO_Init(GPIOF, &gpio);
        }else if (8 == ch){
            RCC_INIT(GPIOF);
            gpio.GPIO_Pin = GPIO_Pin_8;
            GPIO_Init(GPIOF, &gpio);
        }else if(ch == 9) {
            RCC_INIT(GPIOF);
            gpio.GPIO_Pin = GPIO_Pin_9;
            GPIO_Init(GPIOF, &gpio);
        }else if(10 <= ch && ch <= 13){
            RCC_INIT(table[ch].port);
            gpio.GPIO_Pin = table[ch].pin;
            GPIO_Init(table[ch].port, &gpio);
        }else if (14 == ch){
            RCC_INIT(GPIOF);
            gpio.GPIO_Pin = GPIO_Pin_4;
            GPIO_Init(GPIOF, &gpio);
        }else if(ch == 15) {
            RCC_INIT(GPIOF);
            gpio.GPIO_Pin = GPIO_Pin_5;
            GPIO_Init(GPIOF, &gpio);
        }
    }
}

uint16_t Adc::blockConvert(uint8_t ch) {
    ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_480Cycles);
    ADC_SoftwareStartConv(ADC1);
    while (!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC));
    return ADC_GetConversionValue(ADC1);
}


uint8_t Adc::aleady() {
    return ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC);
}


void Adc::start(uint8_t ch) {
    ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_480Cycles);
    ADC_SoftwareStartConv(ADC1);
}

uint16_t Adc::read() {
    return ADC_GetConversionValue(ADC1);
}

