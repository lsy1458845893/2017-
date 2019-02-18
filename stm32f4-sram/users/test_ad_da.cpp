////
//// Created by lsy on 17-7-10.
////
//
//#include "test_ad_da.h"
//
//#include <timex.hpp>
//#include <AD5663.h>
//#include <stm32f4xx_conf.h>
//#include "stdio.h"
//#include "device.hpp"
//
//using namespace dev;
//
//
//class Switch_coding {
//public:
//    gpio *g1;
//    gpio *g2;
//    uint16_t num = 0;
//    char state = 0;
//    uint16_t tims = 0;
//    uint16_t max = 0;
//    AD5663 *dac = NULL;
//
//    Switch_coding(gpio *g1, gpio *g2, AD5663 *dac) : g1(g1), g2(g2), dac(dac) {
//        g1->init_input();
//        g2->init_input();
//    }
//
//    static void check(void *s) {
//        ((Switch_coding *) s)->check();
//    }
//
//    void check(void) {
//        if (g1->read()) {
//            if (g2->read()) {
//                state = 0;
//                tims++;
//            } else {
//                if (state == 0) {
//                    state = 1;
//                    num += 100;
//                    dac->output(1, num);
//                }
//            }
//        } else {
//            if (g2->read()) {
//                if (state == 0) {
//                    state = -1;
//                    num -= 100;
//                    dac->output(1, num);
//                }
//            } else {
//                state = -2;
//                max = tims;
//                tims = 0;
//            }
//        }
//    }
//};
//
//
//#include "lcd_dev.h"
//#include "lcd.h"
//
//static class _lcd_color_ {
//public:
//    u16 WHITE = 0xFFFF;
//    u16 BLACK = 0x0000;
//    u16 BLUE = 0x001F;
//    u16 BRED = 0XF81F;
//    u16 GRED = 0XFFE0;
//    u16 GBLUE = 0X07FF;
//    u16 RED = 0xF800;
//    u16 MAGENTA = 0xF81F;
//    u16 GREEN = 0x07E0;
//    u16 CYAN = 0x7FFF;
//    u16 YELLOW = 0xFFE0;
//    u16 BROWN = 0XBC40;
//    u16 BRRED = 0XFC07;
//    u16 GRAY = 0X8430;
//    u16 DARKBLUE = 0X01CF;
//    u16 LIGHTBLUE = 0X7D7C;
//    u16 GRAYBLUE = 0X5458;
//    u16 LIGHTGREEN = 0X841F;
//    u16 LGRAY = 0XC618;
//    u16 LGRAYBLUE = 0XA651;
//    u16 LBBLUE = 0X2B12;
//} const color;
//
//
//void test_ad_da(void){
//
//    gpio *led = new gpio('F', 10);
//    led->init_output();
//    adc adc1 = adc(1);
//    adc1.open(1);
//    adc1.start(1);
//
//    AD5663 *dac = new AD5663(
//            gpio('B', 13), gpio('B', 14),
//            gpio('D', 2), gpio('D', 3)
//    );
//    gpio clr = gpio('G', 11);
//    clr.init_output();
//    clr.output(1);
//
//    dac->output(1, 0);
//
//    Switch_coding sc = Switch_coding(new gpio('F', 7), new gpio('F', 8), dac);
//
//    usart *io = new usart(1, 9600);
//    time *ht = new time(3);
//    timex *st = new timex();
//    time *sctim = new time(4);
//
//    st->setInterval(gpio::toggle, led, 100);
//    ht->setCallback(timex::update, st);
//
//    sctim->setCallback(Switch_coding::check, &sc);
//    sctim->period(100);
//
//    char buf[50];
//
//    delay_init(168);
//
//    LCD_DEV *dev1 = new LCD_DEV();
//    Lcd *lcd = new Lcd(dev1);
//
//    vu16 tt = 0;
//    while (true) {
//        while (!st->execute());
//        switch (tt++ % 2) {
//            case 0:
//                if (adc1.aleady()) {
//                    sprintf(buf, "adc: %d    ", adc1.read());
//                    io->send(buf);
//                    lcd->print(100, 150, buf, color.YELLOW, color.BLACK);
//                    adc1.start(1);
//                }
//                break;
//            case 1:
//                sprintf(buf, "dac0: %d       ", sc.num);
//                lcd->print(100, 100, buf, color.YELLOW, color.BLACK);
//                break;
//            default:
//                break;
//        }
//    }
//}