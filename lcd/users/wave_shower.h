//
// Created by lsy on 17-5-18.
//

#ifndef TEMPLATE_WAVE_SHOWER_H
#define TEMPLATE_WAVE_SHOWER_H

#include "stm32f4xx.h"
#include "lcd.h"

#include <stdint-gcc.h>

class Wave_shower {
    uint8_t sta = 0;

    uint16_t xoffset, yoffset;
    Lcd *lcd;

    uint16_t lcd_x(uint16_t show_x) { return xoffset + show_x; }

    uint16_t lcd_y(uint16_t show_y) { return yoffset + h - show_y; }

    uint16_t grid_color(uint16_t x, uint16_t y);

public:
    const static uint16_t w = 600, h = 400;

    Wave_shower(Lcd *lcd, uint16_t x, uint16_t y) : lcd(lcd), xoffset(x), yoffset(y) {}

    void prepare(void);

    void clear(uint16_t x, uint16_t y);

    void draw(uint16_t x, uint16_t y, uint16_t c);

    void clear(uint16_t *wave);

    void draw(uint16_t *wave, uint16_t c);

};


#endif //TEMPLATE_WAVE_SHOWER_H
