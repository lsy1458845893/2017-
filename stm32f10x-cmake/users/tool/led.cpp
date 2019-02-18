#include <led.h>
#include <same.h>

#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

void Led::change(void) {
  if (status) {
    status = 0;
    GPIO_SetBits(fmy, pin);
  } else {
    status = 1;
    GPIO_ResetBits(fmy, pin);
  }
}

Led::Led(GPIO_TypeDef *fmy, uint16_t pin):fmy(fmy),pin(pin) {
  RCC_INIT(fmy);

  GPIO_InitTypeDef led;

  led.GPIO_Speed = GPIO_Speed_50MHz;
  led.GPIO_Mode = GPIO_Mode_Out_PP;
  led.GPIO_Pin = pin;

  GPIO_Init(fmy, &led);
}
