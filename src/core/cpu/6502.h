#include <stdint.h>

#pragma once

typedef struct opcode
{
    char name[4];
    uint8_t byte_length;
    uint8_t base_cycle_count;
    void (*addressing_mode)(void);
    void (*operate)(void);

} opcode;



