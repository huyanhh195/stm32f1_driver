#pragma once

#include <stdint.h>
#include <stdbool.h>

#include "register_defs.h"

/** 
  * @brief RCC APB2 peripheral clock enable bit definitions
  */
#define RCC_APB2ENR_CLK_ALT (1U << 0) // Alternate Function I/O clock enable
#define RCC_APB2ENR_CLK_IOA (1U << 2) // I/O port A clock enable
#define RCC_APB2ENR_CLK_IOB (1U << 3) // I/O port B clock enable
#define RCC_APB2ENR_CLK_IOC (1U << 4) // I/O port C clock enable
#define RCC_APB2ENR_CLK_IOD (1U << 5) // I/O port D clock enable
#define RCC_APB2ENR_CLK_IOE (1U << 6) // I/O port E clock enable

bool rcc_system_clock_init(void);
bool rcc_gpio_clock_enable(st_gpio_def_t *gpiox);
