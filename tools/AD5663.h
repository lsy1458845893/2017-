//
// Created by lsy on 17-6-28.
//

#ifndef STM32F4_AD5663_H
#define STM32F4_AD5663_H

#include "device.hpp"

class AD5663 {
private:
    dev::gpio clk;
    dev::gpio dat;
    dev::gpio ldac;
    dev::gpio sync;
public:
    AD5663(dev::gpio clk, dev::gpio dat, dev::gpio ldac, dev::gpio sync) :
            clk(clk), dat(dat), ldac(ldac), sync(sync) {}

    void output(uint8_t ch, uint16_t val) {
        uint8_t i = 0;
        uint32_t set_data;
        clk.output(1);
        sync.output(1);
        sync.output(0);
        clk.output(0);
        set_data = (uint32_t) (((0 << 19) & 0x00380000) + ((ch << 17) & 0x00070000) + (val & 0x0000FFFF));
        set_data <<= 8;
        for (i = 0; i < 24; i++) {
            clk.output(1);
            if (set_data & 0x80000000) dat.output(1);
            else dat.output(0);
            clk.output(0);
            set_data <<= 1;
        }
        ldac.output(0);
        ldac.output(1);
    }

};

#endif //STM32F4_AD5663_H
