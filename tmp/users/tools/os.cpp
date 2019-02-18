//
// Created by lsy on 17-7-12.
//

#include "os.h"

#include "timex.hpp"

using namespace dev;

static time *htim = NULL;
static timex *stim = NULL;
static gpio *led = NULL;

void os_init(uint8_t _dev, gpio *_led) {
    delay_init(72);
    stim = new timex();
    htim = new time(_dev);
    htim->setCallback(timex::update, stim);
    led = _led;
    setInterval(gpio::toggle, led, 100);
}

void setInterval(void(*cb)(void *), void *dat, uint32_t timeout) {
    stim->setInterval(cb, dat, timeout);
}

void setTimeout(void(*cb)(void *), void *dat, uint32_t timeout) {
    stim->setTimeout(cb, dat, timeout);
}

void setTimeout(void(*cb)(void *), void *dat, uint32_t timeout, uint32_t times) {
    stim->setTimeout(cb, dat, timeout, times);
}


uint32_t os_execult(void) {
    return stim->execute();
}


void os_stop(void){
    htim->stop();
}

void os_start(void){
    htim->start();
}
