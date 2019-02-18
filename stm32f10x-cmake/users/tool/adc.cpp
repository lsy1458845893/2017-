//
// Created by lsy on 17-6-14.
//

#include "adc.h"
#include "same.h"

ADC::ADC(ADC_TypeDef *ADCx) : ADCx(ADCx) {
    RCC_INIT(ADCx);

    RCC_ADCCLKConfig(RCC_PCLK2_Div6);

    ADC_InitTypeDef cfg;

    ADC_DeInit(ADCx);

    cfg.ADC_Mode = ADC_Mode_Independent;
    cfg.ADC_ContinuousConvMode = DISABLE;
    cfg.ADC_DataAlign = ADC_DataAlign_Right;
    cfg.ADC_ScanConvMode = ENABLE;
    cfg.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;

    if (ADCx == ADC1)cfg.ADC_NbrOfChannel = 18;
    else if (ADCx == ADC2)cfg.ADC_NbrOfChannel = 16;
    else if (ADCx == ADC3)cfg.ADC_NbrOfChannel = 13;

    ADC_Init(ADCx, &cfg);

    ADC_Cmd(ADCx, ENABLE);

    ADC_ResetCalibration(ADCx);
    while (ADC_GetResetCalibrationStatus(ADCx));
    ADC_StartCalibration(ADCx);
    while (ADC_GetCalibrationStatus(ADCx));
}

//     1     2     3
// 0   A0    A0    A0
// 1   A1    A1    A1
// 2   A2    A2    A2
// 3   A3    A3    A3
// 4   A4    A4    F6
// 5   A5    A5    F7
// 6   A6    A6    F8
// 7   A7    A7    F9
// 8   B0    B0    F10
// 9   B1    B1
// 10  C0    C0    C0
// 11  C1    C1    C1
// 12  C2    C2    C2
// 13  C3    C3    C3
// 14  C4    C4
// 15  C5    C5
// 16  ins
// 17  ref
#include "stdio.h"

void ADC::openChannl(uint8_t ch) {

    GPIO_InitTypeDef gpio;
    GPIO_TypeDef *port;

    if (ADCx == ADC1 || ADCx == ADC2 || ADCx == ADC3) {
        if (0 <= ch && ch <= 15) {
            gpio.GPIO_Mode = GPIO_Mode_AIN;

            switch (ch) {
                case 0 :
                    gpio.GPIO_Pin = GPIO_Pin_0;
                    port = GPIOA;
                    break;
                case 1 :
                    gpio.GPIO_Pin = GPIO_Pin_1;
                    port = GPIOA;
                    break;
                case 2 :
                    gpio.GPIO_Pin = GPIO_Pin_2;
                    port = GPIOA;
                    break;
                case 3 :
                    gpio.GPIO_Pin = GPIO_Pin_3;
                    port = GPIOA;
                    break;
                case 4 :
                    if (ADCx == ADC3) {
                        gpio.GPIO_Pin = GPIO_Pin_6;
                        port = GPIOF;
                    } else {
                        gpio.GPIO_Pin = GPIO_Pin_4;
                        port = GPIOA;
                    }
                    break;
                case 5 :
                    if (ADCx == ADC3) {
                        gpio.GPIO_Pin = GPIO_Pin_7;
                        port = GPIOF;
                    } else {
                        gpio.GPIO_Pin = GPIO_Pin_5;
                        port = GPIOA;
                    }
                    break;
                case 6 :
                    if (ADCx == ADC3) {
                        gpio.GPIO_Pin = GPIO_Pin_8;
                        port = GPIOF;
                    } else {
                        gpio.GPIO_Pin = GPIO_Pin_6;
                        port = GPIOA;
                    }
                    break;
                case 7 :
                    if (ADCx == ADC3) {
                        gpio.GPIO_Pin = GPIO_Pin_9;
                        port = GPIOF;
                    } else {
                        gpio.GPIO_Pin = GPIO_Pin_7;
                        port = GPIOA;
                    }
                    break;
                case 8 :
                    if (ADCx == ADC3) {
                        gpio.GPIO_Pin = GPIO_Pin_10;
                        port = GPIOF;
                    }
                    else {
                        gpio.GPIO_Pin = GPIO_Pin_0;
                        port = GPIOA;
                    }
                    break;
                case 9 :
                    gpio.GPIO_Pin = GPIO_Pin_1;
                    port = GPIOB;
                    break;
                case 10 :
                    gpio.GPIO_Pin = GPIO_Pin_0;
                    port = GPIOC;
                    break;
                case 11 :
                    gpio.GPIO_Pin = GPIO_Pin_1;
                    port = GPIOC;
                    break;
                case 12 :
                    gpio.GPIO_Pin = GPIO_Pin_2;
                    port = GPIOC;
                    break;
                case 13 :
                    gpio.GPIO_Pin = GPIO_Pin_3;
                    port = GPIOC;
                    break;
                case 14 :
                    gpio.GPIO_Pin = GPIO_Pin_4;
                    port = GPIOC;
                    break;
                case 15 :
                    gpio.GPIO_Pin = GPIO_Pin_5;
                    port = GPIOC;
                    break;
            }
            RCC_INIT(port);
            GPIO_Init(port, &gpio);
        } else {
            if (ch == 16){
                ADC_TempSensorVrefintCmd(ENABLE);
            } else if(ch == 17){
            }
        }
    }
}

void ADC::start(uint8_t ch) {
    ADC_RegularChannelConfig(ADCx, ch, 1, ADC_SampleTime_239Cycles5);
    ADC_SoftwareStartConvCmd(ADCx, ENABLE);
}

uint8_t ADC::aleady() { return ADC_GetFlagStatus(ADCx, ADC_FLAG_EOC); }

uint16_t ADC::read() { return ADC_GetConversionValue(ADCx); }

uint16_t ADC::blockConvert(uint8_t ch) {
    ADC_RegularChannelConfig(ADCx, ch, 1, ADC_SampleTime_239Cycles5);
    ADC_SoftwareStartConvCmd(ADCx, ENABLE);
    while (!ADC_GetFlagStatus(ADCx, ADC_FLAG_EOC));
    return ADC_GetConversionValue(ADCx);
}