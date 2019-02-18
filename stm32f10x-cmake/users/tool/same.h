//
// Created by lsy on 17-6-9.
//

#ifndef TEMPLATE_RCC_H
#define TEMPLATE_RCC_H

#include "stm32f10x.h"
void RCC_INIT(void *FMY);

void GPIO_INIT_OUT(GPIO_TypeDef *port,uint16_t pin);
void GPIO_INIT_IN(GPIO_TypeDef *port,uint16_t pin);

#endif //TEMPLATE_RCC_H
