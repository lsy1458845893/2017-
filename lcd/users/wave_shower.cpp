//
// Created by lsy on 17-5-18.
//

#include "wave_shower.h"
#include "color.h"

#define IN_RANGE(x, y) ((x)<w&&(y)<h)
#define Y_RANGE(y) (0 <= (y) && (y) <= 400)
#define X_RANGE(x) (0 <= (x) && (x) <= 600)

uint16_t Wave_shower::grid_color(uint16_t x, uint16_t y) {
    if (x == 0 || y == 0 || x == w || y == h) return color.WHITE;
    if ((x + y) % 2) return color.BLACK;
    if (x % 50 && y % 50) return color.BLACK;
    if (x % 100 && y % 100) return color.GRAY;
    else return color.LGRAY;
}

void Wave_shower::clear(uint16_t x, uint16_t y) {
    if (X_RANGE(x) && Y_RANGE(y)) lcd->lcd->dot(lcd_x(x), lcd_y(y), grid_color(x, y));
}

void Wave_shower::prepare(void) {
    uint16_t x = 0, y = 0;
    for (x = 0; x <= w; x++) {
        lcd->lcd->cursor(x + xoffset, yoffset);
        for (y = 0; y <= h; y++)
            lcd->lcd->write(grid_color(x, y));
    }
}

void Wave_shower::draw(uint16_t x, uint16_t y, uint16_t c) {
    if (X_RANGE(x) && Y_RANGE(y))lcd->lcd->dot(lcd_x(x), lcd_y(y), c);
}

void Wave_shower::clear(uint16_t *wave) {
    uint16_t t = w;
    while (t--) clear(t, wave[t]);
}

void Wave_shower::draw(uint16_t *wave, uint16_t c) {
    uint16_t t = w;
    while (t--) draw(t, wave[t], c);
}





