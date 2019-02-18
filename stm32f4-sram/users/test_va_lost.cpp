////
//// Created by lsy on 17-7-10.
////
//
//#include "test_va_lost.h"
//
//
//#include "stdlib.h"
//#include "stdint.h"
//#include "device.hpp"
//#include "timex.hpp"
//#include "lcd.h"
//#include "lcd_dev.h"
//
//#include "stdio.h"
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
//using namespace dev;
//
//class Switch_coding_1 {
//public:
//    gpio *g1;
//    gpio *g2;
//    uint16_t num = 0;
//    char state = 0;
//
//    Switch_coding_1(gpio *g1, gpio *g2) : g1(g1), g2(g2) {
//        g1->init_input();
//        g2->init_input();
//    }
//
//    static void check(void *s) {
//        ((Switch_coding_1 *) s)->check();
//    }
//
//    void check(void) {
//        if (g1->read()) {
//            if (g2->read()) {
//                state = 0;
//            } else {
//                if (state == 0) {
//                    state = 1;
//                    num += 1;
//                    num %= 64;
//                }
//            }
//        } else {
//            if (g2->read()) {
//                if (state == 0) {
//                    state = -1;
//                    num -= 1;
//                    num %= 64;
//                }
//            } else {
//                state = -2;
//            }
//        }
//    }
//};
//
//void test_va_lost(void) {
//    delay_init(168);
//
//    gpio led = gpio('F', 10);
//    LCD_DEV lcd_dev = LCD_DEV();
//    Lcd lcd = Lcd(&lcd_dev);
//
//    lcd.print(100, 10, "Fa Q", color.WHITE, color.BLACK);
//
//    time htim = time(2);
//    timex stim = timex();
//    htim.setCallback(timex::update, &stim);
//
//    stim.setInterval(gpio::toggle, &led, 100);
//
//    time sctim = time(3);
//    Switch_coding_1 sc = Switch_coding_1(new gpio('F', 7), new gpio('F', 8));
//    sctim.setCallback(Switch_coding_1::check, &sc);
//    sctim.period(100);
//
//    gpio lose[6] = {gpio('I', 0), gpio('I', 1), gpio('I', 2), gpio('I', 3), gpio('I', 4), gpio('I', 5)};
//
//    uint16_t t = 0;
//    uint8_t tmp = 6;
//    char buf[100];
//    while (true) {
//        while (!stim.execute());
//        switch (t++) {
//            case 0:
//                sprintf(buf, "%d      ", sc.num);
//                lcd.print(100, 100, buf, color.YELLOW, color.BLACK);
//                break;
//            case 1:
//                tmp = 6;
//                while (tmp--)
//                    if (sc.num & (1 << tmp)) lose[tmp].output(1);
//                    else lose[tmp].output(0);
//                break;
//            default:
//                t = 0;
//                break;
//        }
//    }
//}