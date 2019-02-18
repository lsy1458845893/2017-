//
// Created by lsy on 17-7-30.
//

#ifndef STM32F4_TEST_ADC_BALLANCE_LOSE_H
#define STM32F4_TEST_ADC_BALLANCE_LOSE_H


#include <lcd.h>
#include <lcd_dev.h>

#include "os.h"
#include <math.h>
#include "syscall.hpp"
#include "stdio.h"
#include "Color.h"
#include "test_shower.h"

using namespace dev;

#include "font.h"

#include "ad9959fuc.h"

enum {
    KEY_0, KEY_1, KEY_2, KEY_3, KEY_4,
    KEY_5, KEY_6, KEY_7, KEY_8, KEY_9,
    KEY_DOT, KEY_NEWLINE,
    KEY_A, KEY_B, KEY_C, KEY_D,
    KEY_S1, KEY_S1U, KEY_S1D,
    KEY_S2, KEY_S2U, KEY_S2D,
    KEY_S3, KEY_S3U, KEY_S3D,
};

class Test_adc_ballance_lose {
private:
    gpio lose1[6];
    gpio lose2[6];
    int16_t lose = 10;
    adc adc1;
    Lcd *lcd;


public:
    static void keyborad(void *d, char chr) { ((Test_adc_ballance_lose *) d)->keyborad(chr); }

    void keyborad(char chr) {
        if (chr == KEY_S1U) lose = (lose < 126) ? lose + 1 : 126;
        else if (chr == KEY_S1D) lose = (lose > 0) ? lose - 1 : 0;
        adjust();
    }

    void adjust(void) {
        uint8_t a = 0, b = 0;
        a = lose / 2;
        b = lose - a;
        for (uint8_t i = 0; i < 6; i++) {
            lose1[i].output((a & (1 << i)) ? true : false);
            lose2[i].output((b & (1 << i)) ? true : false);
            if (a & (1 << i))lcd->show(100 + 6 * (5 - i), 50, '1');
            else lcd->show(100 + 6 * (5 - i), 50, '0');
            if (b & (1 << i))lcd->show(100 + 6 * (5 - i), 70, '1');
            else lcd->show(100 + 6 * (5 - i), 70, '0');
        }
    }

    static void update(void *d) { ((Test_adc_ballance_lose *) d)->update(); }

    void update(void) {
        uint16_t adcval = 2000;
        if (adc1.aleady()) {
            adcval = adc1.read();
            if (abs(adcval - 2000) > 200)
                (adcval < 2000) ?
                (lose = (lose > 0) ? lose - 1 : 0) :
                (lose = (lose < 126) ? lose + 1 : 126);
            adjust();
            char buf[50];
            sprintf(buf, "lose:%5.1f     ", (float) lose / 2);
            lcd->show(100, 100, buf);
            sprintf(buf, "adc:%d     ", adcval);
            printf("adc:%d\n", adcval);
            lcd->show(100, 120, buf);
            adc1.start(1);
        }

    }

    Test_adc_ballance_lose(Lcd *lcd)
            : adc1(adc(1)), lcd(lcd),
              lose1({gpio('I', 0), gpio('I', 1), gpio('I', 2), gpio('I', 3), gpio('I', 4), gpio('I', 5)}),
              lose2({gpio('I', 6), gpio('I', 7), gpio('I', 8), gpio('I', 9), gpio('I', 10), gpio('I', 11)}) {
        adc1.open(1);
        adc1.start(1);
    }

    static void main(void){

//    test_shower();
        usart io = usart(1, 9600);
        os_init(2, 'F', 10);
//    set_print_dev(&io);
        LCD_DEV lcd_dev = LCD_DEV();
        Lcd lcd = Lcd(&lcd_dev);

        Test_adc_ballance_lose test = Test_adc_ballance_lose(&lcd);
        setInterval(Test_adc_ballance_lose::update, &test, 20);
        io.recv(Test_adc_ballance_lose::keyborad, &test);
        while (true) {
            while (!os_execult());
        }
    }
};


#endif //STM32F4_TEST_ADC_BALLANCE_LOSE_H
