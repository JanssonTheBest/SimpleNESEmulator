#include <stdint.h>
#include <cpu_bus.h>

uint8_t cpu_ram[0x0800];
uint8_t ppu_regs[0x0008];
uint8_t apu_and_io_regs[0x0018];
uint8_t prg_ram[0x2000];

//TODO FIGURE OUT IF HAANDLING ALL MIRRORS IN ONE RANGE COMPLICATES THE OFFSET LOGIC
uint8_t cpu_read(uint16_t address)
{
    if (address < 0x2000)
    {
        //cpu ram and its mirrors
    
        return 0;
    }

    if (address < 0x2008)
    {
        //ppu regs

        return 0;
    }

    
}

uint8_t cpu_write(uint16_t address)
{
}
