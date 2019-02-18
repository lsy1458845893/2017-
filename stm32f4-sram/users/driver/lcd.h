//
// Created by lsy on 17-5-17.
//

#ifndef TEMPLATE_LCD_H
#define TEMPLATE_LCD_H


#include "stm32f4xx.h"
#include "lcd_dev.h"
#include "font.h"

class Lcd {
public:
    LCD_DEV *lcd;
    // 480 800
    uint16_t w, h;


    uint16_t color = 0xffff;
    uint16_t background_color = 0;

    char *font_family = (char *) font_default_24x12;
    uint8_t font_y_size = 24;
    uint8_t font_x_size = 12;

    Lcd(LCD_DEV *_lcd) : lcd(_lcd), w(_lcd->w), h(_lcd->h) {}

    void cursor(uint16_t x, uint16_t y) { lcd->cursor(x, y); }

    void write(uint16_t c) { lcd->write(c); }

    void clear(void) { lcd->clear(background_color); }

    void dot(uint16_t x, uint16_t y, uint16_t c);

    uint16_t dot(uint16_t x, uint16_t y);

    void font(uint8_t w, uint8_t h, char *family);

    void line(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1);

    void rect(uint16_t x, uint16_t y, uint16_t w, uint16_t h);

    void show(uint16_t x, uint16_t y, char ch);

    void show(uint16_t x, uint16_t y, char *str);

    void show(uint16_t x, uint16_t y, uint32_t num);

    void show(uint16_t x, uint16_t y, float num);

    void show(uint16_t x, uint16_t y, uint16_t w, uint16_t h, char *img);
};


#endif //TEMPLATE_LCD_H
