//
// Created by lsy on 17-7-15.
//

#ifndef STM32F4_TOUCH_H
#define STM32F4_TOUCH_H

#include "stdint.h"


class Touch {
public:
    struct {
        uint16_t x;
        uint16_t y;
        bool press;
    } points[5];

    void update(void);
};


#endif //STM32F4_TOUCH_H
