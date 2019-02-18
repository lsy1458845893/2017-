//
// Created by lsy on 17-7-15.
//


#include <lcd.h>
#include <lcd_dev.h>

#include "os.h"
#include <math.h>
#include "syscall.hpp"
#include "stdio.h"
#include "test_shower.h"
#include "Color.h"

using namespace dev;

class WaveShower {
private:
    LCD_DEV *lcd;
    uint16_t offset_x;
    uint16_t offset_y;

    uint16_t get_color(uint16_t x, uint16_t y) {
        const uint16_t a = 0, b = Color(100, 100, 100).convert(), c = Color(200, 200, 200).convert();
        if (x % 50 && y % 50) return a;
        if (y % 100 && x % 100)return b;
        return c;
    }

    void dot(uint16_t x, uint16_t y, uint32_t c) {
        if (x < 600 && y <= 400) lcd->dot(offset_x + x, offset_y + 400 - y, Color(c).convert());
    }

    void dot(uint16_t x, uint16_t y, uint16_t c) {
        if (x < 600 && y <= 400) lcd->dot(offset_x + x, offset_y + 400 - y, c);
    }

    void write(uint32_t c) {
        LCD->LCD_RAM = Color(c).convert();
    }

    void write(uint16_t c) {
        LCD->LCD_RAM = c;
    }

public:
    WaveShower(LCD_DEV *lcd, uint16_t offset_x, uint16_t offset_y)
            : lcd(lcd), offset_x(offset_x), offset_y(offset_y) {}

    void restore(void) {
        uint16_t x, y;
        for (x = 0; x <= 600; x++) {
            lcd->cursor(offset_x + x, offset_y);
            for (y = 0; y <= 400; y++)
                LCD->LCD_RAM = get_color(x, y);
        }
    }

    void restore(uint16_t x, uint16_t y1, uint16_t y2) {
        if (y1 >= 400) y1 = 400;
        if (y2 >= 400) y2 = 400;
        if (y1 > y2) {
            uint16_t tmp;
            tmp = y1;
            y1 = y2;
            y2 = tmp;
        }
        for (uint16_t t = y1; t < y2; t++)dot(x, t, get_color(x, t));
    }

    void draw(uint16_t x, uint16_t y1, uint16_t y2, uint32_t c) {
        if (y1 >= 400) y1 = 400;
        if (y2 >= 400) y2 = 400;
        if (y1 > y2) {
            uint16_t tmp;
            tmp = y1;
            y1 = y2;
            y2 = tmp;
        }
        for (uint16_t t = y1; t < y2; t++)dot(x, t, c);
    }

    void restore(uint16_t *dat) {
        uint16_t x = 600;
        while (x--)
            restore(x, dat[x], dat[x + 1]);
    }

    void draw(uint16_t *dat, uint32_t _c) {
        uint16_t x = 600, c = Color(_c).convert();
        while (x--)
            draw(x, dat[x], dat[x + 1], c);
    }
};


void test_shower(void) {

    os_init(2, 'F', 10);

    adc a = adc(1);
    a.open(1);
    a.start(1);

    LCD_DEV lcd_dev = LCD_DEV();
    WaveShower shower(&lcd_dev, 20, 60);
    shower.restore();

    usart io = usart(1, 9600);

    io.send("start execult\n");

    uint16_t dat[600];
    uint16_t tmp[600];
    uint16_t cursor = 0;
    while (true) {
        while (!os_execult());

        if (cursor >= 600) {
            shower.restore(tmp);
            for (uint16_t t = 0; t < 600; t++) tmp[t] = dat[t];
            shower.draw(dat, Color(250, 250, 0).get());
            cursor %= 600;
        }

        if (a.aleady()) {
            char buf[30];
            sprintf(buf, "%d\n", dat[cursor]);
            io.send(buf);
            dat[cursor++] = (uint16_t) (0.097 * a.read());
            a.start(1);
        }
    }
}