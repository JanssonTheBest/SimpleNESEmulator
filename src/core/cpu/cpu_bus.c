#include <stdint.h>
#include "cpu_bus.h"
#include <stdio.h>
#include <stdlib.h>

cpu_bus bus_init()
{
    cpu_bus bus = {
        bus.read_func = &cpu_read,
        bus.write_func = &cpu_write,
    };
    return bus;
}

uint8_t cpu_read(uint16_t addr, cpu_bus *bus)
{
    uint8_t data = bus->open_bus;
    if (addr < 0x2000)
    {
        // cpu ram and its mirrors reepats every 2kb
        data = bus->cpu_ram[addr & 0x07FF];
    }
    else if (addr < 0x4000)
    {
        // ppu regs and it mirrors repeats every 8kb
    }
    else if (addr < 0x4018)
    {
        // implement apu and io reads
    }
    else if (addr < 0x4020)
    {
        // apu and io cpu test -- no implementation
    }
    else
    {
        // implement custom cartidage reads
    }

    bus->open_bus = data;
    return data;
}

uint8_t cpu_write(uint16_t address, uint8_t memory, cpu_bus *bus)
{
}
