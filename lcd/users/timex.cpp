//
// Created by lsy on 17-6-9.
//
//
//#define TIM_NUM 100
//
//typedef void (*callback_t)(void *d);
//
//class Timex {
//private:
//    uint32_t base;
//    uint32_t stamp[TIM_NUM];
//    uint32_t reload[TIM_NUM];
//    uint8_t reload_cmd[TIM_NUM];
//
//    void *data[TIM_NUM];
//    callback_t func[TIM_NUM];
//    uint8_t exec[TIM_NUM];
//
//public:
//    Timex();
//
//    int16_t setTimeout(callback_t fun, void *d, uint32_t timeout);
//
//    int16_t setInterval(callback_t fun, void *d, uint32_t timeout);
//
//    void update(void);
//
//    void execult(void);
//
//    static void update(void *tim) { ((Timex *) tim)->update(); }
//};
//
//Timex::Timex() {
//    uint8_t c = TIM_NUM;
//    while (c--) func[c] = NULL;
//    base = 0;
//}
//
//int16_t Timex::setTimeout(callback_t fun, void *d, uint32_t timeout) {
//    uint8_t c = TIM_NUM;
//    if (fun == NULL) return -2;
//    while (c--) {
//        if (func[c] == NULL) {
//            func[c] = fun;
//            data[c] = d;
//            reload[c] = timeout;
//            reload_cmd[c] = 0;
//            stamp[c] = base + timeout;
//            return c;
//        }
//    }
//    return -1;
//}
//
//int16_t Timex::setInterval(callback_t fun, void *d, uint32_t timeout) {
//    int16_t c;
//    c = setTimeout(fun, d, timeout);
//    if (c > 0)
//        reload_cmd[c] = 1;
//    return c;
//}
//
//void Timex::update(void) {
//    uint8_t c = TIM_NUM;
//    base++;
//    while (c--) {
//        if (stamp[c] == base) {
//            if (func[c]) {
//                exec[c]++;
//                if (reload_cmd[c]) stamp[c] = base + reload[c];
//            }
//        }
//    }
//}
//
//void Timex::execult(void) {
//    uint8_t c = TIM_NUM;
//    while (c--) {
//        if (exec[c]) {
//            exec[c]--;
//            if (func[c]) {
//                func[c](data[c]);
//                 if (!reload_cmd[c]) func[c] = NULL;
//            }
//        }
//    }
//}

#include "timex.h"

