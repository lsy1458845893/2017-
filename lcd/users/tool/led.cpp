#include <led.h>
#include <stm32f4xx_gpio.h>

#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "same.h"

void Led::change(void) {
    if (status) {
        status = 0;
        GPIO_SetBits(family, port);
    } else {
        status = 1;
        GPIO_ResetBits(family, port);
    }
}

Led::Led(GPIO_TypeDef *family, uint32_t pin) : family(family), port(port) {
    GPIO_INIT_OUT(family, port);
}
