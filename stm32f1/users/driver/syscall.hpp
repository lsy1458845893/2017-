//
// Created by lsy on 17-6-13.
//

#ifndef TEMPLATE_SYSCALL_H
#define TEMPLATE_SYSCALL_H

#include "stdint-gcc.h"
#include <stdlib.h>
#include "device.hpp"

void *operator new(size_t size);

void operator delete(void *space);

void set_print_dev(dev::usart *io);
#endif //TEMPLATE_SYSCALL_H
