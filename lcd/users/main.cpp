/**
 *
 * 编码器 b8 b9
 * key1 a1
 * key2 a2
 * led f10
 *
 * + DAC 0   0 - 65535 --
 * + DAC 1   0 - 65535 ？
 * + ADC     0 - 4096
 *
 *   增益     0 - 60
 *   输入值   0 - 60
 *   当前带宽  0 - 60
 *
 */
#include <led.h>
#include "delay.h"
#include "lcd.h"
#include "color.h"
#include "adc.h"
#include <stdio.h>
#include <stm32f4xx_gpio.h>
#include <tgmath.h>
#include <stm32f4xx_conf.h>
#include <oled.h>
#include "AD5663.h"
#include "stdlib.h"
#include "button.h"
#include "sys.h"
#include "wave_shower.h"


#define AMP_DAC(DB) (((DB)-3.36322)*638.7898764580378)
#define AMP_DB(DAC) (3.36322 + 0.00156546*(DAC))

Led *led;
LCD_DEV *lcd_dev;
Lcd *lcd;
Adc *adc;
AD5663 *dac;


void refresh(void) {

    static uint16_t dac0 = 9210;
    static uint16_t dac1 = 37000;
    static char codingswitch = 0;
    static uint32_t ct = 0;
    static char input[10];
    static char amp_reset = 100;
    static char amp_btn_last = 0;

    char buff[50];
    uint16_t adc_c;
    ct++;


    if (ct % 1000 == 00) {
        adc_c = adc->blockConvert(5);
        sprintf(buff, "ADC : %fv -> %d     ", ((float) adc_c) / 1241.212121, adc_c);
        lcd->print(100, 100, buff, color.YELLOW, color.BLACK);
    }

    if (ct % 1000 == 200) {
        sprintf(buff, "DAC1: %fv -> %d     ", ((float) dac0) / 19859.09090909091, dac0);
        lcd->print(100, 130, buff, color.YELLOW, color.BLACK);
    }

    if (ct % 1000 == 400) {
        sprintf(buff, "DAC2: %fv -> %d     ", ((float) dac1) / 19859.09090909091, dac1);
        lcd->print(100, 160, buff, color.YELLOW, color.BLACK);
    }

    if (ct % 1000 == 600) {
        sprintf(buff, "Gain: %.1f db    ", AMP_DB(dac0));
        lcd->print(100, 190, buff, color.YELLOW, color.BLACK);
    }

    static float reset_gain = 5;

    if (abs((int) (reset_gain - AMP_DB(dac0))) > 4.6) {
        reset_gain = (float) AMP_DB(dac0);
        amp_reset = 100;
        GPIO_ResetBits(GPIOF, GPIO_Pin_7);
        delay_ms(1000);
    }

    if (ct % 100 == 50) {
        char recv_key;
        static char r = 0;
        recv_key = button_read(r);
        if (++r >= 4)r = 0;
        button_prepare(r);

        if (recv_key) {
            uint8_t cur = 0;
            float gain = (float) AMP_DB(dac0);
            if (recv_key == 'A') {
                while (input[cur] != 0)cur++;
                if (cur > 0) input[cur - 1] = 0;
            } else if (recv_key == 'B') {
                sscanf(input, "%f", &gain);
                input[0] = 0;
                dac0 = (uint16_t) AMP_DAC(gain);
                dac->output(0, dac0);
            } else if (recv_key == '+') {
                gain = (gain + 5);
                dac0 = (uint16_t) AMP_DAC(gain);
                dac->output(0, dac0);
            } else if (recv_key == '-') {
                gain = (gain - 5);
                dac0 = (uint16_t) AMP_DAC(gain);
                dac->output(0, dac0);
            } else if (('0' <= recv_key && recv_key <= '9') || recv_key == '.') {
                while (input[cur] != 0)cur++;
                if (cur < 9)input[cur] = recv_key;
                input[cur + 1] = 0;
            } else if (recv_key == 'F') {
                static char filter_cmd = 0;
                if (filter_cmd)filter_cmd = 0; else filter_cmd = 1;
                if (filter_cmd)lcd->print(100, 250, (char *) "filter 10MHz", color.YELLOW, color.BLACK);
                else lcd->print(100, 250, (char *) "filter 5MHz ", color.YELLOW, color.BLACK);
                if (filter_cmd) GPIO_ResetBits(GPIOF, GPIO_Pin_6);
                else GPIO_SetBits(GPIOF, GPIO_Pin_6);
            }
            sprintf(buff, "input:  %s    ", input);
            lcd->print(100, 220, buff, color.YELLOW, color.BLACK);
        }
    }

    if (!GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_2)) {
        if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_8)) {
            if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_9)) {
                codingswitch = 1;
            } else {
                if (codingswitch) {
                    codingswitch = 0;
                    dac1 += 10;
                    dac->output(1, dac1);
                }
            }
        } else {
            if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_9)) {
                if (codingswitch) {
                    codingswitch = 0;
                    dac1 -= 10;
                    dac->output(1, dac1);
                }
            } else {
                codingswitch = 0;
            }
        }
    } else {
        if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_8)) {
            if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_9)) {
                codingswitch = 1;
            } else {
                if (codingswitch) {
                    codingswitch = 0;
                    dac0 += 10;
                    dac->output(0, dac0);
                }
            }
        } else {
            if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_9)) {
                if (codingswitch) {
                    codingswitch = 0;
                    dac0 -= 10;
                    dac->output(0, dac0);
                }
            } else {
                codingswitch = 0;
            }
        }
    }


//    static char amp_reset = 0;
//    if (!GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1)) {
//        if (amp_reset == 0)amp_reset = 1;
//    };
//
//    if (amp_reset) {
//        int16_t diff = (uint16_t) (adc->blockConvert(5) - 2000);
//        dac1 -= diff;
//        if (-10 < diff && diff < 10) amp_reset = 0;
//    }

    if (ct % 10 == 3) {

        char amp_btn_now = 0;

        amp_btn_now = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1);
        if (amp_btn_now != amp_btn_last && amp_btn_last) {
//        lcd->print(100,70,'Y',color.WHITE,color.BLACK);
            amp_reset = 100;
            GPIO_ResetBits(GPIOF, GPIO_Pin_7);
            delay_ms(1000);
        }
        amp_btn_last = amp_btn_now;

        if (amp_reset) {
            GPIO_ResetBits(GPIOF, GPIO_Pin_7);
#define DIFF_NUM 64
            static uint8_t diff_cur = 0;
            static int16_t diff[DIFF_NUM];
            int32_t diff_mean = 0;
            if (adc->aleady()) {
                diff[diff_cur++ % DIFF_NUM] = (int16_t) ((adc->read() - 1241));
                adc->start(5);
            }
            uint8_t diff_cur_t = DIFF_NUM;
            uint8_t diff_flag = 0;
            while (diff_cur_t--) {
                diff_mean += diff[diff_cur_t];
                if (-5 <= diff[diff_cur_t] && diff[diff_cur_t] <= 5) diff_flag = 1;
            }

            dac1 -= (diff_mean / (DIFF_NUM * 30));
//        dac1 -= diff;
            dac->output(1, dac1);

            if (diff_flag) {
                amp_reset--;
                delay_ms(5);
//            lcd->print(100,70,'N',color.WHITE,color.BLACK);
            }
        } else GPIO_SetBits(GPIOF, GPIO_Pin_7);
    }
}


void init(void) {
    GPIO_InitTypeDef gpio;
    RCC_APB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); // key
    gpio.GPIO_OType = GPIO_OType_OD;
    gpio.GPIO_Mode = GPIO_Mode_IN;
    gpio.GPIO_PuPd = GPIO_PuPd_UP;
    gpio.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2;
    GPIO_Init(GPIOA, &gpio);

    RCC_APB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE); // 继电器
    gpio.GPIO_OType = GPIO_OType_OD;
    gpio.GPIO_Mode = GPIO_Mode_OUT;
    gpio.GPIO_Speed = GPIO_Speed_50MHz;
    gpio.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
    GPIO_Init(GPIOF, &gpio);
    GPIO_SetBits(GPIOF, GPIO_Pin_6 | GPIO_Pin_7);

    RCC_APB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE); // 编码器
    gpio.GPIO_OType = GPIO_OType_OD;
    gpio.GPIO_Mode = GPIO_Mode_IN;
    gpio.GPIO_PuPd = GPIO_PuPd_NOPULL;
    gpio.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
    GPIO_Init(GPIOB, &gpio);

    RCC_APB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE); // da clear
    gpio.GPIO_OType = GPIO_OType_PP;
    gpio.GPIO_Mode = GPIO_Mode_OUT;
    gpio.GPIO_Speed = GPIO_Speed_100MHz;
    gpio.GPIO_Pin = GPIO_Pin_6;
    GPIO_Init(GPIOG, &gpio);
    GPIO_SetBits(GPIOG, GPIO_Pin_6);


//    RCC_APB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE); // dac reset
//    gpio.GPIO_OType = GPIO_OType_PP;
//    gpio.GPIO_Mode = GPIO_Mode_OUT;
//    gpio.GPIO_Speed = GPIO_Speed_100MHz;
//    gpio.GPIO_Pin = GPIO_Pin_15;
//    GPIO_Init(GPIOC, &gpio);
//    GPIO_SetBits(GPIOC, GPIO_Pin_15);


//    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
//    gpio.GPIO_OType = GPIO_OType_PP;
//    gpio.GPIO_Mode = GPIO_Mode_OUT;
//    gpio.GPIO_Speed = GPIO_Speed_100MHz;
//    gpio.GPIO_PuPd = GPIO_PuPd_NOPULL;
//    gpio.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_3 | GPIO_Pin_5 | GPIO_Pin_7;
//    GPIO_Init(GPIOC, &gpio);
//
//    gpio.GPIO_Mode = GPIO_Mode_IN;
//    gpio.GPIO_PuPd = GPIO_PuPd_NOPULL;
//    gpio.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_11 | GPIO_Pin_13;
//    GPIO_Init(GPIOC, &gpio);
}


//int main(void) {
//    delay_init(168);
//
//    LCD_DEV _lcd_dev = LCD_DEV();
//    lcd_dev = &_lcd_dev;
//
//    Lcd _lcd = Lcd(lcd_dev);
//    lcd = &_lcd;
//
//    AD5663 _dac = AD5663(
//            GPIOB, GPIO_Pin_13,
//            GPIOB, GPIO_Pin_14,
//            GPIOG, GPIO_Pin_8,
//            GPIOG, GPIO_Pin_7
//    );
//    dac = &_dac;
//    dac->output(0, 9210);
//    dac->output(1, 37000);
//
//    Adc _adc = Adc(ADC1);
//    adc = &_adc;
//    adc->openChannl(5);
//
//    button_init();
//
//    init();
//
//    GPIO_ResetBits(GPIOF, GPIO_Pin_7);
//    delay_ms(1000);
//
////    uint16_t size = 0;
////    char buff[100];
////    while (malloc(100)) size += 100;
////    sprintf(buff, "%d", size);
////    lcd->print(100, 100, buff, color.WHITE, color.BLACK);
//
//    lcd->print(100, 250, (char *) "filter 5MHz ", color.YELLOW, color.BLACK);
//    while (1) refresh();
//
//}



int main(void) {
    delay_init(168);
    OLED oled = OLED(RCC_AHB1Periph_GPIOA, GPIOA, GPIO_Pin_0, GPIOA, GPIO_Pin_1);
    while (true){
        oled.print(1,1,0,"TEST");
        oled.commit();
    }
}





//void dot(Lcd *lcd, u16 x, u16 y) {
//    char buf[30] = {};
//    lcd->line((u16) (x - 5), y, (u16) (x + 5), y, color.RED);
//    lcd->line(x, (u16) (y - 5), x, (u16) (y + 5), color.RED);
//    str_append(buf, '[');
//    str_uint(&(buf[str_length(buf)]), x);
//    str_append(buf, ',');
//    str_uint(&(buf[str_length(buf)]), y);
//    str_append(buf, ']');
//    lcd->print((u16) (x + 5), (u16) (y + 5), buf, color.BLACK, color.YELLOW);
//}



//int main(void) {
//    delay_init(168);
//
//    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
//
//    LCD_DEV lcd_dev = LCD_DEV();
//    Lcd lcd = Lcd(&lcd_dev);
//
//    Adc adc = Adc(ADC1);
//    adc.openChannl(5);
//
////    char buff[30];
////    u16 data[600] = {}, t = 0, a;
////    Wave_shower shower = Wave_shower(&lcd, 20, 60);
////    shower.prepare();
//
//
//
////    Led led = Led(RCC_AHB1Periph_GPIOF, GPIOF, GPIO_Pin_10);
//
////    u16 temp = 100;
////    lcd_dev.cursor(100, 100);
////    while (temp--)lcd_dev.write(color.RED);
////    temp = 100;
////    while (temp--)lcd.dot(101, 100 + temp, color.BLUE);
//
////    lcd.rect(10, 10, 110, 50, color.BLUE);
////    lcd.rect(110, 10, 210, 50, color.GREEN);
////    lcd.rect(210, 10, 310, 50, color.RED);
//
////    Touchpad tp = Touchpad(&lcd_dev);
//
////    TP_Init(&lcd_dev);
//
////    u16 x, y;
//
////    USART uart = USART(USART1,9600);
//
////    while (malloc(100)) printf("malloc(100)\n");
//
//    char buff[30];
//    while (1) {
//        delay_ms(100);
//        sprintf(buff,"%d     ",adc.blockConvert(5));
//        lcd.print(10,10,buff,color.WHITE,color.BLACK);
////        uart.send((char *) "hello world\n");
////        sysio->send((char *) "hello world\n");
////        shower.prepare();
////        TP_Scan(0);
////        TP_Scan(0);
////        if (TP_Read_XY(&x, &y))lcd.dot(x, y,color.WHITE);
////        tp.scan();
////        if (tp.press(10, 10, 110, 50))
////            lcd.print(315, 20, "you press blue   ", color.RED, color.BLACK);
////        else if (tp.press(110, 10, 210, 50))
////            lcd.print(315, 20, "you press green  ", color.RED, color.BLACK);
////        else if (tp.press(210, 10, 310, 50))
////            lcd.print(315, 20, "you press red    ", color.RED, color.BLACK);
////        else lcd.print(315, 20, "                ", color.RED, color.BLACK);
////
////        if(tp.press()) lcd.dot(tp.x(),tp.y(),color.LGRAYBLUE);
////        else lcd.print(315, 20, "you press nothing", color.RED, color.BLACK);
//
//    }
//}


#include <stm32f4xx_conf.h>
#include <delay.h>
#include "stm32f4xx.h"

//int main(void){
//
//    delay_init(168);
//    GPIO_InitTypeDef gpio;
//    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);
//    gpio.GPIO_OType = GPIO_OType_PP;
//    gpio.GPIO_Mode = GPIO_Mode_OUT;
//    gpio.GPIO_Speed = GPIO_Speed_100MHz;
//    gpio.GPIO_PuPd = GPIO_PuPd_NOPULL;
//    gpio.GPIO_Pin = GPIO_Pin_7;
//    GPIO_Init(GPIOC,&gpio);
//    while (1){
//        delay_ms(100);
//        GPIO_SetBits(GPIOC,GPIO_Pin_7);
//        delay_ms(100);
//        GPIO_ResetBits(GPIOC,GPIO_Pin_7);
//    }
//}