//
//#include "os.h"
//#include "device.hpp"
//#include "syscall.hpp"
//#include "LMH6518.h"
//#include "lcd.h"
//#include "stdio.h"
//#include "ADF4350.h"
//#include "ad9959fuc.h"
//
//using namespace dev;
//
//#include <LTC2440.h>
//#include <stm32f4xx_conf.h>
//#include <AD5663.h>
//#include "math.h"
//
//class Recv_test {
//private:
//    enum {
//        KEY_0, KEY_1, KEY_2, KEY_3, KEY_4,
//        KEY_5, KEY_6, KEY_7, KEY_8, KEY_9,
//        KEY_DOT, KEY_NEWLINE,
//        KEY_A, KEY_B, KEY_C, KEY_D,
//        KEY_S1, KEY_S1U, KEY_S1D,
//        KEY_S2, KEY_S2U, KEY_S2D,
//        KEY_S3, KEY_S3U, KEY_S3D,
//    };
//
//    usart io;
//    LCD_DEV lcd_dev;
//    Lcd lcd;
//
//    struct {
//        float freq;
//        uint16_t amp;
//        uint16_t phase;
//    } dds[4] = {
//            {1e6, 1000, 0},
//            {1e6, 1000, 0},
//            {1e6, 1000, 0},
//            {1e6, 1000, 0}
//    };
//
//    bool need_update = true;
//    uint8_t select_ch = 0;
//
//public:
//    Recv_test(usart io)
//            : io(io), lcd_dev(LCD_DEV()), lcd(Lcd(&lcd_dev)) {
//        AD9959_Init();
//        io.recv(keyborad_recv, this);
//    }
//
//    static void update(void *obj) { ((Recv_test *) obj)->update(); }
//
//    void update(void) {
//        if (need_update) {
//            char buf[100];
//            sprintf(buf, "select ch %d", select_ch);
//            lcd.show(100, 70, buf);
//
//            sprintf(buf, "freq=%5.5fMHz; amp=%2.3f%%; phase=%2.3f%%;      ",
//                    dds[0].freq / 1e6, dds[0].amp / 20.48, dds[0].phase / 16384);
//            lcd.show(100, 100, buf);
//
//            sprintf(buf, "freq=%5.5fMHz; amp=%2.3f%%; phase=%2.3f%%;      ",
//                    dds[1].freq / 1e6, dds[1].amp / 20.48, dds[1].phase / 16384);
//            lcd.show(100, 130, buf);
//
//            sprintf(buf, "freq=%5.5fMHz; amp=%2.3f%%; phase=%2.3f%%;      ",
//                    dds[2].freq / 1e6, dds[2].amp / 20.48, dds[2].phase / 16384);
//            lcd.show(100, 160, buf);
//
//            sprintf(buf, "freq=%5.5fMHz; amp=%2.3f%%; phase=%2.3f%%;      ",
//                    dds[3].freq / 1e6, dds[3].amp / 20.48, dds[3].phase / 16384);
//            lcd.show(100, 190, buf);
//
//            AD9959_Set_Fre(AD9959_CH0, dds[0].freq);
//            AD9959_Set_Amp(AD9959_CH0, dds[0].amp);
//            AD9959_Set_Phs(AD9959_CH0, dds[0].phase);
//
//            AD9959_Set_Fre(AD9959_CH1, dds[1].freq);
//            AD9959_Set_Amp(AD9959_CH1, dds[1].amp);
//            AD9959_Set_Phs(AD9959_CH1, dds[1].phase);
//
//            AD9959_Set_Fre(AD9959_CH2, dds[2].freq);
//            AD9959_Set_Amp(AD9959_CH2, dds[2].amp);
//            AD9959_Set_Phs(AD9959_CH2, dds[2].phase);
//
//            AD9959_Set_Fre(AD9959_CH3, dds[3].freq);
//            AD9959_Set_Amp(AD9959_CH3, dds[3].amp);
//            AD9959_Set_Phs(AD9959_CH3, dds[3].phase);
//
//            AD9959_Update();
//            need_update = false;
//        }
//    }
//
//    static void keyborad_recv(void *obj, char ch) { ((Recv_test *) obj)->keyborad_recv(ch); }
//
//#define RANG_CHECK(key, var, step, l, h) \
//    if (ch == KEY_S##key##U) var = ( var + step < h ) ? var + step : h - 1;\
//    if (ch == KEY_S##key##D) var = ( var - step > l ) ? var - step : l;
//
//    void keyborad_recv(char ch) {
//        need_update = true;
//        RANG_CHECK(1, dds[select_ch].freq, 1e6, 9e3, 40e6);
//        RANG_CHECK(2, dds[select_ch].amp, 1, 0, 2048);
//        RANG_CHECK(3, dds[select_ch].phase, 10, 0, 16384);
//        if (KEY_A == ch) select_ch = ++select_ch % 4;
//    }
//};
//
//static const float lose_db_to_mv_table[] = {
//        0, 0, 0, 0, 0, 100, 97.6, 93.6, 89.1072, 84.6144, 80.8704,
//        76.752, 70.2, 66.6432, 62.8992, 60.2784, 58.7808, 56.16,
//        52.7904, 50.8248, 46.4256, 44.1792, 41.9328, 39.6864,
//        37.44, 35.568, 33.3216, 31.824, 29.2032, 28.08, 26.5824,
//        25.4592, 25.272, 24.336, 23.2128, 22.0896, 20.2176,
//        19.188, 18.3456, 16.848, 14.04, 13.1976, 12.4488,
//        11.8872, 10.764, 10.296, 9.9216, 9.36, 9.0792,
//        8.6112, 8.2368, 7.8624, 7.2072, 6.9264, 6.6456,
//        6.3648, 5.9904, 5.616, 5.4288, 5.0544, 4.68, 4.4928,
//};
//
//
//#define EXEC_POOL_SIZE 30
//
//struct {
//    bool flag = false;
//    void *dat;
//
//    void (*func)(void *);
//} exec_pool[EXEC_POOL_SIZE] = {};
//
//void func_init(void) {
//    uint8_t t = EXEC_POOL_SIZE;
//    while (t--)exec_pool[t].flag = false;
//}
//
//void func_mark(void (*func)(void *), void *dat) {
//    for (uint16_t t = 0; t < EXEC_POOL_SIZE; t++) {
//        if (!exec_pool[t].flag) {
//            exec_pool[t].flag = true;
//            exec_pool[t].dat = dat;
//            exec_pool[t].func = func;
//            return;
//        }
//    }
//}
//
//void func_check(void) {
//    for (uint16_t t = 0; t < EXEC_POOL_SIZE; t++)
//        if (exec_pool[t].flag) {
//            exec_pool[t].flag = false;
//            exec_pool[t].func(exec_pool[t].dat);
//        }
//}
//
//
//class Contest {
//private:
//    enum {
//        KEY_0, KEY_1, KEY_2, KEY_3, KEY_4,
//        KEY_5, KEY_6, KEY_7, KEY_8, KEY_9,
//        KEY_DOT, KEY_NEWLINE,
//        KEY_A, KEY_B, KEY_C, KEY_D,
//        KEY_S1, KEY_S1U, KEY_S1D,
//        KEY_S2, KEY_S2U, KEY_S2D,
//        KEY_S3, KEY_S3U, KEY_S3D,
//    };
//
//    Lcd lcd;
//
//#define COMPUTE_FREQ(i, min, max, step) min + i * (max - min)/step
//
//    float freq_min = 1e6;
//    float freq_max = 40e6;
//    uint16_t point_num = 100;
//    bool continue_scan = false;
//    int32_t *adcx_val = NULL;
//    int32_t *adcy_val = NULL;
//    float *adc_val = NULL;
//    float *offset = NULL;
//    uint16_t cursor = 0;
//    uint8_t lose = 5;
//
//    gpio loser[6];
//    usart io;
//    usart cmd_io;
//    gpio cmd_en;
//    gpio relay;
//    LTC2440 adcx;
//    LTC2440 adcy;
//    AD5663 dac;
//
//
//    int32_t offset_x;
//    int32_t offset_y;
//
//public:
//    Contest(Lcd lcd, usart io)
//            : io(io), lcd(lcd), relay(gpio('G', 9)), cmd_io(usart(2, 115200)), cmd_en(gpio('A', 0)),
//              loser({gpio('I', 0), gpio('I', 1), gpio('I', 2), gpio('I', 3), gpio('I', 4), gpio('I', 5)}),
//              dac(AD5663(gpio('A', 5), gpio('A', 6), gpio('D', 2), gpio('D', 3))),
//              adcx(LTC2440(gpio('H', 12), gpio('H', 13), gpio('H', 14), gpio('H', 15))),
//              adcy(LTC2440(gpio('H', 9), gpio('H', 8), gpio('H', 7), gpio('H', 6))) {
//        gpio('G', 11).output(1);
//        cmd_en.init_input();
//        AD9959_Init();
//
//        AD9959_Set_Amp(AD9959_CH0, 307);
//        AD9959_Set_Amp(AD9959_CH2, 479);
//        AD9959_Set_Amp(AD9959_CH3, 479);
//        AD9959_Set_Phs(AD9959_CH3, 84);
//
//        io.recv(keyborad_recv, this);
//        cmd_io.recv((void (*)(void *, char)) command_recv_fun, this);
//
//        GPIO_InitTypeDef cfg;
//        cfg.GPIO_Mode = GPIO_Mode_OUT;
//        cfg.GPIO_OType = GPIO_OType_OD;
//        cfg.GPIO_PuPd = GPIO_PuPd_NOPULL;
//        relay.init(&cfg);
//
//        lcd.font_family = (char *) font_default_8x6;
//        lcd.font_x_size = 6;
//        lcd.font_y_size = 8;
//
//        set_point_number(100);
//        set_lose(lose);
//        set_freq(10e6);
//    }
//
//    ////////////////////////// function //////////////////////////////
//
//    void set_freq(double freq) {
//        AD9959_Set_Fre(AD9959_CH0, freq);
//        AD9959_Set_Fre(AD9959_CH2, freq);
//        AD9959_Set_Fre(AD9959_CH3, freq);
//        AD9959_Update();
//
//        char buf[30];
//        sprintf(buf, "freq:%4.4fMHz  ", freq / 1e6);
//        lcd.show(10, 0, buf);
//    }
//
//    void set_lose(uint8_t lose) {
//        loser[0].output(lose & (1 << 0));
//        loser[1].output(lose & (1 << 1));
//        loser[2].output(lose & (1 << 2));
//        loser[3].output(lose & (1 << 3));
//        loser[4].output(lose & (1 << 4));
//        loser[5].output(lose & (1 << 5));
//        char buf[30];
//        sprintf(buf, "lose:%2.1fdb   ", (float) lose / 2);
//        lcd.show(300, 0, buf);
//    }
//
//    void set_relay(bool gnd) {
//        relay.output(gnd ? 0 : 1);
//    }
//
//    void show_wave(float *dat, uint16_t len) {
//        // x (0,1)
//#define COOD_X(x) (600*(x) + 20)
//        // y (-1,1)
//#define COOD_Y(y) (260 - 200*(y))
//
//        lcd.color = 0;
//        lcd.rect(COOD_X(0), COOD_Y(1), COOD_X(1), COOD_Y(-1));
//
//        lcd.color = 0xffff;
//        lcd.line(COOD_X(0), COOD_Y(1), COOD_X(1), COOD_Y(1));
//        lcd.line(COOD_X(0), COOD_Y(0), COOD_X(1), COOD_Y(0));
//        lcd.line(COOD_X(0), COOD_Y(-1), COOD_X(1), COOD_Y(-1));
//        lcd.line(COOD_X(0), COOD_Y(1), COOD_X(0), COOD_Y(-1));
//        lcd.line(COOD_X(1), COOD_Y(1), COOD_X(1), COOD_Y(-1));
//
//        if (dat)
//            for (uint16_t t = 0; t < len - 1; t++)
//                lcd.line((uint16_t) COOD_X((float) t / len),
//                         (uint16_t) COOD_Y(dat[t]),
//                         (uint16_t) COOD_X((float) (t + 1) / len),
//                         (uint16_t) COOD_Y(dat[t + 1]));
//
//    }
//
//    static void update_lose(void *d) { ((Contest *) d)->set_lose(((Contest *) d)->lose); }
//
//    void set_point_number(uint16_t p_num) {
//        point_num = p_num;
//        adcx_val = (int32_t *) realloc(adcx_val, p_num * sizeof(int32_t));
//        adcy_val = (int32_t *) realloc(adcy_val, p_num * sizeof(int32_t));
//        adc_val = (float *) realloc(adc_val, p_num * sizeof(float));
//        offset = (float *) realloc(offset, p_num * sizeof(float));
//    }
//
//    //////////////////// proccess //////////////////////////////
//
//
//
//
//    static void nomalize_process_0(void *d) { ((Contest *) d)->nomalize_process_0(); }
//
//    // nomalize setting
//    void nomalize_process_0(void) {
//        set_relay(1);
//        set_point_number(point_num);
//        // delay 200ms proccess_1
//        setTimeout(nomalize_process_1, this, 200);
//    }
//
//    static void nomalize_process_1(void *d) { ((Contest *) d)->nomalize_process_1(); }
//
//    // nomalize init
//    void nomalize_process_1(void) {
//        if (adcx.aready() && adcy.aready()) {
//            offset_x = adcx.read();
//            offset_y = adcy.read();
//            set_relay(0);
//            cursor = 0;
//            set_freq(COMPUTE_FREQ(cursor, freq_min, freq_max, point_num));
//            // start proccess_2
//            setTimeout(nomalize_process_2, this, 200);
//        } else func_mark(nomalize_process_1, this); // continue
//    }
//
//    static void nomalize_process_2(void *d) { ((Contest *) d)->nomalize_process_2(); }
//
//    // nomalize loop
//    void nomalize_process_2(void) {
//        if (cursor < point_num) {
//            if (adcx.aready() && adcy.aready()) {
//                adcx_val[cursor] = adcx.read() - offset_x;
//                adcy_val[cursor] = adcy.read() - offset_y;
//                cursor++;
//                set_freq(COMPUTE_FREQ(cursor, freq_min, freq_max, point_num));
//            }
//            setTimeout(nomalize_process_2, this, 10);// continue
//        } else {
//            // comput val = sqrt(x^2 + y^2)
//            //        offset = 1 / val
//            for (uint16_t t = 0; t < point_num; t++) {
//                float x, y;
//                x = ((float) adcx_val[t]) * 1.4901161193847656e-07;
//                y = ((float) adcy_val[t]) * 1.4901161193847656e-07;
//                adc_val[t] = (float) sqrt((double) (x * x + y * y));
//                printf("%2.5f %2.5f -> %2.5f\n", x, y, adc_val[t]);
//                offset[t] = 1 / adc_val[t];
//            }
//
//            float max = 0.01;
//            float min = 100000;
//
//            for (uint16_t t = 0; t < point_num; t++) {
//                max = adc_val[t] > max ? adc_val[t] : max;
//                min = adc_val[t] < min ? adc_val[t] : min;
//            }
//
//            for (uint16_t t = 0; t < point_num; t++)
//                adc_val[t] /= max;
//
//            char buf[40];
//            sprintf(buf, "max:%1.2fv  ", max);
//            lcd.show(640, 60, buf);
//            sprintf(buf, "min:%1.2fv  ", min);
//            lcd.show(640, 90, buf);
//
//            show_wave(adc_val, point_num);
//        }
//    }
//
//
//    static void echo_proccess(void *d) { ((Contest *) d)->echo_process_0(); }
//
//    void echo_process_0(void) {
//        static const uint8_t echo[4] = {0xaa, 0x55, 0xff, 0x00};
//        command_send((uint8_t *) echo, 4);
//    }
//
//
//    static void range_scan_process_0(void *d) { ((Contest *) d)->range_scan_process_0(); }
//
//    //  range scan setting
//    void range_scan_process_0(void) {
//        set_relay(1);
//        char buf[70];
//        sprintf(buf, "range(%f,%f,%d)     ", freq_min, freq_max, point_num);
//        lcd.show(450, 0, buf);
//        setTimeout(range_scan_process_1, this, 200);
//    }
//
//    static void range_scan_process_1(void *d) { ((Contest *) d)->range_scan_process_1(); }
//
//    //  range scan init
//    void range_scan_process_1(void) {
//        if (adcx.aready() && adcy.aready()) {
//            offset_x = adcx.read();
//            offset_y = adcy.read();
//            set_relay(0);
//            cursor = 0;
//            set_freq(COMPUTE_FREQ(cursor, freq_min, freq_max, point_num));
//            // start proccess_2
//            setTimeout(range_scan_process_2, this, 10);
//        } else func_mark(range_scan_process_1, this); // continue
//    }
//
//    static void range_scan_process_2(void *d) { ((Contest *) d)->range_scan_process_2(); }
//
//    //  range scan loop
//    void range_scan_process_2(void) {
//        if (cursor < point_num) {
//
//            // range scanniong
//            if (adcx.aready() && adcy.aready()) {
//                adcx_val[cursor] = adcx.read() - offset_x;
//                adcy_val[cursor] = adcy.read() - offset_y;
//                cursor++;
//                set_freq(COMPUTE_FREQ(cursor, freq_min, freq_max, point_num));
//            }
//            func_mark(range_scan_process_2, this); // continue
//        } else {
//
//            // range scan finished
//
//            for (uint16_t t = 0; t < point_num; t++) {
//                float x, y;
//                x = ((float) adcx_val[t]) * 1.4901161193847656e-07;
//                y = ((float) adcy_val[t]) * 1.4901161193847656e-07;
//                adc_val[t] = (float) sqrt((double) (x * x + y * y));
//                adc_val[t] *= offset[t];
//                adc_val[t] = 20 * log10f(adc_val[t]);
//            }
//
//            float max = 0.01;
//            float min = 100000;
//
//            for (uint16_t t = 0; t < point_num; t++) {
//                max = adc_val[t] > max ? adc_val[t] : max;
//                min = adc_val[t] < min ? adc_val[t] : min;
//            }
//
//            char buf[40];
//            sprintf(buf, "max:%1.2fdb", max);
//            lcd.show(640, 60, buf);
//            sprintf(buf, "min:%1.2fdb", min);
//            lcd.show(640, 90, buf);
//
//            if (continue_scan) func_mark(range_scan_process_0, this);
//        }
//    }
//
//    ////////////////////////////// command ////////////////////////////////////
//
//    uint8_t cmd_buf[40];
//    uint8_t cmd_cur = 0;
//    uint16_t skip_self = 0;
//
//    void command_send(uint8_t *dat, uint32_t len) {
//        skip_self = len;
//        for (uint32_t t = 0; t < len; t++)
//            cmd_io.send(dat[t]);
//    }
//
//    static void command_recv_fun(void *d, uint8_t ch) { ((Contest *) d)->command_recv(ch); }
//
//    void command_recv(uint8_t ch) {
//        if (cmd_en.read())
//            if (skip_self) skip_self--;
//            else {
//                uint32_t *reader = (uint32_t *) cmd_buf;
//                if (cmd_cur >= 4) {
//                    if (reader[0] == 0xaa55ff00) { // echo
//                        func_mark(Contest::echo_proccess, this);
//                        cmd_cur = 0;
//                    }
//
//
//                    if (reader[0] == 0xaa55ff00) { // nomalize
//                        // cmd len 4(cmd) + 4(start) + 4(end) + 4(step)
//                        if (cursor >= 16) {
//                            freq_min = reader[1];
//                            freq_max = reader[2];
//                            point_num = reader[3];
//                            func_mark(nomalize_process_0, this);
//                            cmd_cur = 0;
//                        }
//                    }
//
//                    if (reader[0] == 0x12451243) { // range scan
//                        cmd_cur = 0;
//                    }
//
//                    if (reader[0] == 0x12345232) { // point scan
//                    }
//                }
//            }
//    }
//
//    static void keyborad_recv(void *obj, char ch) { ((Contest *) obj)->keyborad_recv(ch); }
//
//    void keyborad_recv(char ch) {
//        RANG_CHECK(1, lose, 1, 0, 64);
//        func_mark(update_lose, this);
//        if (ch == KEY_A)
//            func_mark(nomalize_process_0, this);
//        if (ch == KEY_B)
//            func_mark(range_scan_process_0, this);
//
//    }
//
//};
//
//
//class Test_0 {
//    enum {
//        KEY_0, KEY_1, KEY_2, KEY_3, KEY_4,
//        KEY_5, KEY_6, KEY_7, KEY_8, KEY_9,
//        KEY_DOT, KEY_NEWLINE,
//        KEY_A, KEY_B, KEY_C, KEY_D,
//        KEY_S1, KEY_S1U, KEY_S1D,
//        KEY_S2, KEY_S2U, KEY_S2D,
//        KEY_S3, KEY_S3U, KEY_S3D,
//    };
//
//private:
//
//public:
//    float freq = 10e6;
//    uint8_t lose = 5;
//    uint16_t phase = 84;
//
//    usart io;
//    gpio relay;
//
//    float adc_offset_x, adc_offset_y;
//
//    Lcd lcd;
//    gpio loser[6];
//
//    LTC2440 adcx, adcy;
//
//    Test_0(Lcd lcd, usart io)
//            : io(io), lcd(lcd), relay(gpio('G', 9)),
//              adcx(LTC2440(gpio('H', 12), gpio('H', 13),
//                           gpio('H', 14), gpio('H', 15))),
//              adcy(LTC2440(gpio('H', 9), gpio('H', 8),
//                           gpio('H', 7), gpio('H', 6))),
//              loser({gpio('I', 0), gpio('I', 1), gpio('I', 2),
//                     gpio('I', 3), gpio('I', 4), gpio('I', 5)}) {
//        AD9959_Init();
//        io.recv(keyborad_recv, this);
//
//        GPIO_InitTypeDef cfg;
//        cfg.GPIO_Mode = GPIO_Mode_OUT;
//        cfg.GPIO_OType = GPIO_OType_OD;
//        cfg.GPIO_PuPd = GPIO_PuPd_NOPULL;
//        relay.init(&cfg);
//
//        AD9959_Set_Amp(AD9959_CH0, 307);
//        AD9959_Set_Amp(AD9959_CH2, 479);
//        AD9959_Set_Amp(AD9959_CH3, 479);
//
//        set_lose(lose);
//        set_freq(10e6, 16384 / 8);
//    }
//
//    void set_freq(float freq, uint16_t phase) {
//        AD9959_Set_Fre(AD9959_CH0, freq);
//        AD9959_Set_Fre(AD9959_CH2, freq);
//        AD9959_Set_Fre(AD9959_CH3, freq);
//        AD9959_Set_Phs(AD9959_CH3, phase);
//        AD9959_Update();
//        char buf[60];
//        sprintf(buf, "freq:%4.4fMHz  phase:%d    ", freq / 1e6, phase);
//        lcd.show(100, 100, buf);
//    }
//
//    void set_lose(uint8_t lose) {
//        loser[0].output(lose & (1 << 0));
//        loser[1].output(lose & (1 << 1));
//        loser[2].output(lose & (1 << 2));
//        loser[3].output(lose & (1 << 3));
//        loser[4].output(lose & (1 << 4));
//        loser[5].output(lose & (1 << 5));
//        char buf[60];
//        sprintf(buf, "lose:%2.1fdb   ", (float) lose / 2);
//        lcd.show(100, 130, buf);
//    }

//
//    void set_relay(bool gnd) {
//        relay.output(gnd ? 0 : 1);
//    }
//
//    static void nomalize_process_0(void *d) { ((Test_0 *) d)->nomalize_process_0(); }
//
//    void nomalize_process_0(void) {
//        set_relay(1);
//        // delay 500ms proccess_1
//        setTimeout(nomalize_process_1, this, 500);
//    }
//
//    static void nomalize_process_1(void *d) { ((Test_0 *) d)->nomalize_process_1(); }
//
//    void nomalize_process_1(void) {
//        if (adcx.aready() && adcy.aready()) {
//            adc_offset_x = (float) adcx.read() / 8388.608;
//            adc_offset_y = (float) adcy.read() / 8388.608;
//            set_relay(0);
//            char buf[70];
//            sprintf(buf, "offset x:%f y:%f      ", adc_offset_x, adc_offset_y);
//            lcd.show(100, 160, buf);
//        } else func_mark(nomalize_process_1, this); // continue
//    }
//
//    static void update_lose(void *d) { ((Test_0 *) d)->set_lose(((Test_0 *) d)->lose); }
//
//    static void update_freq(void *d) { ((Test_0 *) d)->set_freq(((Test_0 *) d)->freq, ((Test_0 *) d)->phase); }
//
//    static void keyborad_recv(void *obj, char ch) { ((Test_0 *) obj)->keyborad_recv(ch); }
//
//    void keyborad_recv(char ch) {
//        RANG_CHECK(1, freq, 1e6, 1e6, 40e6);
//        RANG_CHECK(2, lose, 1, 0, 64);
//        RANG_CHECK(3, phase, 5, 0, 16384);
//        func_mark(update_lose, this);
//        func_mark(update_freq, this);
//        if (ch == KEY_A)
//            func_mark(nomalize_process_0, this);
//    }
//
//
//    float tmpx[10];
//    float tmpy[10];
//    uint8_t tmp_c = 0;
//
//    void update_screem(void) {
//        char buf[120];
//        if (adcx.aready() && adcy.aready()) {
//
////            tmpx[tmp_c] = (float) adcx.read() / 8388.608;
////            tmpy[tmp_c] = (float) adcy.read() / 8388.608;
////            tmp_c = ++tmp_c % 10;
//            float x = (float) adcx.read() / 8388.608;
//            float y = (float) adcy.read() / 8388.608;
//
////            float x = 0, y = 0;
////            for (uint16_t t = 0; t < 10; t++) {
////                x += tmpx[t];
////                y += tmpy[t];
////            }
////            x /= 10;
////            y /= 10;
//
//            sprintf(buf, "adc %4.4f - %4.4f  = %4.4f    ",
//                    x, adc_offset_x, x - adc_offset_x);
//            lcd.show(100, 190, buf);
//            sprintf(buf, "adc %4.4f - %4.4f  = %4.4f    ",
//                    y, adc_offset_y, y - adc_offset_y);
//            lcd.show(100, 220, buf);
//            sprintf(buf, "adc -> %4.4f    ",
//                    sqrt((x - adc_offset_x) * (x - adc_offset_x) +
//                         (y - adc_offset_y) * (y - adc_offset_y))
//            );
//            lcd.show(100, 250, buf);
//        }
//    }
//};
//
//
//class Internet {
//private:
//    usart io;
//    gpio cmd;
//
//    void *recv_obj;
//
//    void (*recv_func)(void *, char ch) = NULL;
//
//
//    static void hard_recv(void *t, char ch) { ((Internet *) t)->hard_recv(ch); }
//
//    void hard_recv(char ch) {
//        if (cmd.read() && recv_func)
//            recv_func(recv_obj, ch);
//    }
//
//public:
//    Internet(usart io, gpio cmd) : io(io), cmd(cmd) {
//        cmd.init_input();
//        io.recv(hard_recv, this);
//    }
//
//    static void send(void *t, char ch) { ((Internet *) t)->send(ch); }
//
//    void send(char ch) { io.send(ch); }
//
//    void send(char *dat, uint16_t len) {
//        for (uint16_t t = 0; t < len; t++)
//            io.send(dat[t]);
//    }
//
//    void send(char *str) {
//        for (uint16_t t = 0; str[t]; t++)
//            send(str[t]);
//    }
//
//    void recv(void(*func)(void *, char), void *dat) {
//        recv_func = func;
//        recv_obj = dat;
//    }
//};
//
//
//class Test_1 {
//
//    enum {
//        KEY_0, KEY_1, KEY_2, KEY_3, KEY_4,
//        KEY_5, KEY_6, KEY_7, KEY_8, KEY_9,
//        KEY_DOT, KEY_NEWLINE,
//        KEY_A, KEY_B, KEY_C, KEY_D,
//        KEY_S1, KEY_S1U, KEY_S1D,
//        KEY_S2, KEY_S2U, KEY_S2D,
//        KEY_S3, KEY_S3U, KEY_S3D,
//    };
//
//private:
//    Lcd lcd;
//    usart io;
//    double freq = 1e6;
//    uint32_t amp = 250;
//    Internet internet;
//    adc adc_dev;
//    uint16_t adc_val[100];
//    uint16_t cursor = 0;
//public:
//    Test_1(Lcd lcd, usart io, Internet internet)
//            : lcd(lcd), io(io), internet(internet), adc_dev(adc(1)) {
//        adc_dev.open(1);
//        AD9959_Init();
//        io.recv(keyborad_recv, this);
//        update();
//    }
//
//    bool running = false;
//
//    static void execult(void *t) { ((Test_1 *) t)->execult(); }
//
//    void execult(void) {
//        if (running) {
//            if (freq >= 100e6) {
//                freq = 1e6;
//                cursor = 0;
//
//                char buf[50];
//                sprintf(buf, "{\"min\":%d,\"max\":%d,\"val\":[");
//                internet.send(buf);
//                for (uint16_t t = 0; t < 100; t++) {
//                    sprintf(buf, "%d,", adc_val[t]);
//                    internet.send(buf);
//                }
//                sprintf(buf, "]}\n");
//                internet.send(buf);
//            } else {
//                freq = freq + 1e6;
//                cursor++;
//                adc_val[cursor] = adc_dev.convert(1);
//            }
//
//            update();
//        }
//    }
//
//
//    static void update(void *t) { ((Test_1 *) t)->update(); }
//
//    void update(void) {
//        AD9959_Set_Fre(AD9959_CH2, freq);
//        AD9959_Set_Amp(AD9959_CH2, amp);
//        AD9959_Set_Fre(AD9959_CH3, freq);
//        AD9959_Set_Amp(AD9959_CH3, amp);
//        AD9959_Update();
//        char buf[50];
//        sprintf(buf, "freq:%3.3fMHz amp:%3.3f%%        ", freq / 1e6, (float) amp / 2048);
//        lcd.show(100, 100, buf);
//    }
//
//    static void keyborad_recv(void *t, char ch) { ((Test_1 *) t)->keyborad_recv(ch); }
//
//    void keyborad_recv(char ch) {
//        RANG_CHECK(1, freq, 10e3, 10e3, 100e6);
//        RANG_CHECK(2, amp, 5, 0, 2048);
//        if (ch == KEY_A) running = running ? false : true;
//        func_mark(update, this);
//    }
//
//};
//
//#define COMPUTE_FREQ_1(cur, min, max, step)  (min +  (max - min) * cur / step)
//
//class Test_2 {
//    enum {
//        KEY_0, KEY_1, KEY_2, KEY_3, KEY_4,
//        KEY_5, KEY_6, KEY_7, KEY_8, KEY_9,
//        KEY_DOT, KEY_NEWLINE,
//        KEY_A, KEY_B, KEY_C, KEY_D,
//        KEY_S1, KEY_S1U, KEY_S1D,
//        KEY_S2, KEY_S2U, KEY_S2D,
//        KEY_S3, KEY_S3U, KEY_S3D,
//    };
//private:
//    Lcd lcd;
//    usart io;
//    Internet net;
//    LTC2440 adcx;
//
//    double freq_min = 1e6;
//    double freq_max = 40e6;
//    uint16_t amp = 250;
//
//    int32_t *offset = NULL;
//    int32_t *value = NULL;
//    uint16_t p_num = 100;
//    uint16_t cursor = 0;
//public:
//    Test_2(Lcd lcd, usart io)
//            : lcd(lcd), io(io), net(Internet(usart(2, 460800), gpio('H', 2))), shtim(time(3)),
//              dac(gpio('B', 13), gpio('B', 14), gpio('D', 2), gpio('D', 3)),
//              adcx(LTC2440(gpio('H', 12), gpio('H', 13), gpio('H', 14), gpio('H', 15))) {
//        gpio('G', 11).output(1);
//        AD9959_Init();
//        set_point_num(100);
//        lcd.font_family = (char *) font_default_8x6;
//        lcd.font_x_size = 6;
//        lcd.font_y_size = 8;
//        io.recv(keyborad_recv, this);
//        net.recv(internet_recv, this);
//        update_dds(10e6, amp);
//    }
//
//    /////////////////////////////////////// function ////////////////////////////////////////
//
//    void set_point_num(uint16_t n) {
//        p_num = n;
//        offset = (int32_t *) realloc(offset, n * sizeof(int32_t));
//        value = (int32_t *) realloc(value, n * sizeof(int32_t));
//    }
//
//    void update_dds(double freq, uint16_t amp) {
//        AD9959_Set_Fre(AD9959_CH2, freq);
//        AD9959_Set_Amp(AD9959_CH2, amp);
//        AD9959_Set_Fre(AD9959_CH3, freq);
//        AD9959_Set_Amp(AD9959_CH3, amp);
//        AD9959_Update();
//        char buf[50];
//        sprintf(buf, "freq:%3.3fMHz amp:%3.2f%%    ", freq / 1e6, (float) amp / 2048);
//        lcd.show(0, 0, buf);
//    }
//
//
//    void show_wave(float *dat, uint16_t len) {
//        // x (0,1)
//#define COOD_X(x) (600*(x) + 20)
//        // y (-1,1)
//#define COOD_Y(y) (260 - 200*(y))
//
//        lcd.color = 0;
//        lcd.rect(COOD_X(0), COOD_Y(1), COOD_X(1), COOD_Y(-1));
//
//        lcd.color = 0xffff;
//        lcd.line(COOD_X(0), COOD_Y(1), COOD_X(1), COOD_Y(1));
//        lcd.line(COOD_X(0), COOD_Y(0), COOD_X(1), COOD_Y(0));
//        lcd.line(COOD_X(0), COOD_Y(-1), COOD_X(1), COOD_Y(-1));
//        lcd.line(COOD_X(0), COOD_Y(1), COOD_X(0), COOD_Y(-1));
//        lcd.line(COOD_X(1), COOD_Y(1), COOD_X(1), COOD_Y(-1));
//
//        if (dat)
//            for (uint16_t t = 0; t < len - 1; t++)
//                lcd.line((uint16_t) COOD_X((float) t / len),
//                         (uint16_t) COOD_Y(dat[t]),
//                         (uint16_t) COOD_X((float) (t + 1) / len),
//                         (uint16_t) COOD_Y(dat[t + 1]));
//
//    }
//
//
//    /////////////////////////////////////// thread /////////////////////////////////////////
//
//    static void nomalize_process(void *t) { ((Test_2 *) t)->nomalize_process_0(); }
//
//    void nomalize_process_0(void) {
//        cursor = 0;
//        for (uint16_t t = 0; t < p_num; t++)
//            offset[t] = 0;
//        update_dds(COMPUTE_FREQ_1(0, freq_min, freq_max, p_num), amp);
//        setTimeout(nomalize_process_1, this, 1);
//    }
//
//    static void nomalize_process_1(void *t) { ((Test_2 *) t)->nomalize_process_1(); }
//
//    void nomalize_process_1(void) {
//        if (cursor < p_num) {
//            if (adcx.aready()) {
////                offset[cursor] = adcx.read();
//                printf("{%d,%d},\n", COMPUTE_FREQ_1(cursor, freq_min, freq_max, p_num), adcx.read());
//                cursor++;
//                update_dds(COMPUTE_FREQ_1(cursor, freq_min, freq_max, p_num), amp);
//            }
//            setTimeout(nomalize_process_1, this, 1);
//        } else {
//            // show in screem
//        }
//    }
//
//    static void scan_process(void *t) { ((Test_2 *) t)->scan_process_0(); }
//
//    void scan_process_0(void) {
//        cursor = 0;
//        update_dds(COMPUTE_FREQ_1(0, freq_min, freq_max, p_num), amp);
//        setInterval(scan_process_1, this, 10);
//    }
//
//    static void scan_process_1(void *t) { ((Test_2 *) t)->scan_process_1(); }
//
//    void scan_process_1(void) {
//        if (cursor < p_num) {
//            if (adcx.aready()) {
//                value[cursor] = adcx.read();
////                printf("adc:%d - %d = %d\n", value[cursor], offset[cursor], value[cursor] - offset[cursor]);
//                value[cursor] -= offset[cursor];
//                cursor++;
//                update_dds(COMPUTE_FREQ_1(cursor, freq_min, freq_max, p_num), amp);
//            }
//        } else {
//            float dat[500];
//            for (uint16_t t = 0; t < p_num; t++)
//                dat[t] = value[t] / (40 * 76774.2);
//            show_wave(dat, p_num);
//            cursor = 0;
//        }
//    }
//
////    bool running = false;
////
////    static void update(void *t) { ((Test_2 *) t)->update(); }
////
////    void update(void) {
////        if (running) scan_process_1();
////    }
//
//    time shtim;
//    AD5663 dac;
//
//    void dac_out(float x, float y) {
//        dac.output(0, 65536 * x);
//        dac.output(1, 32768 + 32768 * y);
//    }
//
//    static void shower_process(void *t) { ((Test_2 *) t)->shower_process_0(); }
//
//    void shower_process_0(void) {
//        for (uint16_t t = 0; t < p_num; t++) {
//            dac_out((float) t / p_num, value[t] / (40 * 76774.2));
//            delay_us(5);
//        }
//        dac_out(0, 0);
//        for (uint16_t t = 0; t < p_num * 4; t++) {
//            dac_out((float) t / (p_num * 4), 0);
//        }
//        dac_out(0, 1);
//        for (uint16_t t = 0; t < (p_num * 4); t++) {
//            dac_out((float) t / (p_num * 4), 1);
//        }
//        dac_out(0, -1);
//        for (uint16_t t = 0; t < (p_num * 4); t++) {
//            dac_out((float) t / (p_num * 4), -1);
//        }
//        func_mark(shower_process, this);
//    }
//
//    //////////////////////////////////////  event ////////////////////////////////////////
//    static void keyborad_recv(void *t, char ch) { ((Test_2 *) t)->keyborad_recv(ch); }
//
//    void keyborad_recv(char ch) {
////        RANG_CHECK(1, freq, 10e3, 10e3, 100e6);
//        RANG_CHECK(1, amp, 5, 0, 2048);
//        update_dds(0, amp);
////        if (ch == KEY_A) running = running ? false : true;
////        func_mark(update, this);
//        if (ch == KEY_A) func_mark(nomalize_process, this);
////        if (ch == KEY_B) running = running ? false : true;
//        if (ch == KEY_B) func_mark(scan_process, this);
//        if (ch == KEY_C) func_mark(shower_process, this);
//        if (ch == KEY_D) net_cur = 0;
//    }
//
//
//    char net_buf[1000];
//    uint16_t net_cur = 0;
//
//    static void internet_recv(void *t, char ch) { ((Test_2 *) t)->internet_recv(ch); }
//
//#define CHECK_NET_BUF(a, b, c, d) (a==net_buf[0])&&(b==net_buf[1])&&(c==net_buf[2])&&(d==net_buf[3])
//
//    void internet_recv(char ch) {
//        net.send(ch);
//        net_buf[net_cur++] = ch;
//        if (net_cur >= 4) {
//            if (CHECK_NET_BUF(0xaa, 0x55, 0xaa, 0x55)) {
//                net_cur = 0;
//                func_mark(nomalize_process, this);
//            }
//        }
//    }
//
//};
//
//
//void internet_recv(void *io, char ch) {
//    ((usart *) io)->send(ch);
//}
//
//
//void shower_change(void *d) {
//    AD5663 *dac = (AD5663 *) d;
//
//    static uint16_t t = 0;
//
//    dac->output(0, 3200 + 3000 * sin(0.01 * t));
//    dac->output(1, 3200 + 3000 * cos(0.01 * t));
//
//    t++;
//}
//
//void set_freq(double_t freq) {
//
//    AD9959_Set_Fre(AD9959_CH2, freq);
//    AD9959_Set_Fre(AD9959_CH3, freq);
//
//    AD9959_Update();
//}
//
//int main(void) {
//    usart io = usart(1, 9600);
//    os_init(2, 'F', 10);
//    set_print_dev(&io);
//    func_init();
////    Recv_test gain_test = Recv_test(io);
////    setInterval(Recv_test::update, &gain_test, 20);
//
//    LCD_DEV lcd_dev = LCD_DEV();
//    Lcd lcd = Lcd(&lcd_dev);
//
//
//
////    Contest contest = Contest(lcd, io);
//
////    Test_0 test0 = Test_0(lcd, io);
////    Test_1 test1 = Test_1(lcd, io, Internet(usart(2, 460800), gpio('H', 2)));
////    setInterval(Test_1::execult, &test1, 10);
//
////    Internet net = Internet(usart(2, 460800), gpio('H', 2));
////    net.recv(usart::send, &io);
//
////    Test_2 test2 = Test_2(lcd, io);
////    setInterval(Test_2::update, &test2, 10);
//    AD9959_Init();
//
//    AD9959_Set_Amp(AD9959_CH2, 250);
//    AD9959_Set_Amp(AD9959_CH3, 250);
//
//    set_freq(10e3);
//
//    LTC2440 adcx = LTC2440(gpio('H', 12), gpio('H', 13), gpio('H', 14), gpio('H', 15));
//
//    os_stop();
//    for (uint32_t freq = 10e3; freq <= 100e6; freq += 50e3) {
//        while (!adcx.aready());
//        printf("{%d,%d},\n", freq, adcx.read());
//    }
//    os_start();
//
//    while (true) {
//        while (!os_execult());
////        func_check();
////        test0.update_screem();
//    }
//}
//
//
//
//
//
//
//
//
//
//
////class RemoteExecult {
////private:
////    char buf[1000];
////
////    uint16_t cur = 0;
////
////    uint16_t len = 0;
////
////    uint8_t get_L(char ch) { return ch >> 4; }
////
////    uint8_t get_H(char ch) { return ch & 0xf; }
////
////    char mix(uint8_t H, uint8_t L) { return ((H & 0xf) << 4) | (0xf & L); }
////
////public:
////
////    void recivie_char(char ch) {
////        buf[cur] = ch;
////        if (get_H(ch) > 10) {  // not allow
////            cur = 0;
////            return;
////        }
////        if (get_H(ch) == 9) {
////            if (cur != 9) {    // not allow
////                cur = 0;
////                return;
////            } else {
////                cur++;
////                if (cur == 8 + 2 * len) {
////                    exec();
////                    cur = 0;
////                }
////                return;
////            }
////        }
////        if (get_H(ch) != cur) { // not allow
////            cur = 0;
////            return;
////        } else {
////            cur++;
////            if (cur == 4) {
////                uint8_t a = get_L(buf[0]),
////                        b = get_L(buf[1]),
////                        c = get_L(buf[2]),
////                        d = get_L(buf[3]);
////                len = (a << 12) | (b << 8) | (c << 4) | d;
////                if (len == 0)
////                    exec();
////            }
////            return;
////        }
////    }
////
////    uint16_t get_u16(uint8_t a, uint8_t b, uint8_t c, uint8_t d) {
////        return (a << 12) | (b << 8) | (c << 4) | d;
////    }
////
////    void convert(char *src, char *dec, uint16_t len) {
////        for (uint16_t t = 0; t < len; t++) {
////            dec[t] = mix(src[t], src[t + 1]);
////        }
////    }
////
////    void exec(void) {
////        uint16_t cmd = get_u16(buf[4], buf[5], buf[6], buf[7]);
////        convert((buf + 8), buf, len);
////    }
////
////    virtual void execult(uint16_t cmd, void *dat, uint16_t len) {}
////
////    void send(uint16_t cmd, void *dat, uint16_t len) {
////        char *buf = (char *) dat;
////        uint8_t a, b, c, d;
////        a = get_H(cmd / 256);
////        b = get_L(cmd / 256);
////        c = get_H(cmd % 256);
////        d = get_L(cmd % 256);
////
////        recivie_char(mix(0, a));
////        recivie_char(mix(1, b));
////        recivie_char(mix(2, c));
////        recivie_char(mix(3, d));
////
////
////        a = get_H(len / 256);
////        b = get_L(len / 256);
////        c = get_H(len % 256);
////        d = get_L(len % 256);
////
////        recivie_char(mix(4, a));
////        recivie_char(mix(5, b));
////        recivie_char(mix(6, c));
////        recivie_char(mix(7, d));
////
////        while (len--) {
////            recivie_char(mix(9, get_H(buf[len])));
////            recivie_char(mix(9, get_L(buf[len])));
////        }
////    }
////};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "device.hpp"
#include "os.h"
#include <LTC2440.h>
#include <AD5663.h>
#include <cstdio>
#include "syscall.hpp"
#include "lcd.h"
#include "base64.h"
#include "ad9959fuc.h"


#define EXEC_POOL_SIZE 30

struct {
    bool flag = false;
    void *dat;

    void (*func)(void *);
} exec_pool[EXEC_POOL_SIZE] = {};

void func_init(void) {
    uint8_t t = EXEC_POOL_SIZE;
    while (t--)exec_pool[t].flag = false;
}

void func_mark(void (*func)(void *), void *dat) {
    for (uint16_t t = 0; t < EXEC_POOL_SIZE; t++) {
        if (!exec_pool[t].flag) {
            exec_pool[t].flag = true;
            exec_pool[t].dat = dat;
            exec_pool[t].func = func;
            return;
        }
    }
}

void func_check(void) {
    for (uint16_t t = 0; t < EXEC_POOL_SIZE; t++)
        if (exec_pool[t].flag) {
            exec_pool[t].flag = false;
            exec_pool[t].func(exec_pool[t].dat);
        }
}

using namespace dev;

#define RANG_CHECK(key, var, step, l, h) \
    if (ch == KEY_S##key##U) var = ( var + step < h ) ? var + step : h - 1;\
    if (ch == KEY_S##key##D) var = ( var - step >= l ) ? var - step : l;

#define COMPUTE_FREQ(i, min, max, step) ((float)min + (float)i * (float)(max - min)/(float)step)
static const float lose_db_to_mv_table[] = {
        0, 0, 0, 0, 0, 100, 97.6, 93.6, 89.1072, 84.6144, 80.8704,
        76.752, 70.2, 66.6432, 62.8992, 60.2784, 58.7808, 56.16,
        52.7904, 50.8248, 46.4256, 44.1792, 41.9328, 39.6864,
        37.44, 35.568, 33.3216, 31.824, 29.2032, 28.08, 26.5824,
        25.4592, 25.272, 24.336, 23.2128, 22.0896, 20.2176,
        19.188, 18.3456, 16.848, 14.04, 13.1976, 12.4488,
        11.8872, 10.764, 10.296, 9.9216, 9.36, 9.0792,
        8.6112, 8.2368, 7.8624, 7.2072, 6.9264, 6.6456,
        6.3648, 5.9904, 5.616, 5.4288, 5.0544, 4.68, 4.4928,
};

const static int32_t inside_shower_offset[] = {
        1243874 ,// 0
        1651191 ,// 1
        2145951 ,// 2
        2159605 ,// 3
        2161606 ,// 4
        2159128 ,// 5
        2152983 ,// 6
        2150475 ,// 7
        2144585 ,// 8
        2136154 ,// 9
        2127998 ,// 10
        2122864 ,// 11
        2115652 ,// 12
        2107081 ,// 13
        2104695 ,// 14
        2098991 ,// 15
        2089037 ,// 16
        2075713 ,// 17
        2046008 ,// 18
        2033992 ,// 19
        2023037 ,// 20
        2010249 ,// 21
        1994863 ,// 22
        1986041 ,// 23
        1977374 ,// 24
        1967692 ,// 25
        1966331 ,// 26
        1951676 ,// 27
        1943939 ,// 28
        1934847 ,// 29
        1918361 ,// 30
        1911034 ,// 31
        1901985 ,// 32
        1891308 ,// 33
        1891944 ,// 34
        1887521 ,// 35
        1881281 ,// 36
        1873716 ,// 37
        1866704 ,// 38
        1863200 ,// 39
        1857607 ,// 40
        1849988 ,// 41
        1842187 ,// 42
        1838020 ,// 43
        1833551 ,// 44
        1827085 ,// 45
        1824369 ,// 46
        1820944 ,// 47
        1816988 ,// 48
        1822958 ,// 49
        1820707 ,// 50
        1818021 ,// 51
        1814835 ,// 52
        1804892 ,// 53
        1802161 ,// 54
        1798619 ,// 55
        1795530 ,// 56
        1783665 ,// 57
        1780760 ,// 58
        1778775 ,// 59
        1776549 ,// 60
        1801556 ,// 61
        1800531 ,// 62
        1800644 ,// 63
        1798972 ,// 64
        1799742 ,// 65
        1798528 ,// 66
        1796510 ,// 67
        1792037 ,// 68
        1778778 ,// 69
        1774640 ,// 70
        1770916 ,// 71
        1766706 ,// 72
        1587442 ,// 73
        1371734 ,// 74
        1075600 ,// 75
        962588 ,// 76
        1430406 ,// 77
        1439527 ,// 78
        1443611 ,// 79
        1440791 ,// 80
        1463181 ,// 81
        1475226 ,// 82
        1489272 ,// 83
        1505907 ,// 84
        1647779 ,// 85
        1654642 ,// 86
        1658580 ,// 87
        1660406 ,// 88
        1684445 ,// 89
        1683681 ,// 90
        1682138 ,// 91
        1680292 ,// 92
        1689347 ,// 93
        1690109 ,// 94
        1689803 ,// 95
        1688566 ,// 96
        1690399 ,// 97
        1689313 ,// 98
        1686805 ,// 99
        1683135 ,// 100
        1680461 ,// 101
        1680089 ,// 102
        1678440 ,// 103
        1675963 ,// 104
        1676603 ,// 105
        1676034 ,// 106
        1673672 ,// 107
        1670945 ,// 108
        1669292 ,// 109
        1664093 ,// 110
        1660620 ,// 111
        1657433 ,// 112
        1648985 ,// 113
        1648184 ,// 114
        1644490 ,// 115
        1640842 ,// 116
        1627233 ,// 117
        1624229 ,// 118
        1618580 ,// 119
        1613408 ,// 120
        1611437 ,// 121
        1609318 ,// 122
        1605711 ,// 123
        1588572 ,// 124
        1584649 ,// 125
        1579034 ,// 126
        1571643 ,// 127
        1474148 ,// 128
        1433729 ,// 129
        1375175 ,// 130
        1344767 ,// 131
        1405308 ,// 132
        1416250 ,// 133
        1423046 ,// 134
        1428814 ,// 135
        1399299 ,// 136
        1391954 ,// 137
        1382211 ,// 138
        1373516 ,// 139
        1360058 ,// 140
        1364380 ,// 141
        1364810 ,// 142
        1365081 ,// 143
        1388777 ,// 144
        1389779 ,// 145
        1387123 ,// 146
        1383639 ,// 147
        1386859 ,// 148
        1387384 ,// 149
        1384755 ,// 150
        1382684 ,// 151
        1384292 ,// 152
        1386158 ,// 153
        1384089 ,// 154
        1384408 ,// 155
        1390580 ,// 156
        1394313 ,// 157
        1393575 ,// 158
        1394399 ,// 159
        1410520 ,// 160
        1414547 ,// 161
        1414033 ,// 162
        1413498 ,// 163
        1415177 ,// 164
        1416504 ,// 165
        1414649 ,// 166
        1413972 ,// 167
        1411980 ,// 168
        1407139 ,// 169
        1403931 ,// 170
        1393525 ,// 171
        1393368 ,// 172
        1390531 ,// 173
        1388635 ,// 174
        1380447 ,// 175
        1379644 ,// 176
        1376088 ,// 177
        1374091 ,// 178
        1366151 ,// 179
        1364915 ,// 180
        1360999 ,// 181
        1358562 ,// 182
        1340951 ,// 183
        1335968 ,// 184
        1325913 ,// 185
        1317724 ,// 186
        1304802 ,// 187
        1298974 ,// 188
        1294828 ,// 189
        1287491 ,// 190
        1300421 ,// 191
        1297679 ,// 192
        1292606 ,// 193
        1289206 ,// 194
        1287651 ,// 195
        1283821 ,// 196
        1277925 ,// 197
        1271929 ,// 198
        1249878 ,// 199
};

const static int32_t wired_shower_offset [] = {
        1308517 ,// 0
        1686729 ,// 1
        2044879 ,// 2
        2075149 ,// 3
        2040903 ,// 4
        1995311 ,// 5
        1953592 ,// 6
        1917888 ,// 7
        1885603 ,// 8
        1858454 ,// 9
        1836107 ,// 10
        1817334 ,// 11
        1801367 ,// 12
        1787518 ,// 13
        1770015 ,// 14
        1754265 ,// 15
        1742000 ,// 16
        1729170 ,// 17
        1716002 ,// 18
        1702573 ,// 19
        1689531 ,// 20
        1677363 ,// 21
        1664322 ,// 22
        1650892 ,// 23
        1636936 ,// 24
        1621224 ,// 25
        1606442 ,// 26
        1591402 ,// 27
        1572809 ,// 28
        1552738 ,// 29
        1530116 ,// 30
        1507341 ,// 31
        1487263 ,// 32
        1467870 ,// 33
        1449369 ,// 34
        1433401 ,// 35
        1414804 ,// 36
        1393744 ,// 37
        1371262 ,// 38
        1344625 ,// 39
};

const static int32_t wifi_offset_table[] = {
        1464618 ,// 0
        1780515 ,// 1
        2086800 ,// 2
        2145741 ,// 3
        2157685 ,// 4
        2158671 ,// 5
        2157600 ,// 6
        2158475 ,// 7
        2156598 ,// 8
        2152497 ,// 9
        2150256 ,// 10
        2146461 ,// 11
        2144250 ,// 12
        2142103 ,// 13
        2138656 ,// 14
        2135756 ,// 15
        2132609 ,// 16
        2128229 ,// 17
        2125987 ,// 18
        2122586 ,// 19
        2118997 ,// 20
        2116290 ,// 21
        2112226 ,// 22
        2107885 ,// 23
        2104695 ,// 24
        2100100 ,// 25
        2096784 ,// 26
        2093039 ,// 27
        2087949 ,// 28
        2084670 ,// 29
        2079327 ,// 30
        2075439 ,// 31
        2071289 ,// 32
        2066877 ,// 33
        2059897 ,// 34
        2053025 ,// 35
        2045923 ,// 36
        2041140 ,// 37
        2036680 ,// 38
        2030691 ,// 39
        2026337 ,// 40
        2020696 ,// 41
        2013979 ,// 42
        2008649 ,// 43
        2001649 ,// 44
        1992588 ,// 45
        1986017 ,// 46
        1979359 ,// 47
        1973620 ,// 48
        1968113 ,// 49
        1960289 ,// 50
        1953140 ,// 51
        1946301 ,// 52
        1936945 ,// 53
        1931020 ,// 54
        1924201 ,// 55
        1915832 ,// 56
        1908307 ,// 57
        1900401 ,// 58
        1891203 ,// 59
        1883386 ,// 60
        1874930 ,// 61
        1866154 ,// 62
        1858159 ,// 63
        1848057 ,// 64
        1838370 ,// 65
        1829859 ,// 66
        1819710 ,// 67
        1810914 ,// 68
        1801828 ,// 69
        1791735 ,// 70
        1782253 ,// 71
        1771701 ,// 72
        1761198 ,// 73
        1752024 ,// 74
        1741215 ,// 75
        1730234 ,// 76
        1721456 ,// 77
        1710346 ,// 78
        1699643 ,// 79
        1688862 ,// 80
        1677618 ,// 81
        1667130 ,// 82
        1656952 ,// 83
        1645699 ,// 84
        1634861 ,// 85
        1623295 ,// 86
        1611676 ,// 87
        1600508 ,// 88
        1589772 ,// 89
        1579320 ,// 90
        1568617 ,// 91
        1556726 ,// 92
        1545438 ,// 93
        1533496 ,// 94
        1521577 ,// 95
        1510488 ,// 96
        1499539 ,// 97
        1488034 ,// 98
        1476612 ,// 99
};

//class RemoteCmd {
//private:
//    char buf[10000];
//    uint32_t cur = 0;
//
//public:
//    typedef struct Head {
//        uint32_t a;
//        uint32_t b;
//        uint32_t c;
//        uint32_t d;
//    } Head;
//
//    static void recv_char(void *t, char ch) { ((RemoteCmd *) t)->recv_char(ch); }
//
//    void recv_char(char ch) {
//        buf[cur++] = ch;
//        if (ch == 0) {
//            char conv[10000];
//            base64_decode(buf, cur, (unsigned char *) conv);
//            local_execult(
//                    (Head *) conv, (uint8_t *) (conv + 4 * sizeof(uint32_t)),
//                    (uint16_t) (BASE64_DECODE_OUT_SIZE(cur) - 4 * sizeof(uint32_t)));
//        }
//    }
//
//    void remote_execult(Head *head, uint8_t *body, uint16_t len) {
//        uint8_t raw[1000];
//        uint8_t pack[10000];
//        uint8_t *headp = (uint8_t *) head;
//        uint16_t raw_len = len + 4 * sizeof(uint32_t);
//        uint16_t t = 0;
//        for (t = 0; t < raw_len; t++) {
//            if (t < 4 * sizeof(uint32_t))
//                raw[t] = headp[t];
//            else
//                raw[t] = body[t - 4 * sizeof(uint32_t)];
//        }
//        base64_encode(raw, raw_len, (char *) pack);
//        for (t = 0; t < BASE64_ENCODE_OUT_SIZE(raw_len); t++) recv_char(pack[t]);
//        recv_char(0);
//    }
//
//    void local_execult(Head *head, uint8_t *body, uint16_t len) {
//        printf("head:%x %x %x %x;body(%d):%s\n", head->a, head->b, head->c, head->d,
//               len, body);
//    }
//};


class ContestFinal {
    enum {
        KEY_0, KEY_1, KEY_2, KEY_3, KEY_4,
        KEY_5, KEY_6, KEY_7, KEY_8, KEY_9,
        KEY_DOT, KEY_NEWLINE,
        KEY_A, KEY_B, KEY_C, KEY_D,
        KEY_S1, KEY_S1U, KEY_S1D,
        KEY_S2, KEY_S2U, KEY_S2D,
        KEY_S3, KEY_S3U, KEY_S3D,
    };

    enum {
        STATE_WAITTING,
        STATE_SIGNAL_GENERATOR, // signal_generator
        STATE_SHOWER_INSIDE,    // shower_inside
        STATE_SHOWER_REMOTE,    // shower_remote
    };
private:
    Lcd lcd;
    usart remote;
    gpio remote_cmd;
    usart keyborad;
    LTC2440 adcx;
    AD5663 dac;
    uint8_t func_state = STATE_WAITTING;
public:
    ContestFinal(Lcd lcd, usart keyborad)
            : lcd(lcd), keyborad(keyborad), remote(usart(3, 9600)), remote_cmd(gpio('H', 2)),
              dac(AD5663(gpio('B', 13), gpio('B', 14), gpio('D', 2), gpio('D', 3))),
              adcx(LTC2440(gpio('H', 12), gpio('H', 13), gpio('H', 14), gpio('H', 15))),
              loser({gpio('I', 0), gpio('I', 1), gpio('I', 2), gpio('I', 3), gpio('I', 4), gpio('I', 5)}) {
        gpio('G', 11).output(1);
        keyborad.recv(keyborad_recv, this);
        AD9959_Init();
    }

    void loop(void) {

        while (func_state == STATE_WAITTING) {
            while (!os_execult());
        }

        if (func_state == STATE_SIGNAL_GENERATOR) signal_generator();
        if (func_state == STATE_SHOWER_INSIDE) shower_inside();
        if (func_state == STATE_SHOWER_REMOTE) shower_remote();

        while (true) {
            while (!os_execult());
            if (func_state == STATE_SHOWER_INSIDE) shower_inside_exec();
            if (func_state == STATE_SHOWER_REMOTE) shower_remote_exec();
        }
    }
///////////////////////////////////////      functions       ////////////////////////////////

    uint32_t freq_min = (uint32_t) 100e3;
    uint32_t freq_max = (uint32_t) 100e6;
    uint32_t amp = 97;
    uint32_t freq = (uint32_t) 10e6;
    uint16_t p_num = 100;
    int32_t *value = NULL;
    int32_t *offset = NULL;

    void dds_output_update(void) {
        AD9959_Set_Fre(AD9959_CH2, freq);
        AD9959_Set_Amp(AD9959_CH2, (u16) amp);
        AD9959_Update();
    }

    void set_point_num(uint16_t n) {
        p_num = n;
        value = (int32_t *) realloc(value, n * sizeof(int32_t));
        offset = (int32_t *) realloc(offset, n * sizeof(int32_t));
        for (uint16_t t = 0; t < n; t++) offset[t] = 0;
    }

    void dac_set(float x, float y) {
        dac.output(0, (uint16_t) (65535 * x));
        dac.output(1, (uint16_t) (65535 * y));
    }

    float adc_to_db(int32_t val) { return (float) val / 76774.2f; }

//////////////////////////////////////    signal_generator   /////////////////////////////////

    uint8_t lose = 63;
    gpio loser[6];

    void signal_generator(void) {
        dds_output_update();
        signal_generator_lose_update();
    }

    void signal_generator_lose_update(void) {
        for (uint8_t t = 0; t < 6; t++)
            loser[t].output((lose & (1 << t)) ? true : false);
    }

    void signal_generator_key(char ch) {
        RANG_CHECK(1, freq, 1e6, 1e6, 40e6)
        RANG_CHECK(2, amp, 1, 0, 2048)
        RANG_CHECK(3, lose, 1, 0, 64)
        dds_output_update();
        signal_generator_lose_update();
        char buf[40];
        sprintf(buf, "freq:%3.4fMHz amp:%d;lose:%d   ", (float) freq / 1e6, amp, lose);
        lcd.show(100, 100, buf);
    }

////////////////////////////////////////      inside_shower   /////////////////////////////////////
    uint32_t shower_inside_cur = 0;

    static void shower_inside_scan(void *t) { ((ContestFinal *) t)->shower_inside_scan(); }

    void shower_inside_scan(void) {
        value[shower_inside_cur++] = adcx.read();
        freq = (uint32_t) COMPUTE_FREQ(shower_inside_cur, freq_min, freq_max, p_num);
        dds_output_update();
        if (shower_inside_cur >= p_num) shower_inside_cur = 0;
        char buf[40];
        sprintf(buf, "freq:%3.4fMHz   ", (float) freq / 1e6);
        lcd.show(100, 130, buf);
    }

    void shower_inside(void) {
        set_point_num(200);
        freq_min = (uint32_t) 100e3;
        freq_max = (uint32_t) 100e6;
        amp = 250;
        setInterval(shower_inside_scan, this, 5);
        lcd.show(100, 100, "start shower inside");
    }

    void shower_inside_exec(void) {
        for (uint16_t t = 0; t < (p_num); t++)
            dac_set((float) t / (p_num), (adc_to_db(value[t] - offset[t]) + 60) / 120);

        for (uint16_t t = 0; t < 100; t++)
            dac_set((float) t / 100, 0.5);
        for (uint16_t t = 0; t < 100; t++)
            dac_set((float) t / 100, 0);
        for (uint16_t t = 0; t < 100; t++)
            dac_set((float) t / 100, 1);

    }

    void shower_inside_key(char ch) {
        if (ch == KEY_6) {
            for (uint16_t t = 0; t < p_num; t++) {
                offset[t] = value[t];
            }
        }
        if(ch == KEY_4){
            for (uint16_t t = 0; t < p_num; t++) {
                offset[t] = inside_shower_offset[t];
            }
        }
    }

//////////////////////////////////////       shower_remote    //////////////////////////////////

    void shower_remote(void) {
        set_point_num(p_num);
        freq_min = (uint32_t) 100e3;
        freq_max = (uint32_t) 100e6;
        amp = 250;
        lcd.show(100, 100, "start shower remote");
        remote.recv(remote_recv_char, this);
    }

    //  exec in loop  and  save point and send to remote

    void shower_remote_exec(void) {
        func_check();
        value[shower_inside_cur++] = adcx.read();
        freq = (uint32_t) COMPUTE_FREQ(shower_inside_cur, freq_min, freq_max, p_num);
        dds_output_update();
        //   scan  finished
        if (shower_inside_cur >= p_num) {
            shower_inside_cur = 0;
            Head head;
            head.a = 0xff000001;
            head.b = p_num;
            head.c = freq_min;
            head.d = freq_max;
            uint16_t check[1000];
            for (uint32_t t = 0; t < p_num; t++)
                check[t] = (uint16_t) (65536 * ((((double) (value[t] - offset[t]) / 76774.2f) + 60) / 120));
            remote_execult(&head, (uint8_t *) check, p_num * sizeof(uint16_t));
        }
        char buf[40];
        sprintf(buf, "freq:%3.4fMHz   ", (float) freq / 1e6);
        lcd.show(100, 130, buf);
    }

    void shower_remote_key(char ch) {
        if (ch == KEY_6) {
            for (uint16_t t = 0; t < p_num; t++) {
                offset[t] = value[t];
            }
        }
        if(ch == KEY_DOT){
            for (uint16_t t = 0; t < p_num; t++) {
                offset[t] = wifi_offset_table[t];
            }
        }
        if(ch == KEY_1){
            for (uint16_t t = 0; t < p_num; t++) {
                offset[t] = wired_shower_offset[t];
            }
        }
    }
/////////////////////////////////////        remote           //////////////////////////////////


    char remote_recv_buf[10000];
    uint32_t remote_recv_cur = 0;

    typedef struct Head {
        uint32_t a;
        uint32_t b;
        uint32_t c;
        uint32_t d;
    } Head;

    static void remote_recv_char(void *t, char ch) { ((ContestFinal *) t)->remote_recv_char(ch); }

    void remote_recv_char(char ch) {
        remote_recv_buf[remote_recv_cur++] = ch;
        if (ch == 0) {
            char conv[10000];
            base64_decode(remote_recv_buf, remote_recv_cur, (unsigned char *) conv);
            local_execult(
                    (Head *) conv, (uint8_t *) (conv + 4 * sizeof(uint32_t)),
                    (uint16_t) (BASE64_DECODE_OUT_SIZE(remote_recv_cur) - 4 * sizeof(uint32_t)));
        }
    }

    void remote_execult(Head *head, uint8_t *body, uint16_t len) {
        uint8_t raw[1000];
        uint8_t pack[10000];
        uint8_t *headp = (uint8_t *) head;
        uint16_t raw_len = len + 4 * sizeof(uint32_t);
        uint16_t t = 0;
        for (t = 0; t < raw_len; t++) {
            if (t < 4 * sizeof(uint32_t))
                raw[t] = headp[t];
            else
                raw[t] = body[t - 4 * sizeof(uint32_t)];
        }
        base64_encode(raw, raw_len, (char *) pack);
        for (t = 0; t < BASE64_ENCODE_OUT_SIZE(raw_len); t++) remote.send(pack[t]);
        remote.send('\0');
    }


    static void update_remote_freq(void *t) { ((ContestFinal *) t)->update_remote_freq(); }

    void update_remote_freq(void) {
        printf("remote change range success\n");
        freq = new_freq;
        freq_min = new_min;
        freq_max = new_max;
    }

    uint32_t new_freq;
    uint32_t new_min;
    uint32_t new_max;

    void local_execult(Head *head, uint8_t *body, uint16_t len) {
        if (head->a == 0xff000002) {
            for (uint16_t t = 0; t < p_num; t++)
                offset[t] = value[t];
        }
        if (head->a == 0xff000003) {
            new_freq = head->b;
            new_min = head->c;
            new_max = head->d;
            func_mark(update_remote_freq, this);
        }
    }

//////////////////////////////////////       keyborad        ///////////////////////////////////

    static void keyborad_recv(void *obj, char ch) { ((ContestFinal *) obj)->keyborad_recv(ch); }

    void keyborad_recv(char ch) {
        switch (func_state) {
            case STATE_SIGNAL_GENERATOR:
                signal_generator_key(ch);
                break;
            case STATE_SHOWER_INSIDE:
                shower_inside_key(ch);
                break;
            case STATE_SHOWER_REMOTE:
                shower_remote_key(ch);
                break;
            default:
                switch (ch) {
                    case KEY_A:
                        func_state = STATE_SIGNAL_GENERATOR;
                        break;
                    case KEY_B:
                        func_state = STATE_SHOWER_INSIDE;
                        break;
                    case KEY_C:
                        func_state = STATE_SHOWER_REMOTE;
                        p_num = 40;
                        break;
                    case KEY_D:
                        func_state = STATE_SHOWER_REMOTE;
                        remote = usart(3, 460800);
                        p_num = 100;
                    default:
                        break;
                }
        }
    }

/////////////////////////////////////////////////////////////////////////////////////////////////
};


int main(void) {
    usart io = usart(1, 9600);
    os_init(2, 'F', 10);
    set_print_dev(&io);
    func_init();

    LCD_DEV lcd_dev = LCD_DEV();
    Lcd lcd = Lcd(&lcd_dev);

    ContestFinal final = ContestFinal(lcd, io);
    final.loop();
}



