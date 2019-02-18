#ifndef AD5663_H
#define AD5663_H

#include "stm32f4xx.h"

#include "stdint-gcc.h"

class AD5663 {
private:
    GPIO_TypeDef *CLK_PORT;
    GPIO_TypeDef *DAT_PORT;
    GPIO_TypeDef *LDAC_PORT;
    GPIO_TypeDef *SYNC_PORT;
    uint16_t CLK_PIN;
    uint16_t DAT_PIN;
    uint16_t LDAC_PIN;
    uint16_t SYNC_PIN;

public:
    AD5663(GPIO_TypeDef *CLK_PORT, uint16_t CLK_PIN,
           GPIO_TypeDef *DAT_PORT, uint16_t DAT_PIN,
           GPIO_TypeDef *LDAC_PORT, uint16_t LDAC_PIN,
           GPIO_TypeDef *SYNC_PORT, uint16_t SYNC_PIN);

    void output(uint8_t ch, uint16_t val);
};

//
//void ad5663_init(void);
//
//void DAC_SET(u8 chanel, u16 data);

#endif
