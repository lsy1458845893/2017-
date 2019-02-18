#include "AD5663.h"

#include "same.h"

AD5663::AD5663(GPIO_TypeDef *CLK_PORT, uint16_t CLK_PIN,
               GPIO_TypeDef *DAT_PORT, uint16_t DAT_PIN,
               GPIO_TypeDef *LDAC_PORT, uint16_t LDAC_PIN,
               GPIO_TypeDef *SYNC_PORT, uint16_t SYNC_PIN) :
        CLK_PORT(CLK_PORT), CLK_PIN(CLK_PIN),
        DAT_PORT(DAT_PORT), DAT_PIN(DAT_PIN),
        LDAC_PORT(LDAC_PORT), LDAC_PIN(LDAC_PIN),
        SYNC_PORT(SYNC_PORT), SYNC_PIN(SYNC_PIN) {

    GPIO_INIT_OUT(CLK_PORT, CLK_PIN);
    GPIO_INIT_OUT(DAT_PORT, DAT_PIN);
    GPIO_INIT_OUT(LDAC_PORT, LDAC_PIN);
    GPIO_INIT_OUT(SYNC_PORT, SYNC_PIN);
}

void AD5663::output(uint8_t ch, uint16_t val) {
    u8 i = 0;
    uint32_t set_data;
    GPIO_SetBits(CLK_PORT, CLK_PIN);
    GPIO_SetBits(SYNC_PORT, SYNC_PIN);
    GPIO_ResetBits(SYNC_PORT, SYNC_PIN);
    GPIO_ResetBits(CLK_PORT, CLK_PIN);
    set_data = (uint32_t) (((0 << 19) & 0x00380000) + ((ch << 16) & 0x00070000) + (val & 0x0000FFFF));
    set_data <<= 8;
    for (i = 0; i < 24; i++) {
        GPIO_SetBits(CLK_PORT, CLK_PIN);
        if (set_data & 0x80000000) GPIO_SetBits(DAT_PORT, DAT_PIN);
        else GPIO_ResetBits(DAT_PORT, DAT_PIN);
        GPIO_ResetBits(CLK_PORT, CLK_PIN);
        set_data <<= 1;
    }
    GPIO_ResetBits(LDAC_PORT, LDAC_PIN);
    GPIO_SetBits(LDAC_PORT, LDAC_PIN);
}

#if 0

#include "sys.h"
#include "delay.h"

#define clk_set PBout(13)=1
#define clk_rst PBout(13)=0

#define din_set PBout(14)=1
#define din_rst PBout(14)=0

void DAC_LOAD(void);

void DAC_START(void);

void DAC_CLR(void);

void ad5663_init() {

    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);     //使能PC,D,G端口时钟

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_8 | GPIO_Pin_13 | GPIO_Pin_14;     //PD3,PD6推挽输出
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;         //推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//速度50MHz
    GPIO_Init(GPIOB, &GPIO_InitStructure);      //初始化GPIOD3,6
    GPIO_SetBits(GPIOB, GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_8 | GPIO_Pin_13 | GPIO_Pin_14);    //PD3,PD6 输出高
}


void DAC_LOAD()  //LDAC
{
    GPIO_ResetBits(GPIOB, GPIO_Pin_8);
    GPIO_SetBits(GPIOB, GPIO_Pin_8);
}

void DAC_START()  //SYNC
{
    GPIO_SetBits(GPIOB, GPIO_Pin_10);
    GPIO_ResetBits(GPIOB, GPIO_Pin_10);
}

void DAC_CLR() {
    GPIO_ResetBits(GPIOB, GPIO_Pin_9);
    GPIO_SetBits(GPIOB, GPIO_Pin_9);
}

void DAC_SET(u8 chanel, u16 data) {
    u8 i = 0;
    u32 set_data;
    clk_set;
    DAC_START();
    clk_rst;

    set_data = ((0 << 19) & 0x00380000) + ((chanel << 16) & 0x00070000) + (data & 0x0000FFFF);

    set_data <<= 8;

    for (i = 0; i < 24; i++) {
        clk_set;
        if (set_data & 0x80000000) {
            din_set;
        } else {
            din_rst;
        }

        clk_rst;
        set_data <<= 1;
    }

    DAC_LOAD();

}
#endif