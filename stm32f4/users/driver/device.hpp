//
// Created by lsy on 17-6-20.
//

#ifndef STM32F4_DEVICE_H
#define STM32F4_DEVICE_H

#include "stdint.h"
#include "stdlib.h"
#include "stm32f4xx.h"

namespace dev {

    void SysTick_init(uint8_t p);

    void SysTick_emit(void(*func)(void *), void *dat, uint32_t us);

    bool SysTick_aleady(void);

    class gpio {
    private:
        char port;
        uint8_t pin;
    public:
        gpio(char port, uint8_t pin) : port(port), pin(pin) { init_output(); }

        void init(GPIO_InitTypeDef *s);

        void init_output(void);

        void init_input(void);

        void output(bool s);

        void toggle(void);

        bool read(void);

        static void toggle(void *d) { ((gpio *) d)->toggle(); }
    };

    class usart {
    private:
        uint8_t x;
    public:
        usart(uint8_t x, uint32_t rate);

        void recv(void(*)(void *, char), void *dat);

        bool ready(void);

        static void send(void *t, char c) { ((usart *) t)->send(c); }

        void send(char c);

        void send(char *s);

        void open(void);

        void close(void);
    };

/**
 *    通道号 ADC1  ADC2  ADC3
 * 通道  0   PA0   PA0   PA0
 * 通道  1   PA1   PA1   PA1
 * 通道  2   PA2   PA2   PA2
 * 通道  3   PA3   PA3   PA3
 * 通道  4   PA4   PA4   PF6
 * 通道  5   PA5   PA5   PF7
 * 通道  6   PA6   PA6   PF8
 * 通道  7   PA7   PA7   PF9
 * 通道  8   PB0   PB0   PF10
 * 通道  9   PB1   PB1   PF3
 * 通道  10  PC0   PC0   PC0
 * 通道  11  PC1   PC1   PC1
 * 通道  12  PC2   PC2   PC2
 * 通道  13  PC13  PC13  PC13
 * 通道  14  PC4   PC4   PF4
 * 通道  15  PC5   PC5   PF5
 */
    class adc {
        uint8_t x;
    public:
        adc(uint8_t x);

        void open(uint8_t ch);

        void close(uint8_t ch);

        uint16_t convert(uint8_t ch);

        void start(uint8_t ch);

        bool aleady(void);

        uint16_t read(void);
    };

    class exti {
    private:
        char port;
        uint8_t line;
    public:
        exti(uint8_t port, uint8_t line);

        void close(void);

        void onrising(void(*func)(void *), void *dat);

        void onfalling(void(*func)(void *), void *dat);

        void onchange(void(*func)(void *), void *dat);
    };

    class time {
    private:
        uint8_t x;
    public:
        time(uint8_t x);

        void period(uint32_t p);

        void setCallback(void(*cb)(void *), void *dat);

        void stop(void);

        void start(void);
    };

    class spi {
    private:
        uint8_t x;
    public:
        spi(uint8_t x);

        void init(SPI_InitTypeDef *cfg);

        void init_slave(void);

        void init_master(void);

        void recv(void(*)(void *, uint16_t dat), void *obj);

        void send(uint16_t dat);

        bool ready(void);

        uint16_t read(void);

        uint16_t exchange(uint16_t dat);
    };
}


void delay_init(u8 SYSCLK);

void delay_us(u32 nus);

void delay_xms(u16 nms);

void delay_ms(u16 nms);

#endif //STM32F4_DEVICE_H
