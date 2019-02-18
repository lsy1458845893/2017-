//
// Created by lsy on 17-6-15.
//

#ifndef TEMPLATE_SAME_H
#define TEMPLATE_SAME_H

#include "stm32f4xx.h"

void RCC_INIT(void *dev);

void GPIO_INIT_OUT(GPIO_TypeDef *port,uint16_t pin);
void GPIO_INIT_IN(GPIO_TypeDef *port,uint16_t pin);


#endif //TEMPLATE_SAME_H
