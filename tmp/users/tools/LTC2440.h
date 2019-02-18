//
// Created by lsy on 17-7-9.
//

#ifndef LTC2440_H
#define LTC2440_H


class LTC2440 {
private:
    dev::gpio busy;
    dev::gpio sck;
    dev::gpio sdo;

    uint32_t recv(void) {
        uint8_t t = 32;
        uint32_t recv = 0;
        while (t--) {
            sck.output(1);
            if (sdo.read()) recv |= 1 << t;
            sck.output(0);
        }
    }

public:
    LTC2440(dev::gpio busy, dev::gpio sck, dev::gpio sdo) :
            busy(busy), sck(sck), sdo(sdo) {
        sdo.init_input();
        busy.init_input();
    }

    bool ready(void) { return !busy.read(); }

    uint32_t read(void) { return (recv() & 0x1fffffe0) >> 5; }
};


#endif //LTC2440_H
