#ifndef USART_H
#define USART_H

#include "stm32f10x.h"
#include <stdio.h>

// user setting..
//#define PRINT_TO_USART 	1
//
//#define USART1_RECEIVED_FUNC(recv_char)
//#define USART2_RECEIVED_FUNC(recv_char)
//#define USART3_RECEIVED_FUNC(recv_char)
// user setting--

typedef void(*recv_func_t)(void *obj,char ch);

//// dev : USART1
//// port: GPIOA
//// Tx:   GPIO_Pin_9
//// Rx:   GPIO_Pin_10
//
//// dev : USART2
//// port: GPIOA
//// Tx:   GPIO_Pin_2
//// Rx:   GPIO_Pin_3
//
//// dev : USART3
//// port: GPIOB
//// Tx:   GPIO_Pin_10
//// Rx:   GPIO_Pin_11

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

#endif
