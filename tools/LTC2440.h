//
// Created by lsy on 17-7-9.
//

#ifndef LTC2440_H
#define LTC2440_H

#include "device.hpp"

class LTC2440 {
private:
    dev::gpio busy;
    dev::gpio sck;
    dev::gpio sdo;
    dev::gpio cs;

    uint32_t recv(void) {
        uint8_t t = 32;
        uint32_t recv = 0;
        cs.output(0);
//        delay_us(1);
        while (t--) {
            sck.output(1);
            if (sdo.read()) recv |= 1 << t;
//            delay_us(1);
            sck.output(0);
//            delay_us(1);
        }
        cs.output(1);
        return recv;
    }

public:
    LTC2440(dev::gpio busy, dev::gpio sck, dev::gpio sdo, dev::gpio cs) :
            busy(busy), sck(sck), sdo(sdo), cs(cs) {
        sdo.init_input();
        busy.init_input();
        cs.output(1);
    }

    bool aready(void) { return !busy.read(); }

    int32_t read(void) {
        int32_t dat = (recv() & 0x1fffffe0) >> 5;
//        dat = (dat & (1 << 23)) ? (~(dat & 0x7fffff)) + 1 : (dat & 0x7fffff);
        if (dat & (1 << 23)) dat = -(0xffffff & ((~dat) + 1));
        return dat;
    }
};


#endif //LTC2440_H
