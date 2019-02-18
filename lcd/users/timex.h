//
// Created by lsy on 17-6-9.
//

#ifndef TEMPLATE_TIMERX_H
#define TEMPLATE_TIMERX_H


#include "stdint-gcc.h"
#include "stdlib.h"


typedef void (*callback_t)(void *d);

class Timex {
private:
    class Rnode {
    public:
        Rnode *next;
        uint64_t stamp;
        uint64_t reload;
        void *dat;
        callback_t fun;
    };

    class Tnode {
    public:
        Tnode *next;
        uint64_t stamp;
        uint64_t reload;
        uint16_t times;
        void *dat;
        callback_t fun;
    };

    Rnode *rhead = NULL;
    Tnode *thead = NULL;

    uint64_t base = 0;
    uint64_t last = 0;

    template<class T>
    T *insert(T *head, T *node) {
        T thead = T();
        thead.next = head;
        T *temp = &thead;
        while (temp->next != NULL && temp->next->stamp <= node->stamp)
            temp = temp->next;
        node->next = temp->next;
        temp->next = node;
        return thead.next;
    }

public:

    static void update(void *tim) { ((Timex *) tim)->update(); }

    void requestAnimationFrame(callback_t fun, void *dat) { setTimeout(fun, dat, 1); }

    void update(void) { base++; }

    void setTimeout(callback_t fun, void *dat, uint64_t timeout) {
        Tnode *t = new Tnode();
        t->fun = fun;
        t->dat = dat;
        t->stamp = timeout + base;
        t->times = 1;
        thead = insert<Tnode>(thead, t);
    }

    void setTimeout(callback_t fun, void *dat, uint64_t timeout, uint16_t times) {
        Tnode *t = new Tnode();
        t->fun = fun;
        t->dat = dat;
        t->stamp = timeout + base;
        t->reload = timeout;
        t->times = times;
        thead = insert<Tnode>(thead, t);
    }

    void setInterval(callback_t fun, void *dat, uint64_t time) {
        Rnode *t = new Rnode();
        t->fun = fun;
        t->dat = dat;
        t->stamp = time + base;
        t->reload = time;
        rhead = insert<Rnode>(rhead, t);
    }

    uint32_t execute(void) {
        uint32_t next = 0xFFFFFFF;
        Rnode *rtemp;
        Tnode *ttemp;
        callback_t callback;
        void *data;
        if (thead != NULL) {
            if (thead->stamp == last) {
                callback = thead->fun;
                data = thead->dat;
                ttemp = thead;
                thead = thead->next;
                ttemp->times--;
                if (ttemp->times != 0) {
                    ttemp->stamp += ttemp->reload;
                    thead = insert<Tnode>(thead, ttemp);
                } else
                    delete ttemp;
                if (callback)callback(data);
                return 0;
            } else
                next = thead->stamp - last;
        }
        if (rhead != NULL) {
            if (rhead->stamp == last) {
                callback = rhead->fun;
                data = rhead->dat;
                rtemp = rhead;
                rhead = rhead->next;
                rtemp->stamp += rtemp->reload;
                rhead = insert<Rnode>(rhead, rtemp);
                if (callback)callback(data);
                return 0;
            } else
                next = (rhead->stamp - last) < next ? (rhead->stamp - last) : next;
        }
        if (last != base) last++;
        return next;
    }
};

#endif //TEMPLATE_TIMERX_H
