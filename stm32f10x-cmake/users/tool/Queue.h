//
// Created by lsy on 17-6-20.
//

#ifndef TEMPLATE_QUEUE_H
#define TEMPLATE_QUEUE_H

#include "stdlib.h"

template <typename T>
class Queue {
    class Node {
    public:
        Node *next;
        T dat;
    };

    Node header = {.next = NULL};
    Node *head = &header;
    Node *tale = &header;

public:
    Queue() {}
    bool empty(void) { return head->next == NULL; }

    void push(T dat) {
        tale->next = new Node();
        tale->next->dat = dat;
        tale = tale->next;
    }

    T get(void) {
        T dat = head->next->dat;
        Node *t = head->next;
        head->next = head->next->next;
        delete t;
        return dat;
    }
};


#endif //TEMPLATE_QUEUE_H
