
#include <oled.h>
#include <stm32f10x_gpio.h>
#include <same.h>
#include "stm32f10x.h"
#include "delay.h"
#include "led.h"

#include "timex.h"
#include "time.h"
#include "usart.h"
#include "exti.h"

#include "syscall.h"
#include "stdio.h"
#include "adc.h"
#include "AD5663.h"
#include "math.h"
#include "ADF4350.h"

//
//static uint16_t cursor;
//
//
//static void coding_switch(void *d) {
//    static char state;
//    if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_5)) {
//        if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_4)) {
//            state = 0;
//        } else {
//            if (state == 0) {
//                ad5663->output(0, cursor += 100);
//                state = 1;
//            }
//        }
//    } else {
//        if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_4)) {
//            if (state == 0) {
//                ad5663->output(0, cursor -= 100);
//                state = 1;
//            }
//        } else {
//            state = 1;
//        }
//    }
//}
//
//
//static void print_cursor(void *d) {
//    printf("cur:%f%%\n", ((float) cursor) / 655.36);
//}
//
//static void print_temp(void *str) {
//    printf((const char *) str);
//}
//
//
//static void output_sin(void *d) {
//    cursor += 1;
////    DAC_SET(0, (uint16_t) (65536 * sin(((float )cursor)/600)));
//    ad5663->output(0, (uint16_t) (65536 * sin(((float) cursor) / 600)));
//}



static Time *htim;
static Timex *stim;
static Exti *cs;
static OLED *oled;
static AD5663 *ad5663;


void start_new_session(void *d) {
    static uint16_t count = 0;
    stim->setTimeout(start_new_session, NULL, 30);
}


int main(void) {
    delay_init(72);
    sysio = new USART(USART1, 9600);
    htim = new Time(TIM2);
    stim = new Timex();
    htim->setPeriod(1000);

    OLED oled = OLED(GPIOA, GPIO_Pin_0, GPIOA, GPIO_Pin_1);
    oled.print(1,1,(char *)"TEST");
    oled.commit();
//    GPIO_INIT_IN(GPIOB, GPIO_Pin_5);
//    GPIO_INIT_IN(GPIOB, GPIO_Pin_4);
//    ad5663 = new AD5663(GPIOB, GPIO_Pin_13, GPIOB, GPIO_Pin_14,
//                        GPIOB, GPIO_Pin_8, GPIOB, GPIO_Pin_10);
//    cursor = 30000;

//    ad5663_init();
    stim->setInterval(Led::change, new Led(GPIOC, GPIO_Pin_13), 103);
    stim->setTimeout(start_new_session, NULL, 97, 10);
//    stim->setInterval(print_cursor, NULL, 1007);
//    stim->setInterval(coding_switch, NULL, 2);
//    stim->setInterval(output_sin, NULL, 1);

//    ADF4350 *adf4350 = new ADF4350(
//            GPIOA, GPIO_Pin_0,
//            GPIOA, GPIO_Pin_1,
//            GPIOA, GPIO_Pin_2
//    );
//
//    adf4350->freq(40e6);

    htim->setCallback(Timex::update, stim);
    htim->start();
//    Led *led = new Led(GPIOC, GPIO_Pin_13);

    uint32_t temp;

    ADF4350 pll = ADF4350(
            GPIOA, GPIO_Pin_0,
            GPIOA, GPIO_Pin_1,
            GPIOA, GPIO_Pin_2
    );
    pll.freq(40e6);
    while (1) {
        while (stim->execute() <= 0);
        temp = stim->execute();
        printf("%d\n", temp);
    }
}





