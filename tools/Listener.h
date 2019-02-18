//
// Created by lsy on 17-7-10.
//

#ifndef STM32F1_LISTENER_H
#define STM32F1_LISTENER_H

#include "stdlib.h"
#include "stdint.h"

class Listener {
private:
    struct Node {
        void *data;

        void (*func)(void *);
    } *head = NULL;

    uint16_t size = 0;
public:
    Listener() : size(0), head(NULL) {};


    void add(void(*cb)(void *), void *dat) { head = realloc(head, ++size * sizeof(struct Node)); }

    static void raise(void *obj) { ((Listener *) obj)->raise(); }

    void raise(void) {
        uint16_t t;
        for (t = 0; t < size; t++)
            if (head[t]->func)
                head[t]->func(head[t].data);
    }
};


#endif //STM32F1_LISTENER_H
