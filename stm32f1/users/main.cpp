
#include <stm32f10x_conf.h>
#include <base64.h>
#include "device.hpp"

using namespace dev;

#include "os.h"
#include "syscall.hpp"


#include "stdio.h"


class RemoteCmd {
private:
    char buf[10000];
    uint32_t cur = 0;

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
            char conv[10000];
            base64_decode(buf, cur, (unsigned char *) conv);
            local_execult(
                    (Head *) conv, (uint8_t *) (conv + 4 * sizeof(uint32_t)),
                    (uint16_t) (BASE64_DECODE_OUT_SIZE(cur) - 4 * sizeof(uint32_t)));
        }
    }

    void remote_execult(Head *head, uint8_t *body, uint16_t len) {
        uint8_t raw[1000];
        uint8_t pack[10000];
        uint8_t *headp = (uint8_t *) head;
        uint16_t raw_len = len + 4 * sizeof(uint32_t);
        uint16_t t = 0;
        for (t = 0; t < raw_len; t++) {
            if (t < 4 * sizeof(uint32_t))
                raw[t] = headp[t];
            else
                raw[t] = body[t - 4 * sizeof(uint32_t)];
        }
        base64_encode(raw, raw_len, (char *) pack);
        for (t = 0; t < BASE64_ENCODE_OUT_SIZE(raw_len); t++) recv_char(pack[t]);
        recv_char(0);
    }

    void local_execult(Head *head, uint8_t *body, uint16_t len) {
        printf("head:%x %x %x %x;body(%d):%s\n", head->a, head->b, head->c, head->d,
               len, body);
    }
};

int main(void) {
    os_init(3, 'C', 13);
    usart io = usart(1, 9600);


    while (true) {
        while (!os_execult());
    }
}