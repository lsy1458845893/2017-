//
// Created by lsy on 17-7-5.
//

#ifndef STM32F1_IICX_H
#define STM32F1_IICX_H


class iicx {
private:
public:
    dev::gpio scl;
    dev::gpio dat;

    iicx(dev::gpio scl, dev::gpio dat) :
            scl(scl), dat(dat) {}

    void start(void) {
        scl.output(1);
        dat.output(1);
        dat.output(0);
        scl.output(0);
    }

    void stop(void) {
        scl.output(1);
        dat.output(0);
        dat.output(1);
    }

    void wait_ack(void) {
        scl.output(1);
        scl.output(0);
    }

    void send(uint8_t data) {
        volatile uint8_t t = 8;
        scl.output(0);
        while (t--) {
            if (data & (0x01 << t)) dat.output(1);
            else dat.output(0);
            scl.output(1);
            scl.output(0);
        }
    }
};

#endif //STM32F1_IICX_H
