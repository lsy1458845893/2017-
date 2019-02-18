//
// Created by lsy on 17-6-7.
//

#ifndef TEMPLATE_ADF4350_H
#define TEMPLATE_ADF4350_H

#include "stm32f10x.h"


class ADF4350 {
private:
    GPIO_TypeDef *SCK_FAM;
    uint16_t SCK_PIN;
    GPIO_TypeDef *DAT_FAM;
    uint16_t DAT_PIN;
    GPIO_TypeDef *LE_FAM;
    uint16_t LE_PIN;

    void init(void);

    void send(u32 dat);

public:
    ADF4350(
            GPIO_TypeDef *SCK_FAM, uint16_t SCK_PIN,
            GPIO_TypeDef *DAT_FAM, uint16_t DAT_PIN,
            GPIO_TypeDef *LE_FAM, uint16_t LE_PIN
    );

    void freq(float f);
};

#endif //TEMPLATE_ADF4350_H
