#ifndef REGISTER_DEFS_H
#define REGISTER_DEFS_H

#include <stdint.h>

/** 
  * @brief General Purpose I/O
  */
typedef struct
{
    volatile uint32_t CRL;  // Port configuration register low (0 .. 7)
    volatile uint32_t CRH;  // Port configuration register high (8 .. 15)
    volatile uint32_t IDR;  // Port input data register
    volatile uint32_t ODR;  // Port output data register
    volatile uint32_t BSRR; // Port bit set/reset register
    volatile uint32_t BRR;  // Port bit reset register
    volatile uint32_t LCKK; // Port configuration lock register
} st_gpio_def_t;

/** 
  * @brief RCC 
  */
typedef struct
{
    volatile uint32_t CR;       // Clock control register
    volatile uint32_t CFGR;     // Clock configuration register
    volatile uint32_t CIR;      // Clock interrupt register
    volatile uint32_t APB2RSTR; // APB2 peripheral reset register
    volatile uint32_t APB1RSTR; // APB1 peripheral reset register
    volatile uint32_t AHBENR;   // AHB peripheral clock enable register
    volatile uint32_t APB2ENR;  // APB2 peripheral clock enable register
    volatile uint32_t APB1ENR;  // APB1 peripheral clock enable register
    volatile uint32_t BDCR;     // Backup domain control register
    volatile uint32_t CSR;      // Control/status register
} st_rcc_def_t;

/** 
  * @brief Peripheral memrory map
  */
#define PERIPHERAL_BASE (0x40000000UL) // Peripheral base address in the alias region

#define APB1_PERIPH_BASE PERIPHERAL_BASE
#define APB2_PERIPH_BASE (PERIPHERAL_BASE + 0x00010000UL)
#define AHB_PERIPH_BASE  (PERIPHERAL_BASE + 0x00020000UL)

#define GPIO_BASE_A (APB2_PERIPH_BASE + 0x00000800UL) // GPIO port A base address
#define GPIO_BASE_B (APB2_PERIPH_BASE + 0x00000C00UL) // GPIO port B base address
#define GPIO_BASE_C (APB2_PERIPH_BASE + 0x00001000UL) // GPIO port C base address
#define GPIO_BASE_D (APB2_PERIPH_BASE + 0x00001400UL) // GPIO port D base address
#define GPIO_BASE_E (APB2_PERIPH_BASE + 0x00001800UL) // GPIO port E base address

#define RCC_PERIPH_BASE (AHB_PERIPH_BASE + 0x00001000UL) // Reset and clock control base address

/** 
  * @brief Peripheral declarations
  */
#define GPIO_PORT_A ((st_gpio_def_t *)GPIO_BASE_A) // GPIO port A
#define GPIO_PORT_B ((st_gpio_def_t *)GPIO_BASE_B) // GPIO port B
#define GPIO_PORT_C ((st_gpio_def_t *)GPIO_BASE_C) // GPIO port C
#define GPIO_PORT_D ((st_gpio_def_t *)GPIO_BASE_D) // GPIO port D
#define GPIO_PORT_E ((st_gpio_def_t *)GPIO_BASE_E) // GPIO port E

#define RCC_PERIPH ((st_rcc_def_t *)RCC_PERIPH_BASE) // RCC peripheral

#endif /* REGISTER_DEFS_H */
