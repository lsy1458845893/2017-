//
// Created by lsy on 17-7-5.
//

#ifndef OLED_H
#define OLED_H

#include "device.hpp"

#include "iicx.h"

class oled {
private:
    iicx i2c;

    void data(uint8_t dat) {
        i2c.start();
        i2c.send(0x78);
        i2c.wait_ack();
        i2c.send(0x40);
        i2c.wait_ack();
        i2c.send(dat);
        i2c.wait_ack();
        i2c.stop();
    }

    void command(uint8_t cmd) {
        i2c.start();
        i2c.send(0x78);
        i2c.wait_ack();
        i2c.send(0x00);
        i2c.wait_ack();
        i2c.send(cmd);
        i2c.wait_ack();
        i2c.stop();
    }


public:
    oled(iicx i2c);

    // 0 <= x < 128 && 0 <= y < 8
    void cursor(uint8_t x, uint8_t y) {
        command((uint8_t) (0xb0 + y));
        command((uint8_t) (((x & 0xf0) >> 4) | 0x10));
        command((uint8_t) (x & 0x0f));
    }

    void write(uint8_t dat) { data(dat); };

    void print(uint8_t line, uint8_t x, char ch);

    void print(uint8_t line, uint8_t x, char *str);

    void clear(void) {
        for (uint8_t y = 0; y < 8; y++) {
            cursor(0, y);
            for (uint8_t x = 0; x < 128; x++)
                write(0x00);
        }
    }
};


#endif //STM32F4_OLED_H
