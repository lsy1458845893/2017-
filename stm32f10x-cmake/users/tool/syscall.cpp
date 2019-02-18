//
// Created by lsy on 17-6-13.
//

#include "syscall.h"
#include "stdlib.h"

USART *sysio;

extern "C" int __io_putchar(int ch) {
    if (sysio) sysio->send((char) ch);
    return 0;
}

static char ch_n = 0;
static char ch_c;

static void wait_input(void *d,char ch) {
    ch_n++;
    ch_c = ch;
}

extern "C" int __io_getchar(void) {
    if (sysio) {
        sysio->recv(NULL, wait_input);
        while (!ch_n);
        ch_n = 0;
        return ch_c;
    } else return '\0';
}

extern "C" int __io_puts(const char *str) {
    if (sysio) sysio->send((char *) str);
    return 0;
}


void *operator new(size_t size) {
    return malloc(size);
}

void operator delete(void *space) {
    free(space);
}