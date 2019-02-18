//
// Created by lsy on 17-6-17.
//

#include "button.h"
#include "sys.h"
#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"


char table[4][4] = {
        {'1', '2', '3', 'A'},
        {'4', '5', '6', 'B'},
        {'7', '8', '9', '+'},
        {'.', '0', 'F', '-'},
};

void button_init(void) {
    GPIO_InitTypeDef gpio;
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
    gpio.GPIO_OType = GPIO_OType_PP;
    gpio.GPIO_Mode = GPIO_Mode_OUT;
    gpio.GPIO_Speed = GPIO_Speed_100MHz;
    gpio.GPIO_PuPd = GPIO_PuPd_NOPULL;

//    gpio.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_2;
//    GPIO_Init(GPIOC, &gpio);
//    gpio.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_4;
//    GPIO_Init(GPIOA, &gpio);
    gpio.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_3 | GPIO_Pin_5 | GPIO_Pin_7;
    GPIO_Init(GPIOC, &gpio);

    gpio.GPIO_Mode = GPIO_Mode_IN;
    gpio.GPIO_PuPd = GPIO_PuPd_DOWN;
    gpio.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_11 | GPIO_Pin_13 | GPIO_Pin_15;
    GPIO_Init(GPIOC, &gpio);
}


#define BTN_OUT_0 PCout(1)
#define BTN_OUT_1 PCout(3)
#define BTN_OUT_2 PCout(5)
#define BTN_OUT_3 PCout(7)

#define BTN_IN_0 PCin(9)
#define BTN_IN_1 PCin(11)
#define BTN_IN_2 PCin(13)
#define BTN_IN_3 PCin(15)

void button_prepare(char r) {
    BTN_OUT_0 = 0;
    BTN_OUT_1 = 0;
    BTN_OUT_2 = 0;
    BTN_OUT_3 = 0;

    if (r == 0) BTN_OUT_0 = 1;
    else if (r == 1) BTN_OUT_1 = 1;
    else if (r == 2) BTN_OUT_2 = 1;
    else if (r == 3) BTN_OUT_3 = 1;
}

char button_read(char r) {
    static char _table[4][4] = {};
    if (BTN_IN_0) {
        if (_table[r][0]) {
            _table[r][0] = 0;
            return table[r][0];
        }
    } else _table[r][0] = 1;
    if (BTN_IN_1) {
        if (_table[r][1]) {
            _table[r][1] = 0;
            return table[r][1];
        }
    } else _table[r][1] = 1;
    if (BTN_IN_2) {
        if (_table[r][2]) {
            _table[r][2] = 0;
            return table[r][2];
        }
    } else _table[r][2] = 1;
    if (BTN_IN_3) {
        if (_table[r][3]) {
            _table[r][3] = 0;
            return table[r][3];
        }
    } else _table[r][3] = 1;

    return 0;
}

