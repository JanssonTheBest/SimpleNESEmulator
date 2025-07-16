#include "../core/cpu/cpu_6502.h"
#include "../core/cpu/cpu_bus.h"

int emulate(char* file_path)
{
    cpu_bus bus = bus_init();
    cpu_6502 cpu = cpu_init(bus);
}