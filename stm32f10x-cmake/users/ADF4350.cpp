//
// Created by lsy on 17-6-7.
//

#include "ADF4350.h"
#include <stm32f10x_gpio.h>
#include "stm32f10x.h"
#include "delay.h"

#include "same.h"

/* Registers */
#define ADF4350_REG0 0
#define ADF4350_REG1 1
#define ADF4350_REG2 2
#define ADF4350_REG3 3
#define ADF4350_REG4 4
#define ADF4350_REG5 5

/* REG0 Bit Definitions */
#define ADF4350_REG0_FRACT(x) (((x)&0xFFF) << 3)
#define ADF4350_REG0_INT(x) (((x)&0xFFFF) << 15)

/* REG1 Bit Definitions */
#define ADF4350_REG1_MOD(x) (((x)&0xFFF) << 3)
#define ADF4350_REG1_PHASE(x) (((x)&0xFFF) << 15)
#define ADF4350_REG1_PRESCALER (1 << 27)

/* REG2 Bit Definitions */
#define ADF4350_REG2_COUNTER_RESET_EN (1 << 3)
#define ADF4350_REG2_CP_THREESTATE_EN (1 << 4)
#define ADF4350_REG2_POWER_DOWN_EN (1 << 5)
#define ADF4350_REG2_PD_POLARITY_POS (1 << 6)
#define ADF4350_REG2_LDP_6ns (1 << 7)
#define ADF4350_REG2_LDP_10ns (0 << 7)
#define ADF4350_REG2_LDF_FRACT_N (0 << 8)
#define ADF4350_REG2_LDF_INT_N (1 << 8)
#define ADF4350_REG2_CHARGE_PUMP_CURR_uA(x) (((((x)-312) / 312) & 0xF) << 9)
#define ADF4350_REG2_DOUBLE_BUFF_EN (1 << 13)
#define ADF4350_REG2_10BIT_R_CNT(x) ((x) << 14)
#define ADF4350_REG2_RDIV2_EN (1 << 24)
#define ADF4350_REG2_RMULT2_EN (1 << 25)
#define ADF4350_REG2_MUXOUT(x) ((x) << 26)
#define ADF4350_REG2_NOISE_MODE(x) (((unsigned)(x)) << 29)
#define ADF4350_MUXOUT_THREESTATE 0
#define ADF4350_MUXOUT_DVDD 1
#define ADF4350_MUXOUT_GND 2
#define ADF4350_MUXOUT_R_DIV_OUT 3
#define ADF4350_MUXOUT_N_DIV_OUT 4
#define ADF4350_MUXOUT_ANALOG_LOCK_DETECT 5
#define ADF4350_MUXOUT_DIGITAL_LOCK_DETECT 6

/* REG3 Bit Definitions */
#define ADF4350_REG3_12BIT_CLKDIV(x) ((x) << 3)
#define ADF4350_REG3_12BIT_CLKDIV_MODE(x) ((x) << 16)
#define ADF4350_REG3_12BIT_CSR_EN (1 << 18)
#define ADF4351_REG3_CHARGE_CANCELLATION_EN (1 << 21)
#define ADF4351_REG3_ANTI_BACKLASH_3ns_EN (1 << 22)
#define ADF4351_REG3_BAND_SEL_CLOCK_MODE_HIGH (1 << 23)

/* REG4 Bit Definitions */
#define ADF4350_REG4_OUTPUT_PWR(x) ((x) << 3)
#define ADF4350_REG4_RF_OUT_EN (1 << 5)
#define ADF4350_REG4_AUX_OUTPUT_PWR(x) ((x) << 6)
#define ADF4350_REG4_AUX_OUTPUT_EN (1 << 8)
#define ADF4350_REG4_AUX_OUTPUT_FUND (1 << 9)
#define ADF4350_REG4_AUX_OUTPUT_DIV (0 << 9)
#define ADF4350_REG4_MUTE_TILL_LOCK_EN (1 << 10)
#define ADF4350_REG4_VCO_PWRDOWN_EN (1 << 11)
#define ADF4350_REG4_8BIT_BAND_SEL_CLKDIV(x) ((x) << 12)
#define ADF4350_REG4_RF_DIV_SEL(x) ((x) << 20)
#define ADF4350_REG4_FEEDBACK_DIVIDED (0 << 23)
#define ADF4350_REG4_FEEDBACK_FUND (1 << 23)

/* REG5 Bit Definitions */
#define ADF4350_REG5_LD_PIN_MODE_LOW (0 << 22)
#define ADF4350_REG5_LD_PIN_MODE_DIGITAL (1 << 22)
#define ADF4350_REG5_LD_PIN_MODE_HIGH (3 << 22)

/* Specifications */
#define ADF4350_MAX_OUT_FREQ 4400000000ULL      /* Hz */
#define ADF4350_MIN_OUT_FREQ 137500000          /* Hz */
#define ADF4351_MIN_OUT_FREQ 34375000           /* Hz */
#define ADF4350_MIN_VCO_FREQ 2200000000ULL      /* Hz */
#define ADF4350_MAX_FREQ_45_PRESC 3000000000ULL /* Hz */
#define ADF4350_MAX_FREQ_PFD 32000000           /* Hz */
#define ADF4350_MAX_BANDSEL_CLK 125000          /* Hz */
#define ADF4350_MAX_FREQ_REFIN 250000000        /* Hz */
#define ADF4350_MAX_MODULUS 4095
#define ADF4350_MAX_R_CNT 1023

void ADF4350::send(u32 dat) {
    int8_t t = 32;
    GPIO_ResetBits(LE_FAM, LE_PIN);
    while (t--) {
        delay_us(2);
        GPIO_ResetBits(SCK_FAM, SCK_PIN);
        if (dat & (1 << t))
            GPIO_SetBits(DAT_FAM, DAT_PIN);
        else
            GPIO_ResetBits(DAT_FAM, DAT_PIN);
        delay_us(2);
        GPIO_SetBits(SCK_FAM, SCK_PIN);
    }
    delay_us(2);
    GPIO_ResetBits(SCK_FAM, SCK_PIN);
    GPIO_SetBits(LE_FAM, LE_PIN);
    delay_us(2);
}

void ADF4350::init(void) {

    send(
            ADF4350_REG5_LD_PIN_MODE_DIGITAL |         //锁定检测引脚工作方式
            ADF4350_REG5
    );


    send(
            ADF4350_REG4_FEEDBACK_FUND |               //反馈选择:从VCO输出到N计数器的反馈,1从VCO获得,0分频器的输出获得
            ADF4350_REG4_RF_DIV_SEL(0x6) |               //RF分频器选择:选择RF输出分频器的
            ADF4350_REG4_8BIT_BAND_SEL_CLKDIV(0xF0) |   //频段选择时钟分频器值
            //            ADF4350_REG4_VCO_PWRDOWN_EN |              //VCO关断
            ADF4350_REG4_MUTE_TILL_LOCK_EN |           //静音至检测到锁定(MTLD)
            ADF4350_REG4_AUX_OUTPUT_FUND |
            //辅助输出选择:DB9位设置辅助RF输出。DB9设为0时,辅助RF输出为RF分频器的输出;DB9设为1时,辅助RF输出为VCO基频。
            ADF4350_REG4_AUX_OUTPUT_EN |               //辅助输出使能:为0时,辅助RF输出禁用;DB8设为1时,辅助RF输出使能。
            ADF4350_REG4_RF_OUT_EN |                   //RF输出使能
            ADF4350_REG4_OUTPUT_PWR(0x3) |             //输出功率
            ADF4350_REG4_AUX_OUTPUT_PWR(0x3) |         //辅助输出功率
            ADF4350_REG4
    );


    send(
            // ADF4351_REG3_BAND_SEL_CLOCK_MODE_HIGH | //频段选择时钟模式
            // ADF4351_REG3_ANTI_BACKLASH_3ns_EN |     //防反冲脉冲宽度(ABP)
            // ADF4351_REG3_CHARGE_CANCELLATION_EN |   //电荷消除:设为1将使能电荷泵电荷消除功能降低整数N分频模式下的PFD杂散
            ADF4350_REG3_12BIT_CSR_EN |             //CSR使能
            ADF4350_REG3_12BIT_CLKDIV_MODE(0x1) |   //时钟分频器模式:为00时将禁用时钟分频
            ADF4350_REG3_12BIT_CLKDIV(0x4b3) |      //12位时钟分频器值
            ADF4350_REG3
    );


    send(
//            ADF4350_REG2_NOISE_MODE(0x0) |           //低噪声和低杂散模式
            ADF4350_REG2_MUXOUT(0x3) |               //片内多路复用器由位
            //            ADF4350_REG2_RMULT2_EN |              //参考倍频器:当DB25位设置为0时,倍频器禁用
            ADF4350_REG2_RDIV2_EN |                  //DB24位设置为1时,R分频器与PFD之间将插入一个二分频触发器,以扩大REFIN最大输入速率。
            ADF4350_REG2_10BIT_R_CNT(5) |            //10位R分频器:分频比可以为1至1023
            ADF4350_REG2_DOUBLE_BUFF_EN |            //双缓冲器
            ADF4350_REG2_CHARGE_PUMP_CURR_uA(2500) | //电荷泵电流设置
            ADF4350_REG2_LDF_FRACT_N |                 //锁定检测功能(LDF):LDF控制PFD周期数,锁定检测电路监视该周期数以确定是否实现锁定。
            ADF4350_REG2_LDP_10ns |                   //锁定检测精度(LDP):为0时,比较窗口为10 ns;DB7设为1时,比较窗口为6 ns
            ADF4350_REG2_PD_POLARITY_POS |           //鉴相器极性:如果使用无源环路滤波器或同相有源环路滤波器将此位设置为1。反相有源滤波器将此位设置为0。
            // ADF4350_REG2_POWER_DOWN_EN |          //关断(PD):当此位设置为1时,执行关断,当此位设置为0时,频率合成器恢复正常工作。
            // ADF4350_REG2_CP_THREESTATE_EN |       //电荷泵三态:DB4位设置为1时,电荷泵进入三态模式。正常工作时,应将此位设置为0。
            //             ADF4350_REG2_COUNTER_RESET_EN |          //分频器复位
            ADF4350_REG2
    );

    send(
            ADF4350_REG1_PRESCALER |               //预分频器值
            ADF4350_REG1_PHASE(1) |                  //12位相位值
            ADF4350_REG1_MOD(1250) |             //12位模数值(MOD)
            ADF4350_REG1
    );

    send(
            ADF4350_REG0_INT(255) |
            //16位整数值(INT):对于4/5预分频器,可以设置23 如果相位再同步和杂散优化功能均不使用,建议将相位字到65,535的整数值;对于8/9预分频器,最小整数值为75。
            ADF4350_REG0_FRACT(1250) |                  //12位小数值(FRAC)
            ADF4350_REG0
    );
}

void ADF4350::freq(float f) {
    uint32_t INT, FAC;

    INT = (uint32_t) (((int) f) / 156250);
    FAC = (uint32_t) (int) (1250 * (f - INT * 156250) / 156250);

    send(ADF4350_REG0_INT(INT) | ADF4350_REG0_FRACT(FAC) | ADF4350_REG0);
}

ADF4350::ADF4350(
        GPIO_TypeDef *SCK_FAM, uint16_t SCK_PIN,
        GPIO_TypeDef *DAT_FAM, uint16_t DAT_PIN,
        GPIO_TypeDef *LE_FAM, uint16_t LE_PIN
) : SCK_FAM(SCK_FAM), SCK_PIN(SCK_PIN), DAT_FAM(DAT_FAM),
    DAT_PIN(DAT_PIN), LE_FAM(LE_FAM), LE_PIN(LE_PIN) {

    GPIO_INIT_OUT(SCK_FAM,SCK_PIN);
    GPIO_INIT_OUT(DAT_FAM,DAT_PIN);
    GPIO_INIT_OUT(LE_FAM,LE_PIN);

    init();
};


//void ADF4350_send(u32 d) {
//    int8_t t = 32;
//    ADF4350_LE_L;
//    while (t--) {
//        delay_us(2);
//        ADF4350_CLK_L;
//        if (d & (1 << t))
//            ADF4350_DAT_H;
//        else
//            ADF4350_DAT_L;
//        delay_us(2);
//        ADF4350_CLK_H;
//    }
//    delay_us(2);
//    ADF4350_CLK_L;
//    ADF4350_LE_H;
//    delay_us(2);
//}
//
//void ADF4350_init(void) {
//    GPIO_InitTypeDef adf;
//
//    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
//
//    adf.GPIO_Speed = GPIO_Speed_50MHz;
//    adf.GPIO_Mode = GPIO_Mode_Out_PP;
//    adf.GPIO_Pin = ADF4350_CLK | ADF4350_DAT | ADF4350_LE | ADF4350_CE;
//
//    GPIO_Init(ADF4350_FAMILY, &adf);
//
//    ADF4350_CE_H;
//    delay_ms(10);
//    /**
//     *
//     * RF OUT = [INT + (FRAC/MOD)] × (f PFD /RF Divider) // [7,20479]MHz = [[24,65535] + [0,4095] / 1250] * (10MHz / 64)
//     *
//     * RF Divider是细分VCO频率的输出分频器。 // 1
//     *
//     *
//     * f PFD = REF IN × [(1 + D)/(R × (1 + T))] // 10MHz = 100MHz*((1 + 0) / (5*(1 + 1)))
//     *
//     * REF IN 是参考频率输入;
//     * D是RF REF IN 倍频器位(0或1); // 1
//     * R是RF参考分频系数(1至1023)   // 500
//     * T是参考2分频位(0或1)。      // 1
//     *
//     *
//     * 00000000 01000000 00000000 00000 000  0
//     * 00001000 00000000 10000000 00010 001  1
//     * 00000000 00000000 01001110 01000 010  2
//     * 00000000 00000000 00000100 10110 011  3
//     * 00000000 11001100 10000000 00111 100  4
//     * 00000000 01011000 00000000 00000 101  5
//     *
//     *
//     * 00000000 01000101 10000000 10101 000  0
//     * 00001000 00000000 10000000 11001 001  1
//     * 00000000 00000000 01001110 01000 010  2
//     * 00000000 00000000 00000100 10110 011  3
//     * 00000000 10111100 10000000 00111 100  4
//     * 00000000 01011000 00000000 00000 101  5
//     *
//     *
//     *0
//     */
//    ADF4350_send(
//            ADF4350_REG5_LD_PIN_MODE_DIGITAL |         //锁定检测引脚工作方式
//            ADF4350_REG5
//    );
//
//
//    ADF4350_send(
//            ADF4350_REG4_FEEDBACK_FUND |               //反馈选择:从VCO输出到N计数器的反馈,1从VCO获得,0分频器的输出获得
//            ADF4350_REG4_RF_DIV_SEL(0x6) |               //RF分频器选择:选择RF输出分频器的
//            ADF4350_REG4_8BIT_BAND_SEL_CLKDIV(0xF0) |   //频段选择时钟分频器值
//            //            ADF4350_REG4_VCO_PWRDOWN_EN |              //VCO关断
//            //            ADF4350_REG4_MUTE_TILL_LOCK_EN |           //静音至检测到锁定(MTLD)
//            ADF4350_REG4_AUX_OUTPUT_FUND |
//            //辅助输出选择:DB9位设置辅助RF输出。DB9设为0时,辅助RF输出为RF分频器的输出;DB9设为1时,辅助RF输出为VCO基频。
//            ADF4350_REG4_AUX_OUTPUT_EN |               //辅助输出使能:为0时,辅助RF输出禁用;DB8设为1时,辅助RF输出使能。
//            ADF4350_REG4_RF_OUT_EN |                   //RF输出使能
//            ADF4350_REG4_OUTPUT_PWR(0x3) |             //输出功率
//            ADF4350_REG4_AUX_OUTPUT_PWR(0x3) |         //辅助输出功率
//            ADF4350_REG4
//    );
//
//
//    ADF4350_send(
//            // ADF4351_REG3_BAND_SEL_CLOCK_MODE_HIGH | //频段选择时钟模式
//            // ADF4351_REG3_ANTI_BACKLASH_3ns_EN |     //防反冲脉冲宽度(ABP)
//            // ADF4351_REG3_CHARGE_CANCELLATION_EN |   //电荷消除:设为1将使能电荷泵电荷消除功能降低整数N分频模式下的PFD杂散
//            ADF4350_REG3_12BIT_CSR_EN |             //CSR使能
//            ADF4350_REG3_12BIT_CLKDIV_MODE(0x1) |   //时钟分频器模式:为00时将禁用时钟分频
//            ADF4350_REG3_12BIT_CLKDIV(0x4b3) |      //12位时钟分频器值
//            ADF4350_REG3
//    );
//
//
//    ADF4350_send(
////            ADF4350_REG2_NOISE_MODE(0x0) |           //低噪声和低杂散模式
//            ADF4350_REG2_MUXOUT(0x3) |               //片内多路复用器由位
//            //            ADF4350_REG2_RMULT2_EN |              //参考倍频器:当DB25位设置为0时,倍频器禁用
//            ADF4350_REG2_RDIV2_EN |                  //DB24位设置为1时,R分频器与PFD之间将插入一个二分频触发器,以扩大REFIN最大输入速率。
//            ADF4350_REG2_10BIT_R_CNT(5) |            //10位R分频器:分频比可以为1至1023
//            ADF4350_REG2_DOUBLE_BUFF_EN |            //双缓冲器
//            ADF4350_REG2_CHARGE_PUMP_CURR_uA(2500) | //电荷泵电流设置
//            ADF4350_REG2_LDF_FRACT_N |                 //锁定检测功能(LDF):LDF控制PFD周期数,锁定检测电路监视该周期数以确定是否实现锁定。
//            ADF4350_REG2_LDP_10ns |                   //锁定检测精度(LDP):为0时,比较窗口为10 ns;DB7设为1时,比较窗口为6 ns
//            ADF4350_REG2_PD_POLARITY_POS |           //鉴相器极性:如果使用无源环路滤波器或同相有源环路滤波器将此位设置为1。反相有源滤波器将此位设置为0。
//            // ADF4350_REG2_POWER_DOWN_EN |          //关断(PD):当此位设置为1时,执行关断,当此位设置为0时,频率合成器恢复正常工作。
//            // ADF4350_REG2_CP_THREESTATE_EN |       //电荷泵三态:DB4位设置为1时,电荷泵进入三态模式。正常工作时,应将此位设置为0。
//            //             ADF4350_REG2_COUNTER_RESET_EN |          //分频器复位
//            ADF4350_REG2
//    );
//
//    ADF4350_send(
//            ADF4350_REG1_PRESCALER |               //预分频器值
//            ADF4350_REG1_PHASE(1) |                  //12位相位值
//            ADF4350_REG1_MOD(1250) |             //12位模数值(MOD)
//            ADF4350_REG1
//    );
//
//    ADF4350_send(
//            ADF4350_REG0_INT(255) |
//            //16位整数值(INT):对于4/5预分频器,可以设置23 如果相位再同步和杂散优化功能均不使用,建议将相位字到65,535的整数值;对于8/9预分频器,最小整数值为75。
//            ADF4350_REG0_FRACT(1250) |                  //12位小数值(FRAC)
//            ADF4350_REG0
//    );
//}
//
//
//void ADF4350_freq(float freq) {
//    uint32_t INT, FAC;
//    INT = (uint32_t) (((int) freq) / 312500);
//    FAC = (uint32_t) (int) (1250 * (freq - INT * 312500) / 312500);
//    ADF4350_send(
//            ADF4350_REG0_INT(INT) |
//            //16位整数值(INT):对于4/5预分频器,可以设置23 如果相位再同步和杂散优化功能均不使用,建议将相位字到65,535的整数值;对于8/9预分频器,最小整数值为75。
//            ADF4350_REG0_FRACT(FAC) |                  //12位小数值(FRAC)
//            ADF4350_REG0
//    );
//}

