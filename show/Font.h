//
// Created by lsy on 17-7-12.
//

#ifndef STM32F4_FONT_H
#define STM32F4_FONT_H

#include "Frame.h"
#include "Color.h"
#include "stdlib.h"
#include "string.h"

class Font : public Frame {
private:
    char *str = NULL;
public:

    Color c;

    Font(char *init, uint16_t x, uint16_t y) : c(Color(255, 255, 255)) {
        offset_x = x;
        offset_y = y;
        width = (uint16_t) (6 * strlen(init));
        height = 8;
        str = (char *) malloc(strlen(init) + 1);
        strcpy(str, init);
    }

    Color dot(uint16_t x, uint16_t y);
};

#endif //STM32F4_FONT_H
