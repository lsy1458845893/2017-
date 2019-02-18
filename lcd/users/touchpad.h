//
// Created by lsy on 17-5-19.
//

#ifndef TEMPLATE_TOUCHPAD_H
#define TEMPLATE_TOUCHPAD_H

#include "touch.h"
#include <stdint-gcc.h>

class Touchpad {

public:

    Touchpad(LCD_DEV *lcd) { TP_Init(lcd); }

    uint8_t scan(void) { return tp_dev.scan(0); }

    uint16_t x(void) { return tp_dev.x[0]; }

    uint16_t y(void) { return tp_dev.y[0]; }

    uint8_t press(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1) {
        return (uint8_t) (tp_dev.sta & 0x40 ?
                          (x0 <= tp_dev.x[0] && tp_dev.x[0] <= x1 &&
                           y0 <= tp_dev.y[0] && tp_dev.y[0]) <= y1 : 0);
    }

    uint8_t press(void) { return tp_dev.sta & 0x40; }
};


#endif //TEMPLATE_TOUCHPAD_H
