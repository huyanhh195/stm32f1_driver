#include <stdbool.h>

#include "rcc.h"
#include "gpio.h"
#include "register_helpers.h"
#include "register_defs.h"

bool rcc_system_clock_init()
{
    // TODO: implement this function

    // /* Enable HSE */
    // set_bit(RCC_PERIPH->CR, (1U << 16));

    // while (!check_bit(RCC_PERIPH->CR, (1U << 17)))
    // {
    //     /* Wait for HSE ready */
    // }

    // /* Select HSE as system clock */
    // set_bit(RCC_PERIPH->CFGR, (1U << 0));

    // while ((RCC_PERIPH->CFGR & (3U << 2)) != (1U << 2))
    // {
    //     /* Wait until HSE is selected */
    // }

    return true;
}

bool rcc_gpio_clock_enable(st_gpio_def_t *gpiox)
{
    uint32_t clk_mask = 0x0U;
    bool     ret_val  = true;

    if (NULL == gpiox)
    {
        return false;
    }

    if (GPIO_PORT_A == gpiox)
    {
        clk_mask = RCC_APB2ENR_CLK_IOA;
    }
    else if (GPIO_PORT_B == gpiox)
    {
        clk_mask = RCC_APB2ENR_CLK_IOB;
    }
    else if (GPIO_PORT_C == gpiox)
    {
        clk_mask = RCC_APB2ENR_CLK_IOC;
    }
    else if (GPIO_PORT_D == gpiox)
    {
        clk_mask = RCC_APB2ENR_CLK_IOD;
    }
    else if (GPIO_PORT_E == gpiox)
    {
        clk_mask = RCC_APB2ENR_CLK_IOE;
    }
    else
    {
        /* Invalid GPIO port */
        ret_val = false;
    }

    /* Enable the clock for GPIO port */
    set_bit(&RCC_PERIPH->APB2ENR, clk_mask);

    return ret_val;
}
