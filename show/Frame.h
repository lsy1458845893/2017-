//
// Created by lsy on 17-7-12.
//

#ifndef STM32F4_FRAME_H
#define STM32F4_FRAME_H

#include "stdint.h"
#include "stdlib.h"
//class Frame {
//public:
//
//
//    virtual uint16_t *pipeline(void) {}
//
//    virtual void cursor(uint16_t x, uint16_t y) {}
//
//    virtual void write(uint32_t c) {}
//
//    virtual void dot(uint16_t x, uint16_t y, uint32_t c) {}
//
//    virtual void restore(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2) {}
//
//    virtual void restore(uint16_t x, uint16_t y) {}
//};


#include "Array.h"
#include "Color.h"

class Frame {
private:
public:
    Frame *parent = NULL;

    Array<Frame *> chlid;

    uint16_t offset_x, offset_y;
    uint16_t width, height;

    void append_chlid(Frame *c) {
        chlid.push(c);
        c->parent = this;
    }

    void restore_chlidren(void) {
        for (uint16_t t = 0; t < chlid.length; t++)
            chlid.arr[t]->restore();
    }

    virtual void restore(void) {
        for (uint16_t x = 0; x < width; x++) {
            cursor(x, 0);
            for (uint16_t y = 0; y < height; y++)
                write(dot(x, y));
        }
        restore_chlidren();
    }

    virtual void dot(uint16_t x, uint16_t y, Color c) { if (parent)parent->dot(offset_x + x, offset_y + y, c); }

    virtual void cursor(uint16_t x, uint16_t y) { if (parent)parent->cursor(offset_x + x, offset_y + y); }

    virtual void write(Color c) { if (parent)parent->write(c); }

    virtual Color dot(uint16_t x, uint16_t y) { return Color(255, 255, 255); }
};

#endif //STM32F4_FRAME_H
