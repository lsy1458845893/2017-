#ifndef LED_H
#define LED_H

#include "stm32f10x.h"

class Led {
private:
    GPIO_TypeDef *fmy;
    uint16_t pin;

public:
    char status = 0;

    Led(GPIO_TypeDef *fmy, uint16_t pin);

    void change(void);

    static void change(void *led) { ((Led *) led)->change(); }
};

#endif