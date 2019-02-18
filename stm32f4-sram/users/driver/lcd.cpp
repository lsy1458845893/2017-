//
// Created by lsy on 17-5-17.
//

#include "lcd.h"

uint16_t Lcd::dot(uint16_t x, uint16_t y) { return lcd->read_dot(x, y); }

void Lcd::dot(uint16_t x, uint16_t y, uint16_t c) { lcd->dot(x, y, c); }

#define FLOAT_FORMAT(n) ((int)((float)(n) + 0.5) == (int)(n) ? (int)(n) : (int)(n) + 1)

void Lcd::line(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1) {
    uint16_t t;
    for (t = 0; t < x1 - x0; t++)
        lcd->dot(t + x0, (uint16_t) FLOAT_FORMAT(y0 + t * ((float) (y0 - y1)) / ((float) (x0 - x1))), color);
    for (t = 0; t < y1 - y0; t++)
        lcd->dot((uint16_t) FLOAT_FORMAT(x0 + t * ((float) (x0 - x1)) / ((float) (y0 - y1))), t + y0, color);
}

void Lcd::show(uint16_t x, uint16_t y, char ch) {
    for (uint16_t tx = 0; tx < font_x_size; tx++) {
        cursor(tx + x, y);
        for (uint8_t ty = 0; ty < font_y_size; ty++) {
            if ((font_family[(font_x_size * font_y_size / 8) * (ch - ' ') + (font_y_size / 8) * tx + ty / 8]
                    << (ty % 8)) & 0x80)
                write(color);
            else write(background_color);
        }
    }
}

void Lcd::show(uint16_t x, uint16_t y, char *str) {
    while (*str) {
        show(x, y, *str);
        x += font_x_size;
        str++;
    }
}

#include "stdio.h"

void Lcd::show(uint16_t x, uint16_t y, uint32_t num) {
    char buf[20];
    sprintf(buf, "%d", num);
    show(x, y, buf);
}

void Lcd::show(uint16_t x, uint16_t y, float num) {
    char buf[50];
    sprintf(buf, "%f      ", num);
    show(x, y, buf);
}

void Lcd::show(uint16_t x, uint16_t y, uint16_t w, uint16_t h, char *img) {
    for (uint16_t tx = 0; tx < w; tx++) {
        cursor(tx + x, y);
        for (uint16_t ty = 0; ty < h; ty++)
            if (img[tx * h / 8 + ty / 8] << (ty % 8) & 0x80) write(color);
            else write(background_color);
    }
}

void Lcd::rect(uint16_t x, uint16_t y, uint16_t w, uint16_t h) {
    for (uint16_t tx = 0; tx < w; tx++) {
        cursor(tx + x, y);
        for (uint16_t ty = 0; ty < h; ty++)
            write(color);
    }
}

void Lcd::font(uint8_t w, uint8_t h, char *family) {
    font_y_size = h;
    font_x_size = w;
    font_family = family;
}





