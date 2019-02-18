//
// Created by lsy on 17-7-12.
//

#ifndef STM32F4_SCREEN_H
#define STM32F4_SCREEN_H

#include <lcd_dev.h>
#include "Color.h"

#include "Frame.h"
#include "lcd_dev.h"

class Screen : public Frame {
private:
    LCD_DEV *lcd_dev;
    Color c;
public:
    Screen(LCD_DEV *lcd_dev, Color c) : lcd_dev(lcd_dev), c(c) {
        offset_y = 0;
        offset_x = 0;
        width = lcd_dev->w;
        height = lcd_dev->h;
    }

    Screen(LCD_DEV *lcd_dev) : lcd_dev(lcd_dev), c(Color(0, 0, 0)) {}

    Color dot(uint16_t x, uint16_t y) { return c; }

    void dot(uint16_t x, uint16_t y, Color c) { lcd_dev->dot(x, y, c.convert()); }

    void cursor(uint16_t x, uint16_t y) { lcd_dev->cursor(x, y); }

    void write(Color c) { LCD->LCD_RAM = c.convert(); }

    void restore(void) {
        lcd_dev->clear(c.convert());
        restore_chlidren();
    }
};




#endif //STM32F4_SCREEN_H
