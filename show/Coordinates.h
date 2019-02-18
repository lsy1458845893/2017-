//
// Created by lsy on 17-7-12.
//

#ifndef STM32F4_COORDINATES_H
#define STM32F4_COORDINATES_H

#include "Frame.h"

class Coordinates : public Frame {
private:
    struct Line {
        uint16_t st;
        Color c;
    };

public:

    Coordinates(uint16_t x, uint16_t y) {
        offset_x = x;
        offset_y = y;
        width = 601;
        height = 401;
    }

    Color dot(uint16_t x, uint16_t y) {
        const Color a = Color(0, 0, 0),
                b = Color(100, 100, 100),
                c = Color(200, 200, 200);
        if (x % 50 && y % 50) return a;
        if (x % 100 && y % 100) return b;
        return c;
    }

};

#endif //STM32F4_COORDINATES_H
