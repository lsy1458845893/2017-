#ifndef _BUTTON_H
#define _BUTTON_H

#include <stdint-gcc.h>
#include "stm32f4xx.h"


class Button {
public:
    GPIO_TypeDef *GPIOx[8];
    uint16_t PIN[8];
    uint8_t status[4][4];

    uint8_t onup(uint8_t x,uint8_t y);

    uint8_t ondown(uint8_t x,uint8_t y);

    uint8_t onchange(uint8_t x,uint8_t y);

    uint8_t isup(uint8_t x,uint8_t y);

    uint8_t isdown(uint8_t x,uint8_t y);

    uint8_t get_input(void);

  Button(uint32_t RCC_AHB1Periph_GPIOx, GPIO_TypeDef *GPIO_0, uint16_t pin_0,
         GPIO_TypeDef *GPIO_1, uint16_t pin_1, GPIO_TypeDef *GPIO_2,
         uint16_t pin_2, GPIO_TypeDef *GPIO_3, uint16_t pin_3,
         GPIO_TypeDef *GPIO_4, uint16_t pin_4, GPIO_TypeDef *GPIO_5,
         uint16_t pin_5, GPIO_TypeDef *GPIO_6, uint16_t pin_6,
         GPIO_TypeDef *GPIO_7, uint16_t pin_7);
};

#endif