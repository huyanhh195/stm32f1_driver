#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>
#include <stdbool.h>

#include "register_defs.h"

// TODO: Remove this include
#include "stm32f1xx_hal.h"

/** 
  * @brief GPIO Pin definitions
  */
#define GPIO_0   (1U << 0)  // Pin 0 selected
#define GPIO_1   (1U << 1)  // Pin 1 selected
#define GPIO_2   (1U << 2)  // Pin 2 selected
#define GPIO_3   (1U << 3)  // Pin 3 selected
#define GPIO_4   (1U << 4)  // Pin 4 selected
#define GPIO_5   (1U << 5)  // Pin 5 selected
#define GPIO_6   (1U << 6)  // Pin 6 selected
#define GPIO_7   (1U << 7)  // Pin 7 selected
#define GPIO_8   (1U << 8)  // Pin 8 selected
#define GPIO_9   (1U << 9)  // Pin 9 selected
#define GPIO_10  (1U << 10) // Pin 10 selected
#define GPIO_11  (1U << 11) // Pin 11 selected
#define GPIO_12  (1U << 12) // Pin 12 selected
#define GPIO_13  (1U << 13) // Pin 13 selected
#define GPIO_14  (1U << 14) // Pin 14 selected
#define GPIO_15  (1U << 15) // Pin 15 selected
#define GPIO_ALL (0xFFFF)   // All pins selected

#define GPIO_MASK (0x0000FFFFU) // PIN mask for assert test

#define GPIO_NUM_MAX (16U)

/** 
  * @brief GPIO init struct definition
  */
typedef struct
{
    uint32_t pin;       // GPIO pin number
    uint32_t mode;      // GPIO pin mode
    uint32_t pull;      // GPIO pin pull-up/down configuration
    uint32_t speed;     // GPIO pin speed
    uint32_t alternate; // GPIO pin alternate function
} st_gpio_init_def_t;

/** 
  * @brief GPIO Pin mode
  */
typedef enum
{
    MY_GPIO_MODE_ANALOG, // Analog mode
    MY_GPIO_MODE_IN,     // Input floating
    MY_GPIO_MODE_OUT_PP, // Ouput push-pull
    MY_GPIO_MODE_OUT_OD, // Ouput open-drain
    MY_GPIO_MODE_ALT_PP, // Alternate function output Push-pull
    MY_GPIO_MODE_ALT_OD  // Alternate function output open-drain
} e_gpio_mode_t;

/** 
  * @brief GPIO speed mode
  */
typedef enum
{
    MY_GPIO_SPEED_LOW,    // Max speed 2 MHz
    MY_GPIO_SPEED_MEDIUM, // Max speed 10 MHz
    MY_GPIO_SPEED_HIGH    // Max speed 50 MHz
} e_gpio_speed_t;

/** 
  * @brief GPIO Pin state
  */
typedef enum
{
    GPIO_STATE_LOW  = 0,
    GPIO_STATE_HIGH = 1
} e_gpio_state_t;

/**
  * @brief  Initializes the GPIO pin
  * @param  gpiox: specifies the GPIO pin
  * @param  gpio_init: specifies the configuration of the GPIO pin
  * @retval true if successful, false otherwise
  */
bool gpio_init(st_gpio_def_t *gpiox, const st_gpio_init_def_t *gpio_init);

/**
  * @brief  Configures mode for the GPIO pin
  * @param  gpiox: specifies the GPIO pin
  * @param  gpio_init: specifies the configuration of the GPIO pin
  * @retval true if successful, false otherwise
  */
bool gpio_set_mode(st_gpio_def_t *gpiox, const st_gpio_init_def_t *gpio_init);

/**
  * @brief  Configures speed for the GPIO pin
  * @param  gpiox: specifies the GPIO
  * @param  gpio_init: specifies the configuration of the GPIO pin
  * @retval true if successful, false otherwise
  */
bool gpio_set_speed(st_gpio_def_t *gpiox, const st_gpio_init_def_t *gpio_init);

/**
  * @brief  Reads the specified GPIO port pin
  * @param  gpiox: specifies the GPIO pin
  * @param  pin: specifies the port bit to read
  *             This parameter can be GPIO_x where x can be (0..15)
  * @retval The GPIO pin state
  */
e_gpio_state_t gpio_read(st_gpio_def_t *gpiox, uint32_t pin);

/**
  * @brief  Writes the specified GPIO port pin.
  * @param  gpiox: specifies the GPIO pin
  * @param  pin: specifies the port bit to write.
  *             This parameter can be GPIO_x where x can be (0..15)
  * @param  state: specifies the GPIO pin state.
  *                This parameter can be a value of e_gpio_state_t
  * @retval None
  */
void gpio_write(st_gpio_def_t *gpiox, uint32_t pin, e_gpio_state_t state);

/**
  * @brief  Toggles the specified GPIO port pin
  * @param  gpiox: specifies the GPIO pin
  * @param  pin: specifies the port bit to toggle.
  *             This parameter can be GPIO_x where x can be (0..15)
  * @param  delay_ms: specifies delay in ms
  * @retval None.
  */
void gpio_toggle(st_gpio_def_t *gpiox, uint32_t pin, uint8_t delay_ms);

#endif /* GPIO_H */
