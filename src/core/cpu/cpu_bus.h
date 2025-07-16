#include <stdint.h>

typedef struct
{
    uint8_t *cpu_ram;
    uint8_t *ppu_regs;
    uint8_t *apu_io_regs;
    uint8_t *prg_ram;
    uint8_t open_bus;
    uint8_t (*read_func)(uint16_t, cpu_bus);
    uint8_t (*write_func)(uint16_t, uint8_t, cpu_bus);

} cpu_bus;

cpu_bus bus_init();
