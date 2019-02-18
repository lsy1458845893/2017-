//
// Created by lsy on 17-6-13.
//

#include "syscall.hpp"
#include "stdlib.h"

extern "C" int __io_putchar(int ch) __attribute__((weak));

extern "C" int __io_getchar(void) __attribute__((weak));

extern "C" int __io_puts(const char *str) __attribute__((weak));


#include <cerrno>
#include <cstdlib>
#include "stdio.h"

void *operator new(size_t size) {
    return malloc(size);
}

void operator delete(void *space) {
    free(space);
}


#define MIN_STACK_SIZE 1024 * 10

extern "C" caddr_t _sbrk(int incr) {
    extern char end asm("end");
    register char *stack_ptr asm("sp");
    static char *heap_end;
    char *prev_heap_end;

    if (heap_end == 0)
        heap_end = &end;

    prev_heap_end = heap_end;
    if (heap_end + incr + MIN_STACK_SIZE > stack_ptr) {
//		write(1, "Heap and stack collision\n", 25);
//		abort();
        errno = ENOMEM;
        return (caddr_t) -1;
    }

    heap_end += incr;
    return (caddr_t) prev_heap_end;
}

