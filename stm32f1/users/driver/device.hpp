//
// Created by lsy on 17-6-20.
//

#ifndef STM32F1_DEVICE_H
#define STM32F1_DEVICE_H

#include "stdint.h"
#include "stdlib.h"
#include "stm32f10x.h"

namespace dev {

    void SysTick_init(uint8_t p);

    void SysTick_emit(void(*func)(void *), void *dat, uint32_t us);

    bool SysTick_aleady(void);

    class gpio {
    private:
        char port;
        uint8_t pin;
        bool state = false;
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

        static void send(void *u, char ch) { ((usart *) u)->send(ch); }

        bool ready(void);

        void send(char c);

        void send(char *s);

        void open(void);

        void close(void);
    };

/*
 *    通道号  1     2     3
 * 通道  0   A0    A0    A0
 * 通道  1   A1    A1    A1
 * 通道  2   A2    A2    A2
 * 通道  3   A3    A3    A3
 * 通道  4   A4    A4    F6
 * 通道  5   A5    A5    F7
 * 通道  6   A6    A6    F8
 * 通道  7   A7    A7    F9
 * 通道  8   B0    B0    F10
 * 通道  9   B1    B1
 * 通道  10  C0    C0    C0
 * 通道  11  C1    C1    C1
 * 通道  12  C2    C2    C2
 * 通道  13  C3    C3    C3
 * 通道  14  C4    C4
 * 通道  15  C5    C5
 * 通道  16  ins
 * 通道  17  ref
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

#endif //STM32F1_DEVICE_H
