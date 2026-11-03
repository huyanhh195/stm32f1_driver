#include "register_helpers.h"

uint32_t read_register(volatile const uint32_t *reg)
{
    if (NULL == reg)
    {
        return 0;
    }

    return *reg;
}

void write_register(volatile uint32_t *reg, uint32_t mask)
{
    if (NULL == reg)
    {
        return;
    }

    *reg = mask;
}

void clear_register(volatile uint32_t *reg)
{
    if (NULL == reg)
    {
        return;
    }

    *reg = 0x0;
}

void set_bit(volatile uint32_t *reg, uint32_t mask)
{
    if (NULL == reg)
    {
        return;
    }

    volatile uint32_t reg_tmp  = read_register(reg);
    reg_tmp                   |= mask;

    write_register(reg, reg_tmp);
}

void clear_bit(volatile uint32_t *reg, uint32_t mask)
{
    if (NULL == reg)
    {
        return;
    }

    volatile uint32_t reg_tmp  = read_register(reg);
    reg_tmp                   &= ~mask;

    write_register(reg, reg_tmp);
}

void toggle_bit(volatile uint32_t *reg, uint32_t mask)
{
    if (NULL == reg)
    {
        return;
    }

    volatile uint32_t reg_tmp  = read_register(reg);
    reg_tmp                   ^= mask;

    write_register(reg, reg_tmp);
}

bool check_bit(volatile const uint32_t *reg, uint32_t mask)
{
    if (NULL == reg)
    {
        return false;
    }

    volatile uint32_t reg_tmp = read_register(reg);

    return ((reg_tmp & mask) != 0);
}
