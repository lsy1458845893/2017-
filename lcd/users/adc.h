//
// Created by lsy on 17-6-15.
//

#ifndef TEMPLATE_ADC_H
#define TEMPLATE_ADC_H

#include "stm32f4xx.h"
#include "stdint-gcc.h"


/**
 *    通道号 ADC1  ADC2  ADC3
 * 通道  0   PA0   PA0   PA0
 * 通道  1   PA1   PA1   PA1
 * 通道  2   PA2   PA2   PA2
 * 通道  3   PA3   PA3   PA3
 * 通道  4   PA4   PA4   PF6
 * 通道  5   PA5   PA5   PF7
 * 通道  6   PA6   PA6   PF8
 * 通道  7   PA7   PA7   PF9
 * 通道  8   PB0   PB0   PF10
 * 通道  9   PB1   PB1   PF3
 * 通道  10  PC0   PC0   PC0
 * 通道  11  PC1   PC1   PC1
 * 通道  12  PC2   PC2   PC2
 * 通道  13  PC13  PC13  PC13
 * 通道  14  PC4   PC4   PF4
 * 通道  15  PC5   PC5   PF5
 */
class Adc {
    ADC_TypeDef *ADCx;
public:
    Adc(ADC_TypeDef *ADCx);

    void openChannl(uint8_t ch);

    uint16_t blockConvert(uint8_t ch);

    void start(uint8_t ch);

    uint8_t aleady(void);

    uint16_t read(void);
};


#endif //TEMPLATE_ADC_H
