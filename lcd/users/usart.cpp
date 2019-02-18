//
// Created by lsy on 17-6-15.
//

#include "usart.h"
#include "same.h"

static struct _usart_recv_t {
    void *obj;
    recv_func_t fun;
} _usart_dev[5];

extern USART *sysio;

USART::USART(USART_TypeDef *USARTx, u32 bound) : USARTx(USARTx) {

    RCC_INIT(USARTx);

    USART_DeInit(USARTx);

    USART_InitTypeDef uart;
    NVIC_InitTypeDef nvic;
    GPIO_InitTypeDef gpio;

    gpio.GPIO_Mode = GPIO_Mode_AF;
    gpio.GPIO_Speed = GPIO_Speed_50MHz;
    gpio.GPIO_OType = GPIO_OType_PP;
    gpio.GPIO_PuPd = GPIO_PuPd_UP;

    if (USARTx == USART1) {
        RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
        GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_USART1);
        GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_USART1);
        gpio.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
        GPIO_Init(GPIOA, &gpio);
        nvic.NVIC_IRQChannel = USART1_IRQn;
    }

    uart.USART_BaudRate = bound;
    uart.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    uart.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    uart.USART_Parity = USART_Parity_No;
    uart.USART_StopBits = USART_StopBits_1;
    uart.USART_WordLength = USART_WordLength_8b;

    nvic.NVIC_IRQChannelCmd = ENABLE;
    nvic.NVIC_IRQChannelPreemptionPriority = 2;
    nvic.NVIC_IRQChannelSubPriority = 2;

    USART_Init(USARTx, &uart);

    USART_Cmd(USARTx,ENABLE);

    USART_ITConfig(USARTx, USART_IT_RXNE, ENABLE);

    NVIC_Init(&nvic);


//    GPIO_InitTypeDef GPIO_InitStructure;
//    USART_InitTypeDef USART_InitStructure;
//    NVIC_InitTypeDef NVIC_InitStructure;
//
//    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
//    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
//
//
//    GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1);
//    GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1);
//
//
//    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
//    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
//    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
//    GPIO_Init(GPIOA, &GPIO_InitStructure);
//
//
//    USART_InitStructure.USART_BaudRate = bound;
//    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
//    USART_InitStructure.USART_StopBits = USART_StopBits_1;
//    USART_InitStructure.USART_Parity = USART_Parity_No;
//    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
//    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
//    USART_Init(USART1, &USART_InitStructure);
//
//    USART_Cmd(USART1, ENABLE);
//
//
//    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
//
//
//    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
//    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
//    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
//    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//    NVIC_Init(&NVIC_InitStructure);

}

void USART::recv(void *obj, recv_func_t fun) {
    u8 x;
    if (USARTx == USART1) x = 1;
    else if (USARTx == USART2)x = 2;
    else if (USARTx == USART3) x = 3;
    else if (USARTx == UART4) x = 4;
    else if (USARTx == UART5) x = 5;
    else return;
    _usart_dev[x].fun = fun;
    _usart_dev[x].obj = obj;
}

void USART::send(char ch) {
    while (USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET);
    USART_SendData(USARTx, (uint16_t) ch);
}

void USART::send(char *str) {
    while (*str)send(*str++);
}

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

extern "C" void UART4_IRQHandler(void) {
    char received_char;
    if (USART_GetITStatus(UART4, USART_IT_RXNE) != RESET) {
        if (_usart_dev[4].fun)
            _usart_dev[4].fun(_usart_dev[4].obj, (char) USART_ReceiveData(UART4));
        USART_ClearITPendingBit(UART4, USART_IT_RXNE);
    }
}


extern "C" void UART5_IRQHandler(void) {
    char received_char;
    if (USART_GetITStatus(UART5, USART_IT_RXNE) != RESET) {
        if (_usart_dev[5].fun)
            _usart_dev[5].fun(_usart_dev[5].obj, (char) USART_ReceiveData(UART5));
        USART_ClearITPendingBit(UART5, USART_IT_RXNE);
    }
}
