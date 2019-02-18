#include <button.h>
#include <stm32f4xx_conf.h>
#include "stm32f4xx.h"

Button::Button(uint32_t RCC_AHB1Periph_GPIOx, GPIO_TypeDef *GPIO_0,
               uint16_t pin_0, GPIO_TypeDef *GPIO_1, uint16_t pin_1,
               GPIO_TypeDef *GPIO_2, uint16_t pin_2, GPIO_TypeDef *GPIO_3,
               uint16_t pin_3, GPIO_TypeDef *GPIO_4, uint16_t pin_4,
               GPIO_TypeDef *GPIO_5, uint16_t pin_5, GPIO_TypeDef *GPIO_6,
               uint16_t pin_6, GPIO_TypeDef *GPIO_7, uint16_t pin_7) {
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOx, ENABLE);

  GPIO_InitTypeDef butt;

  butt.GPIO_PuPd = GPIO_PuPd_NOPULL;
  butt.GPIO_OType = GPIO_OType_PP;
  butt.GPIO_Mode = GPIO_Mode_OUT;
  butt.GPIO_Speed = GPIO_Speed_100MHz;

  GPIOx[0] = GPIO_0;
  PIN[0] = pin_0;

  butt.GPIO_Pin = pin_0;
  GPIO_Init(GPIO_0, &butt);

  GPIOx[1] = GPIO_1;
  PIN[1] = pin_1;

  butt.GPIO_Pin = pin_1;
  GPIO_Init(GPIO_1, &butt);

  GPIOx[2] = GPIO_2;
  PIN[2] = pin_2;

  butt.GPIO_Pin = pin_2;
  GPIO_Init(GPIO_2, &butt);

  GPIOx[3] = GPIO_3;
  PIN[3] = pin_3;

  butt.GPIO_Pin = pin_3;
  GPIO_Init(GPIO_3, &butt);

  GPIOx[4] = GPIO_4;
  PIN[4] = pin_4;


  butt.GPIO_PuPd = GPIO_PuPd_NOPULL;
  butt.GPIO_OType = GPIO_OType_PP;
  butt.GPIO_Mode = GPIO_Mode_IN;
  butt.GPIO_Speed = GPIO_Speed_100MHz;

  butt.GPIO_Pin = pin_4;
  GPIO_Init(GPIO_4, &butt);

  GPIOx[5] = GPIO_5;
  PIN[5] = pin_5;

  butt.GPIO_Pin = pin_5;
  GPIO_Init(GPIO_5, &butt);

  GPIOx[6] = GPIO_6;
  PIN[6] = pin_6;

  butt.GPIO_Pin = pin_6;
  GPIO_Init(GPIO_6, &butt);

  GPIOx[7] = GPIO_7;
  PIN[7] = pin_7;

  butt.GPIO_Pin = pin_7;
  GPIO_Init(GPIO_7, &butt);
}

uint8_t Button::onup(uint8_t x, uint8_t y) {
    return 0;
}

uint8_t Button::ondown(uint8_t x, uint8_t y) {
    return 0;
}

uint8_t Button::onchange(uint8_t x, uint8_t y) {
    return 0;
}

uint8_t Button::isup(uint8_t x, uint8_t y) {
    return 0;
}

uint8_t Button::isdown(uint8_t x, uint8_t y) {
    return 0;
}

uint8_t Button::get_input(void) {
    return 0;
}
