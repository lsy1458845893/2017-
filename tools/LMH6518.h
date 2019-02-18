//
// Created by lsy on 17-6-7.
//

#ifndef LMH6518_H
#define LMH6518_H


class LMH6518 {
private:
    dev::gpio clk;
    dev::gpio dat;
    dev::gpio cs;

    void send(uint16_t data) {
        int cursor = 16;
        cs.output(0);
        while (cursor--) {
            clk.output(0);
            if (data & (1 << cursor))dat.output(1);
            else dat.output(0);
            clk.output(1);
        }
        cs.output(1);
    }

public:
    enum {
        FILTER_FULL = 0,
        FILTER_20MHz,
        FILTER_100MHz,
        FILTER_200MHz,
        FILTER_350MHz,
        FILTER_650MHz,
        FILTER_750MHz
    };

    enum {
        BANDWIDTH_0 = 0,
        BANDWIDTH_2,
        BANDWIDTH_4,
        BANDWIDTH_6,
        BANDWIDTH_8,
        BANDWIDTH_10,
        BANDWIDTH_12,
        BANDWIDTH_14,
        BANDWIDTH_16,
        BANDWIDTH_18,
        BANDWIDTH_20,
    };

    LMH6518(dev::gpio clk, dev::gpio dat, dev::gpio cs)
            : clk(clk), dat(dat), cs(cs) {
        clk.output(1);
        cs.output(1);
        dat.output(1);
    }

    void set(bool fullpower, bool preamp, uint8_t filter, uint8_t bandwidth) {
        uint16_t data = 0;
        data = fullpower ? data : data | (1 << 10);
        data = preamp ? data | (1 << 4) : data;
        data |= filter << 6;
        data |= bandwidth;
        send(data);
    }
};


#endif //TEMPLATE_LMH6518_H
