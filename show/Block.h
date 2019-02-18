//
// Created by lsy on 17-7-12.
//

#ifndef STM32F4_BLOCK_H
#define STM32F4_BLOCK_H

#include "Frame.h"
#include "Color.h"


class Block : public Frame {
private:
    Color c;
public:
    Block(Color c, uint16_t x, uint16_t y, uint16_t w, uint16_t h) : c(c) {
        offset_x = x;
        offset_y = y;
        width = w;
        height = h;
    }

    Color dot(uint16_t x, uint16_t y) { return c; }
};


#endif
