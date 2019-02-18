//
// Created by lsy on 17-5-17.
//

#ifndef TEMPLATE_COLOR_H
#define TEMPLATE_COLOR_H

#include "stm32f4xx.h"

static class _lcd_color_ {
public:
    u16 WHITE = 0xFFFF;
    u16 BLACK = 0x0000;
    u16 BLUE = 0x001F;
    u16 BRED = 0XF81F;
    u16 GRED = 0XFFE0;
    u16 GBLUE = 0X07FF;
    u16 RED = 0xF800;
    u16 MAGENTA = 0xF81F;
    u16 GREEN = 0x07E0;
    u16 CYAN = 0x7FFF;
    u16 YELLOW = 0xFFE0;
    u16 BROWN = 0XBC40;
    u16 BRRED = 0XFC07;
    u16 GRAY = 0X8430;
    u16 DARKBLUE = 0X01CF;
    u16 LIGHTBLUE = 0X7D7C;
    u16 GRAYBLUE = 0X5458;
    u16 LIGHTGREEN = 0X841F;
    u16 LGRAY = 0XC618;
    u16 LGRAYBLUE = 0XA651;
    u16 LBBLUE = 0X2B12;
} const color;

#endif //TEMPLATE_COLOR_H
