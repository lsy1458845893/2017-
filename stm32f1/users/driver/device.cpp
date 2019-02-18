#include <misc.h>
#include <stm32f10x_conf.h>
#include <stm32f10x_adc.h>
#include <stm32f10x_exti.h>
#include <stm32f10x_spi.h>
#include "device.hpp"
#include "stdlib.h"

using namespace dev;


static uint8_t fac_us = 0;//us?????????
static uint16_t fac_ms = 0;//ms?????????


void delay_init(u8 SYSCLK) {

    SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);
    fac_us = SYSCLK / 8;                        //???????1/8
    fac_ms = (u16) fac_us * 1000;//??ucos??,???????ms?????systick?????
}


void delay_us(u32 nus) {
    u32 temp;
    SysTick->LOAD = nus * fac_us; //??????
    SysTick->VAL = 0x00;        //????????
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;          //???????
    do {
        temp = SysTick->CTRL;
    } while ((temp & 0x01) && !(temp & (1 << 16)));//????????
    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;       //????????
    SysTick->VAL = 0X00;       //????????
}

void delay_xms(u16 nms) {
    u32 temp;
    SysTick->LOAD = (u32) nms * fac_ms;//??????(SysTick->LOAD?24bit)
    SysTick->VAL = 0x00;           //????????
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;          //???????
    do {
        temp = SysTick->CTRL;
    } while ((temp & 0x01) && !(temp & (1 << 16)));//????????
    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;       //????????
    SysTick->VAL = 0X00;       //????????
}

//???nms
//nms:0~65535
void delay_ms(u16 nms) {
    u32 temp;
    SysTick->LOAD = (u32) nms * fac_ms;//??????(SysTick->LOAD?24bit)
    SysTick->VAL = 0x00;           //????????
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;          //???????
    do {
        temp = SysTick->CTRL;
    } while (temp & 0x01 && !(temp & (1 << 16)));//????????
    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;       //????????
    SysTick->VAL = 0X00;       //????????
}


/*
 *  EXTI0_IRQHandler
 *  EXTI1_IRQHandler
 *  EXTI2_IRQHandler
 *  EXTI3_IRQHandler
 *  EXTI4_IRQHandler
 *  EXTI9_5_IRQHandler
 *  EXTI15_10_IRQHandler
 *  TIM1_BRK_IRQHandler
 *  TIM1_UP_IRQHandler
 *  TIM1_TRG_COM_IRQHandler
 *  TIM1_CC_IRQHandler
 *  TIM2_IRQHandler
 *  TIM3_IRQHandler
 *  TIM4_IRQHandler
 *  TIM5_IRQHandler
 *  TIM6_IRQHandler
 *  TIM7_IRQHandler
 *  TIM8_BRK_IRQHandler
 *  TIM8_UP_IRQHandler
 *  TIM8_TRG_COM_IRQHandler
 *  TIM8_CC_IRQHandler
 *  I2C1_EV_IRQHandler
 *  I2C1_ER_IRQHandler
 *  I2C2_EV_IRQHandler
 *  I2C2_ER_IRQHandler
 *  USART1_IRQHandler
 *  USART2_IRQHandler
 *  USART3_IRQHandler
 *  UART4_IRQHandler
 *  UART5_IRQHandler
 *  RTCAlarm_IRQHandler
 *  USBWakeUp_IRQHandler
 *  FSMC_IRQHandler
 *  SDIO_IRQHandler
 *  ADC1_2_IRQHandler
 *  ADC3_IRQHandler
 *  USB_HP_CAN1_TX_IRQHandler
 *  USB_LP_CAN1_RX0_IRQHandler
 *  CAN1_RX1_IRQHandler
 *  CAN1_SCE_IRQHandler
 *  DMA1_Channel1_IRQHandler
 *  DMA1_Channel2_IRQHandler
 *  DMA1_Channel3_IRQHandler
 *  DMA1_Channel4_IRQHandler
 *  DMA1_Channel5_IRQHandler
 *  DMA1_Channel6_IRQHandler
 *  DMA1_Channel7_IRQHandler
 *  DMA2_Channel1_IRQHandler
 *  DMA2_Channel2_IRQHandler
 *  DMA2_Channel3_IRQHandler
 *  DMA2_Channel4_5_IRQHandler
 *  WWDG_IRQHandler
 *  PVD_IRQHandler
 *  TAMPER_IRQHandler
 *  RTC_IRQHandler
 *  FLASH_IRQHandler
 *  RCC_IRQHandler
 */


static void *SysTick_dat;

static void (*SysTick_func)(void *dat);


void SysTick_init(uint8_t p) {
    SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);
}

void SysTick_emit(void(*func)(void *), void *dat, uint32_t us) {
    SysTick_func = func;
    SysTick_dat = dat;
}

bool SysTick_aleady(void) { return SysTick_func == NULL; }

extern "C" void SysTick_Handler(void) {
    void (*func)(void *);
    func = SysTick_func;
    SysTick_func = NULL;
    if (func)func(SysTick_dat);
}

////////////////////////////////////////////////////////

static const uint32_t GPIOx_RCC[] = {
        RCC_APB2Periph_GPIOA, RCC_APB2Periph_GPIOB, RCC_APB2Periph_GPIOC,
        RCC_APB2Periph_GPIOD, RCC_APB2Periph_GPIOE, RCC_APB2Periph_GPIOF,
        RCC_APB2Periph_GPIOG
};

static const GPIO_TypeDef *GPIOx[] = {
        GPIOA, GPIOB, GPIOC,
        GPIOD, GPIOE, GPIOF,
        GPIOG
};


static const uint16_t GPIO_Pin_x[] = {
        GPIO_Pin_0, GPIO_Pin_1, GPIO_Pin_2, GPIO_Pin_3,
        GPIO_Pin_4, GPIO_Pin_5, GPIO_Pin_6, GPIO_Pin_7,
        GPIO_Pin_8, GPIO_Pin_9, GPIO_Pin_10, GPIO_Pin_11,
        GPIO_Pin_12, GPIO_Pin_13, GPIO_Pin_14, GPIO_Pin_15
};

static const uint8_t GPIO_PinSourcex[] = {
        GPIO_PinSource0, GPIO_PinSource1, GPIO_PinSource2, GPIO_PinSource3,
        GPIO_PinSource4, GPIO_PinSource5, GPIO_PinSource6, GPIO_PinSource7,
        GPIO_PinSource8, GPIO_PinSource9, GPIO_PinSource10, GPIO_PinSource11,
        GPIO_PinSource12, GPIO_PinSource13, GPIO_PinSource14, GPIO_PinSource15,
};

void gpio::output(bool s) {
    if (s) GPIO_SetBits((GPIO_TypeDef *) GPIOx[port - 'A'], GPIO_Pin_x[pin]);
    else GPIO_ResetBits((GPIO_TypeDef *) GPIOx[port - 'A'], GPIO_Pin_x[pin]);
}

bool gpio::read(void) {
    return GPIO_ReadInputDataBit((GPIO_TypeDef *) GPIOx[port - 'A'], GPIO_Pin_x[pin]);
}

void gpio::init(GPIO_InitTypeDef *s) {
    RCC_APB2PeriphClockCmd(GPIOx_RCC[port - 'A'], ENABLE);
    s->GPIO_Pin = GPIO_Pin_x[pin];
    GPIO_Init((GPIO_TypeDef *) GPIOx[port - 'A'], s);
}

void gpio::init_output(void) {
    GPIO_InitTypeDef p;
    p.GPIO_Speed = GPIO_Speed_50MHz;
    p.GPIO_Mode = GPIO_Mode_Out_PP;
    init(&p);
}

void gpio::init_input(void) {
    GPIO_InitTypeDef p;
    p.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    init(&p);
}

void gpio::toggle(void) {
    if (state) {
        GPIO_ResetBits((GPIO_TypeDef *) GPIOx[port - 'A'], GPIO_Pin_x[pin]);
        state = false;
    } else {
        GPIO_SetBits((GPIO_TypeDef *) GPIOx[port - 'A'], GPIO_Pin_x[pin]);
        state = true;
    }
}

///////////////////////////////////////////////////
static const struct {
    uint32_t rcc;
    USART_TypeDef *dev;
    char rx_port;
    char tx_port;
    uint8_t rx_pin;
    uint8_t tx_pin;

    void (*rcc_func)(uint32_t, FunctionalState);

    uint8_t nvic;
} USARTx[] = {
        {RCC_APB2Periph_USART1, USART1, 'A', 'A', 10, 9,  RCC_APB2PeriphClockCmd, USART1_IRQn},
        {RCC_APB1Periph_USART2, USART2, 'A', 'A', 3,  2,  RCC_APB1PeriphClockCmd, USART2_IRQn},
        {RCC_APB1Periph_USART3, USART3, 'B', 'B', 11, 10, RCC_APB1PeriphClockCmd, USART3_IRQn},
//        {RCC_APB1Periph_UART4, UART4, 0, 0, 0,0,  RCC_APB2PeriphClockCmd,UART4_IRQn  },
//        {RCC_APB1Periph_UART5, UART5, 0, 0, 0,0,  RCC_APB2PeriphClockCmd,UART5_IRQn  },
//        {RCC_APB2Periph_USART6, USART6, 0, 0, 0,0,  RCC_APB2PeriphClockCmd,USART6_IRQn },
//        {RCC_APB1Periph_UART7, UART7, 0, 0, 0,0,  RCC_APB2PeriphClockCmd,UART7_IRQn  },
//        {RCC_APB1Periph_UART8, UART8, 0, 0, 0,0,  RCC_APB2PeriphClockCmd,UART8_IRQn  },
//        {RCC_APB2Periph_UART9, UART9, 0, 0, 0,0,  RCC_APB2PeriphClockCmd,UART9_IRQn  },
//        {RCC_APB2Periph_UART10, UART10, 0, 0, 0,0,  RCC_APB2PeriphClockCmd,UART10_IRQn },
};

static struct {
    void *dat;

    void (*cb)(void *dat, char ch);
} USARTx_CB[3] = {
        {NULL, NULL},
        {NULL, NULL},
        {NULL, NULL},
};

usart::usart(uint8_t x, uint32_t rate) : x(x) {
    gpio rx = gpio(USARTx[x - 1].rx_port, USARTx[x - 1].rx_pin);
    gpio tx = gpio(USARTx[x - 1].tx_port, USARTx[x - 1].tx_pin);

    GPIO_InitTypeDef gpio_cfg;

    gpio_cfg.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    rx.init(&gpio_cfg);
    gpio_cfg.GPIO_Speed = GPIO_Speed_50MHz;
    gpio_cfg.GPIO_Mode = GPIO_Mode_AF_PP;
    tx.init(&gpio_cfg);

    USART_InitTypeDef uart_cfg;


    uart_cfg.USART_BaudRate = rate;
    uart_cfg.USART_WordLength = USART_WordLength_8b;
    uart_cfg.USART_StopBits = USART_StopBits_1;
    uart_cfg.USART_Parity = USART_Parity_No;
    uart_cfg.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    uart_cfg.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;


    NVIC_InitTypeDef nvic_cfg;
    nvic_cfg.NVIC_IRQChannel = USARTx[x - 1].nvic;
    nvic_cfg.NVIC_IRQChannelPreemptionPriority = 3;
    nvic_cfg.NVIC_IRQChannelSubPriority = 3;
    nvic_cfg.NVIC_IRQChannelCmd = ENABLE;


    USARTx[x - 1].rcc_func(USARTx[x - 1].rcc, ENABLE);

    USART_DeInit(USARTx[x - 1].dev);

    USART_Init(USARTx[x - 1].dev, &uart_cfg);

    NVIC_Init(&nvic_cfg);

    USART_ITConfig(USARTx[x - 1].dev, USART_IT_RXNE, ENABLE);

    USART_Cmd(USARTx[x - 1].dev, ENABLE);
}

void usart::open(void) {
    USART_Cmd(USARTx[x - 1].dev, ENABLE);
}

void usart::close(void) {
    USART_Cmd(USARTx[x - 1].dev, DISABLE);
}

bool usart::ready(void) {
    return USART_GetFlagStatus(USARTx[x - 1].dev, USART_FLAG_TXE) != RESET;
}

void usart::send(char c) {
    while (USART_GetFlagStatus(USARTx[x - 1].dev, USART_FLAG_TXE) == RESET);
    USART_SendData(USARTx[x - 1].dev, (uint16_t) c);
}

void usart::send(char *s) {
    do {
        send(*s);
        if (*s == '\0') break;
        else s++;
    } while (true);
}

void usart::recv(void (*func)(void *, char), void *dat) {
    USARTx_CB[x - 1].cb = func;
    USARTx_CB[x - 1].dat = dat;
}

extern "C" void USART1_IRQHandler(void) {
    char ch;
    if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET) {
        ch = (char) USART_ReceiveData(USART1);
        if (USARTx_CB[0].cb)USARTx_CB[0].cb(USARTx_CB[0].dat, ch);
        USART_ClearITPendingBit(USART1, USART_IT_RXNE);
    }
}

extern "C" void USART2_IRQHandler(void) {
    char ch;
    if (USART_GetITStatus(USART2, USART_IT_RXNE) != RESET) {
        ch = (char) USART_ReceiveData(USART2);
        if (USARTx_CB[1].cb)USARTx_CB[1].cb(USARTx_CB[1].dat, ch);
        USART_ClearITPendingBit(USART2, USART_IT_RXNE);
    }
}

extern "C" void USART3_IRQHandler(void) {
    char ch;
    if (USART_GetITStatus(USART3, USART_IT_RXNE) != RESET) {
        ch = (char) USART_ReceiveData(USART3);
        if (USARTx_CB[2].cb)USARTx_CB[2].cb(USARTx_CB[2].dat, ch);
        USART_ClearITPendingBit(USART3, USART_IT_RXNE);
    }
}

/////////////////////////////////////////////////////////////////

static const struct {
    ADC_TypeDef *dev;
    uint32_t rcc;
    uint8_t port[16];
    uint8_t pin[16];
} ADCx[] = {

/*
{
        ADC1, RCC_APB2Periph_ADC1,
        {'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'B', 'B', 'C', 'C', 'C', 'C', 'C', 'C'},
        { 0 ,  1 ,  2 ,  3 ,  4 ,  5 ,  6 ,  7 ,  0 ,  1 ,  0 ,  1 ,  2 ,  3 ,  4 ,  5}
},
{
        ADC2, RCC_APB2Periph_ADC2,
        {'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'B', 'B', 'C', 'C', 'C', 'C', 'C', 'C'},
        { 0 ,  1 ,  2 ,  3 ,  4 ,  5 ,  6 ,  7 ,  0 ,  1 ,  0 ,  1 ,  2 ,  3 ,  4 ,  5}
},
{
        ADC3, RCC_APB2Periph_ADC3,
        {'A', 'A', 'A', 'A', 'F', 'F', 'F', 'F', 'F', ' ', 'C', 'C', 'C', 'C', ' ', ' '},
        { 0 ,  1 ,  2 ,  3 ,  6 ,  7 ,  8 ,  9 ,  10,  0 ,  0 ,  1 ,  2 ,  3 ,  0 ,  0}
}
*/
        {
                ADC1, RCC_APB2Periph_ADC1,
                {'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'B', 'B', 'C', 'C', 'C', 'C', 'C', 'C'},
                {0, 1, 2, 3, 4, 5, 6, 7, 0,  1, 0, 1, 2, 3, 4, 5}
        },
        {
                ADC2, RCC_APB2Periph_ADC2,
                {'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'B', 'B', 'C', 'C', 'C', 'C', 'C', 'C'},
                {0, 1, 2, 3, 4, 5, 6, 7, 0,  1, 0, 1, 2, 3, 4, 5}
        },
        {
                ADC3, RCC_APB2Periph_ADC3,
                {'A', 'A', 'A', 'A', 'F', 'F', 'F', 'F', 'F', ' ', 'C', 'C', 'C', 'C', ' ', ' '},
                {0, 1, 2, 3, 6, 7, 8, 9, 10, 0, 0, 1, 2, 3, 0, 0}
        }
};

adc::adc(uint8_t x) : x(x) {

    ADC_InitTypeDef cfg;

    cfg.ADC_Mode = ADC_Mode_Independent;
    cfg.ADC_ContinuousConvMode = DISABLE;
    cfg.ADC_DataAlign = ADC_DataAlign_Right;
    cfg.ADC_ScanConvMode = ENABLE;
    cfg.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
    cfg.ADC_NbrOfChannel = 16;

    RCC_ADCCLKConfig(RCC_PCLK2_Div6);

    ADC_DeInit(ADCx[x - 1].dev);

    RCC_APB2PeriphClockCmd(ADCx[x - 1].rcc, ENABLE);

    ADC_Init(ADCx[x - 1].dev, &cfg);

    ADC_Cmd(ADCx[x - 1].dev, ENABLE);

    ADC_ResetCalibration(ADCx[x - 1].dev);
    while (ADC_GetResetCalibrationStatus(ADCx[x - 1].dev));
    ADC_StartCalibration(ADCx[x - 1].dev);
    while (ADC_GetCalibrationStatus(ADCx[x - 1].dev));

}

void adc::open(uint8_t ch) {
    GPIO_InitTypeDef cfg;
    cfg.GPIO_Mode = GPIO_Mode_AIN;
    gpio p = gpio(ADCx[x - 1].port[ch], ADCx[x - 1].pin[ch]);
    p.init(&cfg);
}

uint16_t adc::convert(uint8_t ch) {
    ADC_RegularChannelConfig(ADCx[x - 1].dev, ch, 1, ADC_SampleTime_239Cycles5);
    ADC_SoftwareStartConvCmd(ADCx[x - 1].dev, ENABLE);
    while (!ADC_GetFlagStatus(ADCx[x - 1].dev, ADC_FLAG_EOC));
    return ADC_GetConversionValue(ADCx[x - 1].dev);
}

bool adc::aleady() {
    return ADC_GetFlagStatus(ADCx[x - 1].dev, ADC_FLAG_EOC);
}

void adc::start(uint8_t ch) {
    ADC_RegularChannelConfig(ADCx[x - 1].dev, ch, 1, ADC_SampleTime_239Cycles5);
    ADC_SoftwareStartConvCmd(ADCx[x - 1].dev, ENABLE);
}

uint16_t adc::read() {
    return ADC_GetConversionValue(ADCx[x - 1].dev);
}

void adc::close(uint8_t ch) {
    GPIO_InitTypeDef cfg;
    cfg.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    gpio p = gpio(ADCx[x - 1].port[ch], ADCx[x - 1].pin[ch]);
    p.init(&cfg);
}

/////////////////////////////////////////////////////////////////////////////////////

static const uint8_t GPIO_PortSourceGPIOx[] = {
        GPIO_PortSourceGPIOA, GPIO_PortSourceGPIOB, GPIO_PortSourceGPIOC,
        GPIO_PortSourceGPIOD, GPIO_PortSourceGPIOE, GPIO_PortSourceGPIOF,
        GPIO_PortSourceGPIOG
};

static const struct {
    uint32_t dev;
    uint8_t nvic;
} EXTIx[] = {
        {EXTI_Line0,  EXTI0_IRQn},
        {EXTI_Line1,  EXTI1_IRQn},
        {EXTI_Line2,  EXTI2_IRQn},
        {EXTI_Line3,  EXTI3_IRQn},
        {EXTI_Line4,  EXTI4_IRQn},
        {EXTI_Line5,  EXTI9_5_IRQn},
        {EXTI_Line6,  EXTI9_5_IRQn},
        {EXTI_Line7,  EXTI9_5_IRQn},
        {EXTI_Line8,  EXTI9_5_IRQn},
        {EXTI_Line9,  EXTI9_5_IRQn},
        {EXTI_Line10, EXTI15_10_IRQn},
        {EXTI_Line11, EXTI15_10_IRQn},
        {EXTI_Line12, EXTI15_10_IRQn},
        {EXTI_Line13, EXTI15_10_IRQn},
        {EXTI_Line14, EXTI15_10_IRQn},
        {EXTI_Line15, EXTI15_10_IRQn},
};

exti::exti(uint8_t port, uint8_t line) : port(port), line(line) {
    NVIC_InitTypeDef nvic_cfg;

    nvic_cfg.NVIC_IRQChannel = EXTIx[line].nvic;
    nvic_cfg.NVIC_IRQChannelPreemptionPriority = 0x01;
    nvic_cfg.NVIC_IRQChannelSubPriority = 0x02;
    nvic_cfg.NVIC_IRQChannelCmd = ENABLE;

    GPIO_EXTILineConfig(GPIO_PortSourceGPIOx[port - 'A'], GPIO_PinSourcex[line]);
    NVIC_Init(&nvic_cfg);
}

static struct {
    void (*func)(void *);

    void *dat;
} EXTI_CB[] = {
        {NULL, NULL},
        {NULL, NULL},
        {NULL, NULL},
        {NULL, NULL},
        {NULL, NULL},
        {NULL, NULL},
        {NULL, NULL},
        {NULL, NULL},
        {NULL, NULL},
        {NULL, NULL},
        {NULL, NULL},
        {NULL, NULL},
        {NULL, NULL},
        {NULL, NULL},
        {NULL, NULL},
        {NULL, NULL}
};

void exti::onrising(void (*func)(void *), void *dat) {
    EXTI_CB[line].func = func;
    EXTI_CB[line].dat = dat;
    EXTI_InitTypeDef exti_cfg;
    exti_cfg.EXTI_Line = EXTIx[line].dev;
    exti_cfg.EXTI_Mode = EXTI_Mode_Interrupt;
    exti_cfg.EXTI_Trigger = EXTI_Trigger_Rising;
    exti_cfg.EXTI_LineCmd = ENABLE;
    EXTI_Init(&exti_cfg);
}

void exti::onfalling(void (*func)(void *), void *dat) {
    EXTI_CB[line].func = func;
    EXTI_CB[line].dat = dat;
    EXTI_InitTypeDef exti_cfg;
    exti_cfg.EXTI_Line = EXTIx[line].dev;
    exti_cfg.EXTI_Mode = EXTI_Mode_Interrupt;
    exti_cfg.EXTI_Trigger = EXTI_Trigger_Falling;
    exti_cfg.EXTI_LineCmd = ENABLE;
    EXTI_Init(&exti_cfg);
}

void exti::onchange(void (*func)(void *), void *dat) {
    EXTI_CB[line].func = func;
    EXTI_CB[line].dat = dat;
    EXTI_InitTypeDef exti_cfg;
    exti_cfg.EXTI_Line = EXTIx[line].dev;
    exti_cfg.EXTI_Mode = EXTI_Mode_Interrupt;
    exti_cfg.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
    exti_cfg.EXTI_LineCmd = ENABLE;
    EXTI_Init(&exti_cfg);
}

void exti::close(void) {
    EXTI_CB[line].func = NULL;
    EXTI_InitTypeDef exti_cfg;
    exti_cfg.EXTI_Line = EXTIx[line].dev;
    exti_cfg.EXTI_LineCmd = DISABLE;
    EXTI_Init(&exti_cfg);
}

extern "C" void EXTI0_IRQHandler(void) {
    if (EXTI_GetITStatus(EXTI_Line0) != RESET) {
        if (EXTI_CB[0].func)EXTI_CB[0].func(EXTI_CB[0].dat);
        EXTI_ClearITPendingBit(EXTI_Line0);
    }
}

extern "C" void EXTI1_IRQHandler(void) {
    if (EXTI_GetITStatus(EXTI_Line1) != RESET) {
        if (EXTI_CB[1].func)EXTI_CB[1].func(EXTI_CB[1].dat);
        EXTI_ClearITPendingBit(EXTI_Line1);
    }
}

extern "C" void EXTI2_IRQHandler(void) {
    if (EXTI_GetITStatus(EXTI_Line2) != RESET) {
        if (EXTI_CB[2].func)EXTI_CB[2].func(EXTI_CB[2].dat);
        EXTI_ClearITPendingBit(EXTI_Line2);
    }
}

extern "C" void EXTI3_IRQHandler(void) {
    if (EXTI_GetITStatus(EXTI_Line3) != RESET) {
        if (EXTI_CB[3].func)EXTI_CB[3].func(EXTI_CB[3].dat);
        EXTI_ClearITPendingBit(EXTI_Line3);
    }
}

extern "C" void EXTI4_IRQHandler(void) {
    if (EXTI_GetITStatus(EXTI_Line4) != RESET) {
        if (EXTI_CB[4].func)EXTI_CB[4].func(EXTI_CB[4].dat);
        EXTI_ClearITPendingBit(EXTI_Line4);
    }
}

extern "C" void EXTI9_5_IRQHandler(void) {
    if (EXTI_GetITStatus(EXTI_Line5) != RESET) {
        if (EXTI_CB[5].func)EXTI_CB[5].func(EXTI_CB[5].dat);
        EXTI_ClearITPendingBit(EXTI_Line5);
    }
    if (EXTI_GetITStatus(EXTI_Line6) != RESET) {
        if (EXTI_CB[6].func)EXTI_CB[6].func(EXTI_CB[6].dat);
        EXTI_ClearITPendingBit(EXTI_Line6);
    }
    if (EXTI_GetITStatus(EXTI_Line7) != RESET) {
        if (EXTI_CB[7].func)EXTI_CB[7].func(EXTI_CB[7].dat);
        EXTI_ClearITPendingBit(EXTI_Line7);
    }
    if (EXTI_GetITStatus(EXTI_Line8) != RESET) {
        if (EXTI_CB[8].func)EXTI_CB[8].func(EXTI_CB[8].dat);
        EXTI_ClearITPendingBit(EXTI_Line8);
    }
    if (EXTI_GetITStatus(EXTI_Line9) != RESET) {
        if (EXTI_CB[9].func)EXTI_CB[9].func(EXTI_CB[9].dat);
        EXTI_ClearITPendingBit(EXTI_Line9);
    }
}

extern "C" void EXTI15_10_IRQHandler(void) {
    if (EXTI_GetITStatus(EXTI_Line10) != RESET) {
        if (EXTI_CB[10].func)EXTI_CB[10].func(EXTI_CB[10].dat);
        EXTI_ClearITPendingBit(EXTI_Line10);
    }
    if (EXTI_GetITStatus(EXTI_Line11) != RESET) {
        if (EXTI_CB[11].func)EXTI_CB[11].func(EXTI_CB[11].dat);
        EXTI_ClearITPendingBit(EXTI_Line11);
    }
    if (EXTI_GetITStatus(EXTI_Line12) != RESET) {
        if (EXTI_CB[12].func)EXTI_CB[12].func(EXTI_CB[12].dat);
        EXTI_ClearITPendingBit(EXTI_Line12);
    }
    if (EXTI_GetITStatus(EXTI_Line13) != RESET) {
        if (EXTI_CB[13].func)EXTI_CB[13].func(EXTI_CB[13].dat);
        EXTI_ClearITPendingBit(EXTI_Line13);
    }
    if (EXTI_GetITStatus(EXTI_Line14) != RESET) {
        if (EXTI_CB[14].func)EXTI_CB[14].func(EXTI_CB[14].dat);
        EXTI_ClearITPendingBit(EXTI_Line14);
    }
    if (EXTI_GetITStatus(EXTI_Line15) != RESET) {
        if (EXTI_CB[15].func)EXTI_CB[15].func(EXTI_CB[15].dat);
        EXTI_ClearITPendingBit(EXTI_Line15);
    }
}

/////////////////////////////////////////////////////////////////////////////////////////

// Tout= ((arr+1)*(psc+1))/Tclk;

static struct {
    void (*func)(void *);

    void *dat;
} GTIMx_CB[5] = {
        {NULL, NULL},
        {NULL, NULL},
        {NULL, NULL},
        {NULL, NULL},
        {NULL, NULL},
};

const static struct {
    TIM_TypeDef *dev;

    void (*rcc_func)(uint32_t, FunctionalState);

    uint32_t rcc;
    uint8_t nvic;
} TIMx[] = {
        {TIM1, RCC_APB2PeriphClockCmd, RCC_APB2Periph_TIM1},
        {TIM2, RCC_APB1PeriphClockCmd, RCC_APB1Periph_TIM2, TIM2_IRQn},
        {TIM3, RCC_APB1PeriphClockCmd, RCC_APB1Periph_TIM3, TIM3_IRQn},
        {TIM4, RCC_APB1PeriphClockCmd, RCC_APB1Periph_TIM4, TIM4_IRQn},
};

time::time(uint8_t x) : x(x) {
    TIM_TimeBaseInitTypeDef tim_timeBase;
    NVIC_InitTypeDef nvic_cfg;

    tim_timeBase.TIM_Period = 999;
    tim_timeBase.TIM_Prescaler =
            (uint16_t) (TIMx[x - 1].rcc_func == RCC_APB1PeriphClockCmd ? 71 : 35);
    tim_timeBase.TIM_CounterMode = TIM_CounterMode_Up;
    tim_timeBase.TIM_ClockDivision = TIM_CKD_DIV1;

    nvic_cfg.NVIC_IRQChannel = TIMx[x - 1].nvic;
    nvic_cfg.NVIC_IRQChannelPreemptionPriority = 0x01;
    nvic_cfg.NVIC_IRQChannelSubPriority = 0x03;
    nvic_cfg.NVIC_IRQChannelCmd = ENABLE;

    TIMx[x - 1].rcc_func(TIMx[x - 1].rcc, ENABLE);
    TIM_TimeBaseInit(TIMx[x - 1].dev, &tim_timeBase);
    TIM_ITConfig(TIMx[x - 1].dev, TIM_IT_Update, ENABLE);
    NVIC_Init(&nvic_cfg);
    TIM_Cmd(TIMx[x - 1].dev, ENABLE);
}

void time::period(uint32_t p) {
    TIM_TimeBaseInitTypeDef tim_timeBase;
    tim_timeBase.TIM_Period = p - 1;
    tim_timeBase.TIM_Prescaler =
            (uint16_t) (TIMx[x - 1].rcc_func == RCC_APB1PeriphClockCmd ? 71 : 35);
    tim_timeBase.TIM_CounterMode = TIM_CounterMode_Up;
    tim_timeBase.TIM_ClockDivision = TIM_CKD_DIV1;

    TIM_TimeBaseInit(TIMx[x - 1].dev, &tim_timeBase);
}

void time::setCallback(void (*cb)(void *), void *dat) {
    GTIMx_CB[x].func = cb;
    GTIMx_CB[x].dat = dat;
}

void time::stop(void) {
    TIM_Cmd(TIMx[x - 1].dev, DISABLE);
}

void time::start(void) {
    TIM_Cmd(TIMx[x - 1].dev, ENABLE);
}


extern "C" void TIM2_IRQHandler(void) {
    if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET) {
        if (GTIMx_CB[2].func)GTIMx_CB[2].func(GTIMx_CB[2].dat);
        TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
    }
}

extern "C" void TIM3_IRQHandler(void) {
    if (TIM_GetITStatus(TIM3, TIM_IT_Update) == SET) {
        if (GTIMx_CB[3].func)GTIMx_CB[3].func(GTIMx_CB[3].dat);
        TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
    }
}

extern "C" void TIM4_IRQHandler(void) {
    if (TIM_GetITStatus(TIM4, TIM_IT_Update) == SET) {
        if (GTIMx_CB[4].func)GTIMx_CB[4].func(GTIMx_CB[4].dat);
        TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
    }
}

extern "C" void TIM5_IRQHandler(void) {
    if (TIM_GetITStatus(TIM5, TIM_IT_Update) == SET) {
        if (GTIMx_CB[5].func)GTIMx_CB[5].func(GTIMx_CB[5].dat);
        TIM_ClearITPendingBit(TIM5, TIM_IT_Update);
    }
}

////////////////////////////////////////////////////////////////////////////////////////
const static struct {
    SPI_TypeDef *dev;

    struct {
        char clock_port;
        uint8_t clock_pin;
        char miso_port;
        uint8_t miso_pin;
        char mosi_port;
        uint8_t mosi_pin;
    } io;

    void (*rcc_fun)(uint32_t, FunctionalState);

    uint32_t rcc;

    uint8_t nvic;
} SPIX[] = {
        {SPI1, {'A', 5,  'A', 6,  'A', 7},  RCC_APB2PeriphClockCmd, RCC_APB2Periph_SPI1, SPI1_IRQn},
        {SPI2, {'B', 13, 'B', 14, 'B', 15}, RCC_APB1PeriphClockCmd, RCC_APB1Periph_SPI2, SPI2_IRQn},
        {SPI3, {},                          RCC_APB1PeriphClockCmd, RCC_APB1Periph_SPI3, 0},
};

static struct {
    void (*recv_func)(void *obj, uint16_t dat);

    void *obj;
} SPI_RECV[] = {
        {NULL, NULL},
        {NULL, NULL},
        {NULL, NULL},
        {NULL, NULL},
};

spi::spi(uint8_t x) : x(x) {
    NVIC_InitTypeDef nvic_cfg;

    nvic_cfg.NVIC_IRQChannel = SPIX[x - 1].nvic;
    nvic_cfg.NVIC_IRQChannelSubPriority = 0x03;
    nvic_cfg.NVIC_IRQChannelPreemptionPriority = 0x3;
    nvic_cfg.NVIC_IRQChannelCmd = ENABLE;

    SPIX[x - 1].rcc_fun(SPIX[x - 1].rcc, ENABLE);

    init_master();

    NVIC_Init(&nvic_cfg);

    SPI_Cmd(SPIX[x - 1].dev, ENABLE);
}

void spi::init(SPI_InitTypeDef *cfg) {
    SPI_Init(SPIX[x - 1].dev, cfg);
}

void spi::init_slave(void) {

    GPIO_InitTypeDef gpio_cfg;
    gpio_cfg.GPIO_Speed = GPIO_Speed_50MHz;

    gpio clk = gpio(SPIX[x - 1].io.clock_port, SPIX[x - 1].io.clock_pin);
    gpio miso = gpio(SPIX[x - 1].io.miso_port, SPIX[x - 1].io.miso_pin);
    gpio mosi = gpio(SPIX[x - 1].io.mosi_port, SPIX[x - 1].io.mosi_pin);
    clk.init_input();
    mosi.init_input();
    gpio_cfg.GPIO_Mode = GPIO_Mode_AF_PP;
    miso.init(&gpio_cfg);

    SPI_InitTypeDef cfg;
    cfg.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
    cfg.SPI_Mode = SPI_Mode_Slave;
    cfg.SPI_DataSize = SPI_DataSize_8b;
    cfg.SPI_CPOL = SPI_CPOL_High;
    cfg.SPI_CPHA = SPI_CPHA_2Edge;
    cfg.SPI_NSS = SPI_NSS_Soft;
    cfg.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;
    cfg.SPI_FirstBit = SPI_FirstBit_MSB;
    cfg.SPI_CRCPolynomial = 7;
    init(&cfg);

//    SPI_I2S_ITConfig(SPIX[x - 1].dev, SPI_I2S_IT_RXNE, ENABLE);
}

void spi::init_master(void) {

    GPIO_InitTypeDef gpio_cfg;
    gpio_cfg.GPIO_Speed = GPIO_Speed_50MHz;

    gpio clk = gpio(SPIX[x - 1].io.clock_port, SPIX[x - 1].io.clock_pin);
    gpio miso = gpio(SPIX[x - 1].io.miso_port, SPIX[x - 1].io.miso_pin);
    gpio mosi = gpio(SPIX[x - 1].io.mosi_port, SPIX[x - 1].io.mosi_pin);
    miso.init_input();
    gpio_cfg.GPIO_Mode = GPIO_Mode_AF_PP;
    mosi.init(&gpio_cfg);
    clk.init(&gpio_cfg);

    SPI_InitTypeDef cfg;
    cfg.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
    cfg.SPI_Mode = SPI_Mode_Master;
    cfg.SPI_DataSize = SPI_DataSize_8b;
    cfg.SPI_CPOL = SPI_CPOL_High;
    cfg.SPI_CPHA = SPI_CPHA_2Edge;
    cfg.SPI_NSS = SPI_NSS_Soft;
    cfg.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;
    cfg.SPI_FirstBit = SPI_FirstBit_MSB;
    cfg.SPI_CRCPolynomial = 7;
    init(&cfg);

//    SPI_I2S_ITConfig(SPIX[x - 1].dev, SPI_I2S_IT_RXNE, DISABLE);
}

void spi::recv(void (*fun)(void *, uint16_t), void *obj) {
    SPI_RECV[x - 1].recv_func = fun;
    SPI_RECV[x - 1].obj = obj;
}

void spi::send(uint16_t dat) {
    while (SPI_I2S_GetFlagStatus(SPIX[x - 1].dev, SPI_I2S_FLAG_TXE) == RESET);
    SPI_I2S_SendData(SPIX[x - 1].dev, dat);
}

bool spi::ready(void) {
    return SPI_I2S_GetFlagStatus(SPIX[x - 1].dev, SPI_I2S_FLAG_TXE) != RESET;
}

uint16_t spi::read(void) {
    return SPI_I2S_ReceiveData(SPIX[x - 1].dev);
}

uint16_t spi::exchange(uint16_t dat) {
    SPI_I2S_SendData(SPIX[x - 1].dev, dat);
    while (SPI_I2S_GetFlagStatus(SPIX[x - 1].dev, SPI_I2S_FLAG_TXE) != SET);
    return SPI_I2S_ReceiveData(SPIX[x - 1].dev);
}

#include "stdio.h"

extern "C" void SPI1_IRQHandler(void) {
    if (SPI_I2S_GetITStatus(SPI1, SPI_I2S_IT_RXNE) != RESET) {
        if (SPI_RECV[0].recv_func)SPI_RECV[0].recv_func(SPI_RECV[0].obj, (uint16_t) SPI_I2S_ReceiveData(SPI1));
        SPI_I2S_ClearITPendingBit(SPI1, SPI_I2S_IT_RXNE);
    }
}

extern "C" void SPI2_IRQHandler(void) {
    if (SPI_I2S_GetITStatus(SPI2, SPI_I2S_IT_RXNE) != RESET) {
        if (SPI_RECV[1].recv_func)SPI_RECV[1].recv_func(SPI_RECV[1].obj, (uint16_t) SPI_I2S_ReceiveData(SPI2));
        SPI_I2S_ClearITPendingBit(SPI2, SPI_I2S_IT_RXNE);
    }
}

extern "C" void SPI3_IRQHandler(void) {
    if (SPI_I2S_GetITStatus(SPI3, SPI_I2S_IT_RXNE) != RESET) {
        if (SPI_RECV[2].recv_func)SPI_RECV[2].recv_func(SPI_RECV[2].obj, (uint16_t) SPI_I2S_ReceiveData(SPI3));
        SPI_I2S_ClearITPendingBit(SPI3, SPI_I2S_IT_RXNE);
    }
}
