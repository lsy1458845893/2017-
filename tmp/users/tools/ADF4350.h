//
// Created by lsy on 17-6-28.
//

#ifndef STM32F4_ADF4350_H
#define STM32F4_ADF4350_H

#include <device.hpp>

class ADF4350 {
private:
    dev::gpio sck;
    dev::gpio dat;
    dev::gpio le;

    void send(uint32_t data);
public:
    ADF4350(dev::gpio sck, dev::gpio dat, dev::gpio le);

    void rate(float f);
};


#endif //STM32F4_ADF4350_H
