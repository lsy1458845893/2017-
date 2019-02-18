//
// Created by lsy on 17-7-12.
//

#ifndef STM32F4_OS_H
#define STM32F4_OS_H

#include "stdint.h"
#include "device.hpp"

void os_init(uint8_t dev,char port,char pin);

void setInterval(void(*cb)(void *), void *dat, uint32_t timeout);

void setTimeout(void(*cb)(void *), void *dat, uint32_t timeout);

void setTimeout(void(*cb)(void *), void *dat, uint32_t timeout, uint32_t times);

uint32_t os_execult(void);

void os_stop(void);

void os_start(void);

#endif //STM32F4_OS_H
