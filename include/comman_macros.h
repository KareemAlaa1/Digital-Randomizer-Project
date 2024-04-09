#ifndef comman_macros
#define comman_macros

#define SET_BIT(reg, bit) (reg |= (1 << bit))
#define CLEAR_BIT(reg, bit) (reg &= ~(1 << bit))
#define TOGGLE_BIT(reg, bit) (reg ^= (1 << bit))
#define READ_BIT(REG_NAME, BIT_NUM) (REG_NAME >> BIT_NUM) & 1

#endif