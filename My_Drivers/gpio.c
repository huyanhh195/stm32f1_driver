#include "gpio.h"
#include "rcc.h"
#include "register_helpers.h"
#include "register_defs.h"

static inline bool is_gpio_pin(uint32_t pin)
{
    bool ret_val = false;

    if (((pin & GPIO_MASK) != 0) && ((pin & ~GPIO_MASK) == 0))
    {
        ret_val = true;
    }

    return ret_val;
}

bool gpio_init(st_gpio_def_t *gpiox, const st_gpio_init_def_t *gpio_init)
{
    bool ret_val = true;

    /* Check valid input parameters */
    if (NULL == gpiox || NULL == gpio_init || !is_gpio_pin(gpio_init->pin))
    {
        return false;
    }

    /* Configure GPIO Port clock */
    if (!rcc_gpio_clock_enable(gpiox))
    {
        ret_val = false;
    }

    /* Configure pin mode */
    if (!gpio_set_mode(gpiox, gpio_init))
    {
        ret_val = false;
    }

    return ret_val;
}

// Handle IT mode
bool gpio_set_mode(st_gpio_def_t *gpiox, const st_gpio_init_def_t *gpio_init)
{
    uint32_t config  = 0x0U;
    uint32_t pin_pos = 0x0U;
    bool     ret_val = true;

    /* Check valid input parameters */
    if (NULL == gpiox || !is_gpio_pin(gpio_init->pin))
    {
        return false;
    }

    /* Configure GPIO pin mode */
    for (uint8_t i = 0; i < GPIO_NUM_MAX; i++)
    {
        if (gpio_init->pin & (1U << i))
        {
            /* Select register */
            volatile uint32_t *reg = NULL;
            if (i < 8U)
            {
                reg = &gpiox->CRL;
            }
            else
            {
                reg = &gpiox->CRH;
            }

            /* Get configuration pin mode */
            e_gpio_mode_t mode = (e_gpio_mode_t)gpio_init->mode;
            switch (mode)
            {
                case MY_GPIO_MODE_ANALOG:
                    config = 0x0U; // CNF = 00, MODE = 00
                    break;

                case MY_GPIO_MODE_IN:
                    config = 0x4U; // CNF = 01, MODE = 00
                    break;

                case MY_GPIO_MODE_OUT_PP:
                    config = 0x1U; // CNF = 00, MODE > 00
                    break;

                case MY_GPIO_MODE_OUT_OD:
                    config = 0x5U; // CNF = 01, MODE > 00
                    break;

                case MY_GPIO_MODE_ALT_PP:
                    config = 0x9U; // CNF = 10, MODE > 00
                    break;

                case MY_GPIO_MODE_ALT_OD:
                    config = 0xDU; // CNF = 11, MODE > 00
                    break;

                default:
                    ret_val = false;
                    break;
            }

            /* Check valid mode*/
            if (false == ret_val)
            {
                break;
            }

            /* Get the position of pin within the register */
            pin_pos = (i % 8U) * 4U;

            /* Clear old configuration */
            clear_bit(reg, (0xFU << pin_pos));

            /* Set new configuration */
            set_bit(reg, (config << pin_pos));

            /* Set speed if needed */
            bool is_output_mode = ((mode == MY_GPIO_MODE_OUT_PP) || (mode == MY_GPIO_MODE_OUT_OD) ||
                                   (mode == MY_GPIO_MODE_ALT_PP) || (mode == MY_GPIO_MODE_ALT_OD));
            if (is_output_mode)
            {
                gpio_set_speed(gpiox, gpio_init);
            }
        }
    }

    return ret_val;
}

bool gpio_set_speed(st_gpio_def_t *gpiox, const st_gpio_init_def_t *gpio_init)
{
    uint32_t mode_pos = 0x0U;
    uint32_t config   = 0x0U;
    bool     ret_val  = true;

    /* Check valid input-parameters */
    if (NULL == gpiox || !is_gpio_pin(gpio_init->pin))
    {
        return false;
    }

    /* Handle speed configuration */
    for (uint8_t i = 0; i < GPIO_NUM_MAX; i++)
    {
        /* Check if the pin is selected */
        if (gpio_init->pin & (1U << i))
        {
            /* Select register */
            volatile uint32_t *reg = NULL;
            if (i < 8U)
            {
                reg = &gpiox->CRL;
            }
            else
            {
                reg = &gpiox->CRH;
            }

            /* Get the position mode bits of port within the register */
            mode_pos = (i % 8U) * 4U;

            /* Get speed configuration */
            switch ((e_gpio_speed_t)gpio_init->speed)
            {
                case MY_GPIO_SPEED_LOW:
                    config = 0x2U; // MODE = 10
                    break;

                case MY_GPIO_SPEED_MEDIUM:
                    config = 0x1U; // MODE = 01
                    break;

                case MY_GPIO_SPEED_HIGH:
                    config = 0x3U; // MODE = 11
                    break;

                default:
                    ret_val = false;
                    break;
            }

            /* Check valid speed */
            if (false == ret_val)
            {
                break;
            }

            /* Clear old configuration */
            clear_bit(reg, (0x3U << mode_pos));

            /* Set new configuration */
            set_bit(reg, (config << mode_pos));

            ret_val = true;
        }
    }

    return ret_val;
}

e_gpio_state_t gpio_read(st_gpio_def_t *gpiox, uint32_t pin)
{
    e_gpio_state_t ret_state = GPIO_STATE_LOW;

    /* Check valid input-parameters */
    if (NULL == gpiox || !is_gpio_pin(pin))
    {
        return ret_state;
    }

    if ((gpiox->IDR & pin) != (uint32_t)GPIO_STATE_LOW)
    {
        ret_state = GPIO_STATE_HIGH;
    }

    return ret_state;
}

void gpio_write(st_gpio_def_t *gpiox, uint32_t pin, e_gpio_state_t state)
{
    /* Check valid input-parameters */
    if (NULL == gpiox || !is_gpio_pin(pin))
    {
        return;
    }

    if (GPIO_STATE_HIGH == state)
    {
        gpiox->BSRR = pin; // Set pin
    }
    else
    {
        gpiox->BSRR = (pin << GPIO_NUM_MAX); // Reset pin
    }
}

void gpio_toggle(st_gpio_def_t *gpiox, uint32_t pin, uint8_t delay_ms)
{
    /* Check valid input-parameters */
    if (NULL == gpiox || !is_gpio_pin(pin))
    {
        return;
    }

    e_gpio_state_t state = (gpiox->ODR & pin) ? GPIO_STATE_HIGH : GPIO_STATE_LOW;

    if (GPIO_STATE_HIGH == state)
    {
        gpio_write(gpiox, pin, GPIO_STATE_LOW);
    }
    else
    {
        gpio_write(gpiox, pin, GPIO_STATE_HIGH);
    }

    /* Todo: Implement delay */
    HAL_Delay(delay_ms);
}
