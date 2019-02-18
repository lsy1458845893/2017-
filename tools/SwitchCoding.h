//
// Created by lsy on 17-7-11.
//

#ifndef STM32F4_SWITCHCODING_H
#define STM32F4_SWITCHCODING_H


#include <device.hpp>

class SwitchCoding {
private:
    dev::gpio left;
    dev::gpio right;
    bool state;

    void *udat;

    void (*up)(void *);

    void (*down)(void *);

public:
    SwitchCoding(dev::gpio left, dev::gpio right) : left(left), right(right) {}

    void setCallback(void (*_up)(void *), void (*_down)(void *), void *dat) {
        udat = dat;
        up = _up;
        down = _down;
    }

    static void update(void *dat) { ((SwitchCoding *) dat)->update(); }

    void update(void) {
        if (left.read()) {
            if (right.read()) state = false;
            else {
                if (state) {
                    if (up)up(udat);
                    state = false;
                }
            }
        } else {
            if (right.read()) {
                if (state) {
                    if (down)down(udat);
                    state = false;
                }
            } else state = true;
        }
    }

};


#endif //STM32F4_SWITCHCODING_H
