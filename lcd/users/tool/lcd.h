//
// Created by lsy on 17-5-17.
//

#ifndef TEMPLATE_LCD_H
#define TEMPLATE_LCD_H


#include "stm32f4xx.h"

#include "lcd_dev.h"

class Lcd {

public:
    LCD_DEV *lcd;
    // 480 800
    u16 w, h;

    Lcd(LCD_DEV *_lcd) : lcd(_lcd), w(_lcd->w), h(_lcd->h) {}

    void cursor(u16 x, u16 y) { lcd->cursor(x, y); }

    void write(u16 c) { lcd->write(c); }

    void dot(u16 x, u16 y, u16 c);

    u16 dot(u16 x, u16 y);

    void line(u16 x0, u16 y0, u16 x1, u16 y1, u16 c);

    void rect(u16 x0, u16 y0, u16 x1, u16 y1, u16 c);

    void print(u16 x, u16 y, char ch, u16 c, u16 b);

    void print(u16 x, u16 y, char *str, u16 c, u16 b);

    void draw(u16 x, u16 y, char *img, u16 w, u16 h, u16 c, u16 b);
};


#endif //TEMPLATE_LCD_H
