//
// Created by lsy on 17-7-16.
//

#ifndef STM32F4_COORDINATES_H
#define STM32F4_COORDINATES_H

class Coordinates {
private:
    LCD_DEV *lcd_dev;
    uint16_t offset_x, offset_y;
public:
    Coordinates(LCD_DEV *lcd_dev, uint16_t x, uint16_t y)
            : lcd_dev(lcd_dev), offset_x(x), offset_y(y) {
        for (uint16_t tx = 0; tx <= 600; tx++) {
            lcd_dev->cursor(offset_x + tx, offset_y);
            for (uint16_t ty = 0; ty <= 400; ty++)
                lcd_dev->write(dot(tx, 400 - ty));
        }
    }

    uint16_t dot(uint16_t x, uint16_t y) {
        if (x % 50 && y % 50) return Color(0, 0, 0).convert();
        if (x % 100 && y % 100) return Color(100, 100, 100).convert();
        else return Color(200, 200, 200).convert();
    }

    void dot(uint16_t x, uint16_t y, uint16_t c) {
        x = x > 600 ? 600 : x;
        y = y > 400 ? 400 : y;
        lcd_dev->dot(offset_x + x, offset_y + 400 - y, c);
    }

    void restore(uint16_t x, uint16_t y) {
        x = x > 600 ? 600 : x;
        y = y > 400 ? 400 : y;
        dot(x, y, dot(x, y));
    }
};

#endif //STM32F4_COORDINATES_H
