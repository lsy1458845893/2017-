
#include <AD5663.h>
#include <cmath>
#include "os.h"
#include "device.hpp"
#include "syscall.hpp"

using namespace dev;

#include "base64.h"

#include "stdio.h"


#define EXEC_POOL_SIZE 30

struct {
    bool flag = false;
    void *dat;

    void (*func)(void *);
} exec_pool[EXEC_POOL_SIZE] = {};

void func_init(void) {
    uint8_t t = EXEC_POOL_SIZE;
    while (t--)exec_pool[t].flag = false;
}

void func_mark(void (*func)(void *), void *dat) {
    for (uint16_t t = 0; t < EXEC_POOL_SIZE; t++) {
        if (!exec_pool[t].flag) {
            exec_pool[t].flag = true;
            exec_pool[t].dat = dat;
            exec_pool[t].func = func;
            return;
        }
    }
}

void func_check(void) {
    for (uint16_t t = 0; t < EXEC_POOL_SIZE; t++)
        if (exec_pool[t].flag) {
            exec_pool[t].flag = false;
            exec_pool[t].func(exec_pool[t].dat);
        }
}


uint16_t p_num;
uint16_t value[1000];

class RemoteCmd {
private:
    char buf[10000];
    uint32_t cur = 0;
    uint32_t len = 0;
public:
    typedef struct Head {
        uint32_t a;
        uint32_t b;
        uint32_t c;
        uint32_t d;
    } Head;

    static void recv_char(void *t, char ch) { ((RemoteCmd *) t)->recv_char(ch); }

    void recv_char(char ch) {
        buf[cur++] = ch;
        if (ch == 0) {
            len = cur;
            cur = 0;
            func_mark(convert_data, this);
        }
    }

//    void remote_execult(Head *head, uint8_t *body, uint16_t len) {
//        uint8_t raw[1000];
//        uint8_t pack[10000];
//        uint8_t *headp = (uint8_t *) head;
//        uint16_t raw_len = len + 4 * sizeof(uint32_t);
//        uint16_t t = 0;
//        for (t = 0; t < raw_len; t++) {
//            if (t < 4 * sizeof(uint32_t))
//                raw[t] = headp[t];
//            else
//                raw[t] = body[t - 4 * sizeof(uint32_t)];
//        }
//        base64_encode(raw, raw_len, (char *) pack);
//        for (t = 0; t < BASE64_ENCODE_OUT_SIZE(raw_len); t++) recv_char(pack[t]);
//        recv_char(0);
//    }

    static void convert_data(void *t) { ((RemoteCmd *) t)->convert_data(); }

    void convert_data(void) {
        char conv[10000];
        base64_decode(buf, len, (unsigned char *) conv);
        local_execult(
                (Head *) conv, (uint8_t *) (conv + 4 * sizeof(uint32_t)),
                (uint16_t) (BASE64_DECODE_OUT_SIZE(len) - 4 * sizeof(uint32_t)));
    }

    void local_execult(Head *head, uint8_t *body, uint16_t len) {
        if (head->a == 0xff000001) {
            uint16_t *valrecv = (uint16_t *) body;
            p_num = (uint16_t) head->b;
            for (uint16_t t = 0; t < head->b; t++) {
                value[t] = valrecv[t];
            }
        }
    }
};


RemoteCmd cmd;


void net_recv(void *t, char ch) {
    cmd.recv_char(ch);
}

#define DOTP(x, y)   dac->output(0,(uint32_t)((x) * 65535));  \
                    dac->output(1,(uint32_t)((y) * 65535));

#define DOT(x, y)   dac.output(0,(uint32_t)((x) * 65535));  \
                    dac.output(1,(uint32_t)((y) * 65535));

float adc_to_db(int32_t val) { return (float) val / 76774.2f; }


//
//void callback(void *t){
//    AD5663 *dac = (AD5663 *) t;
//    static uint32_t div = 0;
//    if (div < p_num){
//        DOTP((float) div / (p_num), ((float) value[div] / 65536));
//    }else if(div < p_num + 100){
//        DOTP((float) div / 100, 0.5);
//    } else if(div < p_num + 200){
//        DOTP((float) div / 100, 0);
//    }else if(div < p_num + 300){
//        DOTP((float) div / 100, 1);
//    } else DOTP(0, 0.5);
//    div ++;
//    if(div > p_num + 300) div = 0;
//}

int main(void) {
    usart io = usart(1, 9600);
    os_init(2, 'F', 10);
    set_print_dev(&io);
    func_init();
    cmd = RemoteCmd();
    p_num = 0;
    usart net = usart(3, 9600);
    net.recv(net_recv, NULL);

    AD5663 dac = AD5663(gpio('B', 13), gpio('B', 14), gpio('G', 8), gpio('G', 7));
    gpio('G', 6).output(1);

//    time htim = time(3);
//    htim.period(25);
//    htim.setCallback(callback,&dac);


    while (true) {
        while (!os_execult());
        func_check();
        for (int16_t t = 0; t < (p_num); t++) {
            DOT((float) t / (p_num), ((float) value[t] / 65536));
        }

        for (int16_t t = 99; t >= 0; t--) {
            DOT((float) t / 100, 0.5);
        }

        for (int16_t t = 0; t < 100; t++) {
            DOT((float) t / 100, 0);
        }

        for (int16_t t = 99; t >= 0; t--) {
            DOT((float) t / 100, 1);
        }
        DOT(0, 0);
    }
}
