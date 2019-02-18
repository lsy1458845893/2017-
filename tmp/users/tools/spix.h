//
// Created by lsy on 17-7-9.
//

#ifndef STM32F1_SPIX_H
#define STM32F1_SPIX_H

#include "device.hpp"

class spix {
private:
    dev::gpio sck;
    dev::gpio mosi;
    dev::gpio miso;

    bool recv = true;
public:
    spix(dev::gpio sck, dev::gpio mosi, dev::gpio miso) :
            sck(sck), mosi(mosi), miso(miso) { miso.init_input(); }

    uint8_t exchange(uint8_t dat) {
        uint8_t i = 8;
        uint8_t recv = 0;
        while (i--) {
            sck.output(1);
            if (dat & (1 << i)) mosi.output(1);
            else mosi.output(0);
            sck.output(0);
            if (miso.read()) recv |= 1 << i;
        }
        return recv;
    }
};


#endif //STM32F1_SPIX_H
