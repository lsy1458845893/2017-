//
// Created by lsy on 17-7-15.
//

#ifndef STM32F4_ARRAY_H
#define STM32F4_ARRAY_H

#include "device.hpp"

template<typename T>
class Array {
public:
    T *arr = NULL;
    uint16_t length = 0;

    void push(T e) {
        arr = (T *) realloc(arr, (++length) * sizeof(T));
        arr[length - 1] = e;
    }

    ~Array() { if (arr) free(arr); }
};


#endif //STM32F4_ARRAY_H
