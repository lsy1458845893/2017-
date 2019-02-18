#ifndef LED_H
#define LED_H

#include "stm32f4xx.h"
#include "delay.h"
#include <stdint-gcc.h>

class Led {
private:
    GPIO_TypeDef *family;
    uint16_t port;

public:
    char status = 0;

    Led(GPIO_TypeDef *family, uint32_t pin);

    void change(void);

    static void callback(void *data) {
        Led *led = (Led *) data;
        led->change();
    };


};

#endif