//
// Created by lsy on 17-8-4.
//

#ifndef STM32F1_KEY_BORAD_H
#define STM32F1_KEY_BORAD_H

class KeyBorad {
    using namespace dev;
private:
    struct {
        bool st;
        bool key;
        int8_t inc;
        gpio a;
        gpio b;
        gpio c;
    } sc[3];
    gpio row[4];
    gpio col[4];
    uint8_t kst = 0;

    uint8_t next(uint8_t n) { return (uint8_t) ((n + 1) % 4); }

    usart *io;

    void send(uint8_t dat) {
        io->send(dat);
    }

public:
    KeyBorad(usart *io) :
            sc({{false, false, 0, gpio('A', 1), gpio('A', 2), gpio('A', 0)},
                {false, false, 0, gpio('A', 4), gpio('A', 5), gpio('A', 3)},
                {false, false, 0, gpio('A', 7), gpio('A', 8), gpio('A', 6)}}),
            row({gpio('B', 8), gpio('B', 9), gpio('B', 10), gpio('B', 11)}),
            col({gpio('B', 12), gpio('B', 13), gpio('B', 14), gpio('B', 15)}),
            io(io) {
        GPIO_InitTypeDef cfg;
        cfg.GPIO_Mode = GPIO_Mode_IPD;
        col[0].init(&cfg);
        col[1].init(&cfg);
        col[2].init(&cfg);
        col[3].init(&cfg);

        sc[0].a.init_input();
        sc[0].b.init_input();
        sc[0].c.init_input();

        sc[1].a.init_input();
        sc[1].b.init_input();
        sc[1].c.init_input();

        sc[2].a.init_input();
        sc[2].b.init_input();
        sc[2].c.init_input();
    }

    bool key[4][4] = {
            {false, false, false, false},
            {false, false, false, false},
            {false, false, false, false},
            {false, false, false, false},
    };

    static void update(void *d) { ((KeyBorad *) d)->update(); }

    void update(void) {
        enum {
            KEY_0, KEY_1, KEY_2, KEY_3, KEY_4,
            KEY_5, KEY_6, KEY_7, KEY_8, KEY_9,
            KEY_DOT, KEY_NEWLINE,
            KEY_A, KEY_B, KEY_C, KEY_D,
            KEY_S1, KEY_S1U, KEY_S1D,
            KEY_S2, KEY_S2U, KEY_S2D,
            KEY_S3, KEY_S3U, KEY_S3D,
        };

        const uint8_t layer[4][4] = {
                {KEY_7,   KEY_8, KEY_9,       KEY_A,},
                {KEY_4,   KEY_5, KEY_6,       KEY_B,},
                {KEY_1,   KEY_2, KEY_3,       KEY_C,},
                {KEY_DOT, KEY_0, KEY_NEWLINE, KEY_D,}
        };


        for (uint8_t t = 0; t < 4; t++) {
            if (col[t].read()) {
                if (!key[kst][t]) {
                    key[kst][t] = true;
                    send(layer[kst][t]);
                }
            } else key[kst][t] = false;
        }

        row[kst].output(0);
        kst = next(kst);
        row[kst].output(1);

        const uint8_t sctable[3][3] = {
                {KEY_S1, KEY_S1U, KEY_S1D},
                {KEY_S2, KEY_S2U, KEY_S2D},
                {KEY_S3, KEY_S3U, KEY_S3D}
        };

        for (uint8_t t = 0; t < 3; t++) {
            if (!sc[t].c.read()) {
                if (!sc[t].key) {
                    sc[t].key = true;
                    send(sctable[t][0]);
                }
            } else sc[t].key = false;

            if (sc[t].a.read()) {
                if (!sc[t].b.read()) {
                    if (!sc[t].st) {
                        sc[t].st = true;
                        send(sctable[t][1]);
                    }
                } else sc[t].st = false;
            } else {
                if (sc[t].b.read()) {
                    if (!sc[t].st) {
                        sc[t].st = true;
                        send(sctable[t][2]);
                    }
                }
            }
        }
    }

    static int main(void) {
        os_init(3, 'C', 13);
        usart io = usart(1, 9600);

        time keytim = time(2);
        KeyBorad key = KeyBorad(&io);
        keytim.setCallback(KeyBorad::update, &key);
        keytim.period(100);

        while (true) {
            while (!os_execult());
        }
    }
};

#endif //STM32F1_KEY_BORAD_H
