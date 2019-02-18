//
// Created by lsy on 17-6-14.
//

#ifndef TEMPLATE_ADC_H
#define TEMPLATE_ADC_H

#include "stm32f10x.h"

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

class ADC {
    ADC_TypeDef *ADCx;
public:
    ADC(ADC_TypeDef *ADCX);

    void openChannl(uint8_t ch);

    uint16_t blockConvert(uint8_t ch);

    void start(uint8_t ch);

    uint8_t aleady(void);

    uint16_t read(void);
};


#endif //TEMPLATE_ADC_H
