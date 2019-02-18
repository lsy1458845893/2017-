//
// Created by lsy on 17-7-12.
//

#ifndef STM32F4_COLOR_H
#define STM32F4_COLOR_H

#include "stdint.h"

class Color {
public:
    uint8_t alpha, r, g, b;

    Color(uint8_t alpha, uint8_t r, uint8_t g, uint8_t b)
            : alpha(alpha), r(r), g(g), b(b) {}

    Color(uint8_t r, uint8_t g, uint8_t b)
            : alpha(255), r(r), g(g), b(b) {}

    Color(uint32_t c) {
        b = (uint8_t) (0xff & c);
        c >>= 8;
        g = (uint8_t) (0xff & c);
        c >>= 8;
        r = (uint8_t) (0xff & c);
        c >>= 8;
        alpha = (uint8_t) (0xff & c);
    }

    uint32_t get() {
        uint32_t ret = 0;
        ret |= alpha;
        ret <<= 8;
        ret |= r;
        ret <<= 8;
        ret |= g;
        ret <<= 8;
        ret |= b;
        return ret;
    }

    Color over(Color c) {
        float a = ((float) alpha) / 255;
        c.r = (uint8_t) (a * r + (1 - a) * c.r);
        c.g = (uint8_t) (a * g + (1 - a) * c.g);
        c.b = (uint8_t) (a * b + (1 - a) * c.b);
        c.alpha = 255;
        return c;
    }

    uint16_t convert(void) {
        uint8_t tr, tg, tb;
        tr = (uint8_t) (r * 0.125);
        tg = (uint8_t) (g * 0.25);
        tb = (uint8_t) (b * 0.125);
        return (uint16_t) ((tr << 11) | (tg << 5) | (tb << 0));
    }
};

#endif //STM32F4_COLOR_H
