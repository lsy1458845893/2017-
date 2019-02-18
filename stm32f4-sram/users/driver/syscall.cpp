//
// Created by lsy on 17-6-13.
//

#include "syscall.hpp"
#include "stdlib.h"
#include <cerrno>
#include <cstdlib>
#include "stdio.h"

extern "C" int __io_putchar(int ch) __attribute__((weak));

extern "C" int __io_getchar(void) __attribute__((weak));

extern "C" int __io_puts(const char *str) __attribute__((weak));

static dev::usart *sysio;

extern "C" int __io_putchar(int ch) {
    if (sysio)sysio->send(ch);
    return 0;
}

extern "C" int __io_puts(const char *str) {
    if (sysio)sysio->send((char *) str);
    return 0;
}

extern "C" int _write(int file, char *ptr, int len) {
    int DataIdx;

    for (DataIdx = 0; DataIdx < len; DataIdx++) {
        __io_putchar(*ptr++);
    }
    return len;
}

void set_print_dev(dev::usart *io) {
    sysio = io;
}

void *operator new(size_t size) {
    return malloc(size);
}

void operator delete(void *space) {
    free(space);
}


#define MIN_STACK_SIZE 1024 * 15

/**
 * ------------- & end
 *
 *
 *
 *
 *
 * ------------- pre_heap_end
 *
 *
 * ------------- heap_end
 *
 *
 */


#define BASE ((vu8 *)0x68000000)
#define SIZE 1024 * 1024

extern "C" caddr_t _sbrk(int incr) {
    static char *heap_end = NULL;
    char *prev_heap_end;

    if (heap_end == NULL)
        heap_end = (char *) BASE;

    static uint16_t last = 0;

    if (last + incr > SIZE) {
        errno = ENOMEM;
        return (caddr_t) -1;
    }

    prev_heap_end = heap_end;

    heap_end += incr;
    return (caddr_t) prev_heap_end;
}

