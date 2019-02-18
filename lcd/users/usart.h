//
// Created by lsy on 17-6-15.
//

#ifndef TEMPLATE_USART_H
#define TEMPLATE_USART_H

#include "stm32f4xx.h"


typedef void(*recv_func_t)(void *obj,char ch);
class USART{
    USART_TypeDef *USARTx;
public:

    USART(USART_TypeDef* USARTx,u32 bound);
    void recv(void *obj,recv_func_t fun);
    void send(char ch);
    void send(char *str);

    static void send(void *obj,char ch){ ((USART *)obj)->send(ch); }
    static void send(void *obj,char *str){ ((USART *)obj)->send(str); }
};

extern USART *sysio;

#endif //TEMPLATE_USART_H
