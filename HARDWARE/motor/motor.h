#ifndef HARDWARE_MOTOR_H
#define HARDWARE_MOTOR_H

#include "delay.h"

#define TB6600_RCC   RCC_APB2Periph_GPIOA
#define TB6600_PORT  GPIOA

#define DIR_PIN_PORT TB6600_PORT
#define DIR_PIN      GPIO_Pin_4

#define PUL_PIN_PORT TB6600_PORT
#define PUL_PIN      GPIO_Pin_5

#define ENA_PIN_PORT TB6600_PORT
#define ENA_PIN      GPIO_Pin_6

void motor_gpio_init(void);
void motor_cmd(uint8_t mode, uint16_t pul, uint16_t half_time);

#endif
