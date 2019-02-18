#include "stm32f10x.h"
#include "stm32f10x_usart.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "usart.h"
#include "delay.h"

static struct _usart_recv_t {
    void *obj;
    recv_func_t fun;
} _usart_dev[5];

USART::USART(USART_TypeDef *USARTx, u32 bound) {
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    if (USARTx == USART1) {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA, ENABLE);
        USART_DeInit(USART1);
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_Init(GPIOA, &GPIO_InitStructure);
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_Init(GPIOA, &GPIO_InitStructure);

        NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
    } else if (USARTx == USART2) {
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

        USART_DeInit(USART2);

        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_Init(GPIOA, &GPIO_InitStructure);
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_Init(GPIOA, &GPIO_InitStructure);

        NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
    } else if (USARTx == USART3) {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);

        USART_DeInit(USART3);

        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_Init(GPIOB, &GPIO_InitStructure);
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_Init(GPIOB, &GPIO_InitStructure);

        NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
    }


    USART_InitStructure.USART_BaudRate = bound;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl
            = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ


    USART_Init(USARTx, &USART_InitStructure);

    NVIC_Init(&NVIC_InitStructure);

    USART_ITConfig(USARTx, USART_IT_RXNE, ENABLE);

    USART_Cmd(USARTx, ENABLE);

    this->USARTx = USARTx;
}

void USART::recv(void *obj, recv_func_t fun) {
    u8 x;
    if (USARTx == USART1) x = 1;
    else if (USARTx == USART2)x = 2;
    else if (USARTx == USART3) x = 3;
    else return;
    _usart_dev[x].fun = fun;
    _usart_dev[x].obj = obj;
}

void USART::send(char ch) {
    while(USART_GetFlagStatus(USARTx,USART_FLAG_TC) == RESET);
    USART_SendData(USARTx, (uint16_t) ch);
}

void USART::send(char *str) {
    while (*str)send(*str++);
}


//void usart1_init(u32 bound)
//{
//  GPIO_InitTypeDef GPIO_InitStructure;
//  USART_InitTypeDef USART_InitStructure;
//  NVIC_InitTypeDef NVIC_InitStructure;
//
//  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);
//
//  USART_DeInit(USART1);
//
//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
//  GPIO_Init(GPIOA, &GPIO_InitStructure);
//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
//  GPIO_Init(GPIOA, &GPIO_InitStructure);
//  //
//  USART_InitStructure.USART_BaudRate = bound;
//  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
//  USART_InitStructure.USART_StopBits = USART_StopBits_1;
//  USART_InitStructure.USART_Parity = USART_Parity_No;
//  USART_InitStructure.USART_HardwareFlowControl
//  = USART_HardwareFlowControl_None;
//  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
//  USART_Init(USART1, &USART_InitStructure);
//
//  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
//  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2 ;
//  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
//  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ
//  NVIC_Init(&NVIC_InitStructure);
//
//  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
//
//  USART_Cmd(USART1, ENABLE);
//}
////
//void usart2_init(u32 bound)
//{
//  GPIO_InitTypeDef GPIO_InitStructure;
//  USART_InitTypeDef USART_InitStructure;
//  NVIC_InitTypeDef NVIC_InitStructure;
//
//  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
//RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
//
//  USART_DeInit(USART2);
//
//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
//  GPIO_Init(GPIOA, &GPIO_InitStructure);
//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
//  GPIO_Init(GPIOA, &GPIO_InitStructure);
//  //
//  USART_InitStructure.USART_BaudRate = bound;
//  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
//  USART_InitStructure.USART_StopBits = USART_StopBits_1;
//  USART_InitStructure.USART_Parity = USART_Parity_No;
//  USART_InitStructure.USART_HardwareFlowControl
//  = USART_HardwareFlowControl_None;
//  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
//  USART_Init(USART2, &USART_InitStructure);
//
//  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
//  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2 ;
//  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
//  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ
//  NVIC_Init(&NVIC_InitStructure);
//
//  USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
//
//  USART_Cmd(USART2, ENABLE);
//}
//
//void usart3_init(u32 bound)
//{
//  GPIO_InitTypeDef GPIO_InitStructure;
//  USART_InitTypeDef USART_InitStructure;
//  NVIC_InitTypeDef NVIC_InitStructure;
//
//    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
//RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);
//
//  USART_DeInit(USART3);
//
//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
//  GPIO_Init(GPIOB, &GPIO_InitStructure);
//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
//  GPIO_Init(GPIOB, &GPIO_InitStructure);
//  //
//  USART_InitStructure.USART_BaudRate = bound;
//  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
//  USART_InitStructure.USART_StopBits = USART_StopBits_1;
//  USART_InitStructure.USART_Parity = USART_Parity_No;
//  USART_InitStructure.USART_HardwareFlowControl
//  = USART_HardwareFlowControl_None;
//  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
//  USART_Init(USART3, &USART_InitStructure);
//
//  NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
//  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2 ;
//  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
//  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ
//  NVIC_Init(&NVIC_InitStructure);
//
//  USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
//
//  USART_Cmd(USART3, ENABLE);
//}

extern "C" void USART1_IRQHandler(void) {
    if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET) {
        if (_usart_dev[1].fun)
            _usart_dev[1].fun(_usart_dev[1].obj, (char) USART_ReceiveData(USART1));
        USART_ClearITPendingBit(USART1, USART_IT_RXNE);
    }
}

extern "C" void USART2_IRQHandler(void) {
    char received_char;
    if (USART_GetITStatus(USART2, USART_IT_RXNE) != RESET) {
        if (_usart_dev[2].fun)
            _usart_dev[2].fun(_usart_dev[2].obj, (char) USART_ReceiveData(USART2));
        USART_ClearITPendingBit(USART2, USART_IT_RXNE);
    }
}

extern "C" void USART3_IRQHandler(void) {
    char received_char;
    if (USART_GetITStatus(USART3, USART_IT_RXNE) != RESET) {
        if (_usart_dev[3].fun)
            _usart_dev[3].fun(_usart_dev[3].obj, (char) USART_ReceiveData(USART3));
        USART_ClearITPendingBit(USART3, USART_IT_RXNE);
    }
}
