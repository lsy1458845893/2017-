//
// Created by lsy on 17-6-13.
//

#ifndef TEMPLATE_SYSCALL_H
#define TEMPLATE_SYSCALL_H

#include "stdint-gcc.h"
#include <stdlib.h>

void *operator new(size_t size);

void operator delete(void *space);

#endif //TEMPLATE_SYSCALL_H
