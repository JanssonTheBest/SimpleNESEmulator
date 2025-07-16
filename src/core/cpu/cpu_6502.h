#include <stdint.h>

#pragma once

typedef struct
{
    uint8_t reg_a;
    uint8_t reg_x;
    uint8_t reg_pc;
    uint8_t reg_y;
    uint8_t reg_sp;
    uint8_t reg_p;

    uint8_t flag_carry;
    uint8_t flag_zero;
    uint8_t flag_interrupt_disable;
    uint8_t flag_decimal;
    uint8_t flag_overflow;
    uint8_t flag_negative;
    const uint8_t flag_unused;

    cpu_bus *cpu_bus;
    
    uint8_t clock_count;

    int (*cpu_step_func)(cpu_6502*);
} cpu_6502;

cpu_6502 cpu_init(cpu_bus bus);
