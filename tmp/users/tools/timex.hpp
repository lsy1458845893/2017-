//
// Created by lsy on 17-6-9.
//

/**
 * depends: stdlib.h stdint.h
 */

#ifndef TEMPLATE_TIMERX_H
#define TEMPLATE_TIMERX_H

#include "device.hpp"

#define tim_t int64_t

class timex {
private:
    class Rnode {
    public:
        Rnode *next;
        tim_t stamp;
        tim_t reload;
        void *dat;
        void(*fun)(void *);
    };

    class Tnode {
    public:
        Tnode *next;
        tim_t stamp;
        tim_t reload;
        uint16_t times;
        void *dat;
        void(*fun)(void *);
    };

    Rnode *rhead = NULL;
    Tnode *thead = NULL;

    tim_t base = 0;
    tim_t last = 0;

    template<class T>
    T *insert(T *head, T *node) {
        T thead = T();
        thead.next = head;
        T *temp = &thead;
        while (temp->next != NULL && (temp->next->stamp - base) <= (node->stamp - base))
            temp = temp->next;
        node->next = temp->next;
        temp->next = node;
        return thead.next;
    }

public:

    static void update(void *tim) { ((timex *) tim)->update(); }

    void requestAnimationFrame(void(*fun)(void *), void *dat) { setTimeout(fun, dat, 1); }

    void update(void) { base++; }

    void setTimeout(void(*fun)(void *), void *dat, tim_t timeout) {
        Tnode *t = new Tnode();
        t->fun = fun;
        t->dat = dat;
        t->stamp = timeout + base;
        t->times = 1;
        thead = insert<Tnode>(thead, t);
    }

    void setTimeout(void(*fun)(void *), void *dat, tim_t timeout, uint16_t times) {
        Tnode *t = new Tnode();
        t->fun = fun;
        t->dat = dat;
        t->stamp = timeout + base;
        t->reload = timeout;
        t->times = times;
        thead = insert<Tnode>(thead, t);
    }

    void setInterval(void(*fun)(void *), void *dat, tim_t time) {
        Rnode *t = new Rnode();
        t->fun = fun;
        t->dat = dat;
        t->stamp = time + base;
        t->reload = time;
        rhead = insert<Rnode>(rhead, t);
    }

    tim_t execute(void) {
        tim_t next = 0xFFFFFFF;
        Rnode *rtemp;
        Tnode *ttemp;
        void(*callback)(void *);
        void *data;
        do {
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
                    next = thead->stamp - base;
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
                    next = (rhead->stamp - base) < next ? (rhead->stamp - base) : next;
            }
            if (last != base) last++;
            else break;
        }while (true);
        return next;
    }
};

#endif //TEMPLATE_TIMERX_H
