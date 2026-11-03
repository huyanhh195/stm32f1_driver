#ifndef REGISTER_HELPERS_H
#define REGISTER_HELPERS_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

inline uint32_t read_register(volatile const uint32_t *reg);
inline void     write_register(volatile uint32_t *reg, uint32_t mask);
inline void     clear_register(volatile uint32_t *reg);
inline void     set_bit(volatile uint32_t *reg, uint32_t mask);
inline void     clear_bit(volatile uint32_t *reg, uint32_t mask);

#endif /* REGISTER_HELPERS_H */
