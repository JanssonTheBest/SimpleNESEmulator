#include <stdint.h>
#include "6502.h"

int initialize(void)
{
}

uint8_t a;
uint8_t x;
uint8_t pc;
uint8_t y;
uint8_t sp;
uint8_t p;

opcode opcode_table[0xFE] = {

    [0x69] = {"ADC", 2, 2, 0, &addressing_immediate, &adc},
    [0x65] = {"ADC", 2, 3, 0, &addressing_zero_page, &adc},
    [0x75] = {"ADC", 2, 4, 0, &addressing_zero_page_indexed_x, &adc},
    [0x6D] = {"ADC", 3, 4, 0, &addressing_absolute, &adc},
    [0x7D] = {"ADC", 3, 4, 5, &addressing_absolute_indexed_x, &adc},
    [0x79] = {"ADC", 3, 4, 5, &addressing_absolute_indexed_y, &adc},
    [0x61] = {"ADC", 2, 6, 0, &addressing_indexed_indirect_x, &adc},
    [0x71] = {"ADC", 2, 5, 6, &addressing_indirect_indexed_y, &adc},

    

}; // 0 indexed FF

// val = PEEK((arg + X) % 256)
void addressing_zero_page_indexed_x()
{
}
// val = PEEK((arg + Y) % 256)
void addressing_zero_page_indexed_y()
{
}
// val = PEEK(arg + X)
void addressing_absolute_indexed_x()
{
}
// val = PEEK(arg + Y)
void addressing_absolute_indexed_y()
{
}
// val = PEEK(PEEK((arg + X) % 256) + PEEK((arg + X + 1) % 256) * 256)
void addressing_indexed_indirect_x()
{
}
// val = PEEK(PEEK(arg) + PEEK((arg + 1) % 256) * 256 + Y)
void addressing_indirect_indexed_y()
{
}
// Instructions like RTS or CLC have no address operand, the destination of results are implied.
void addressing_implicit()
{
}
// Many instructions can operate on the accumulator, e.g. LSR A. Some assemblers will treat no operand as an implicit A where applicable.
void addressing_accumulator()
{
}
// Uses the 8-bit operand itself as the value for the operation, rather than fetching a value from a memory address.
void addressing_immediate()
{
}
// Fetches the value from an 8-bit address on the zero page.
void addressing_zero_page()
{
}
// Fetches the value from a 16-bit address anywhere in memory.
void addressing_absolute()
{
}
// Branch instructions (e.g. BEQ, BCS) have a relative addressing mode that specifies an 8-bit signed offset relative to the current PC.
void addressing_relative()
{
}
// The JMP instruction has a special indirect addressing mode that can jump to the address stored in a 16-bit pointer anywhere in memory.
void addressing_indirect()
{
}

//

// Add with Carry: A = A + memory + C
void adc()
{
}
// Bitwise AND: A = A & memory
void and()
{
}
// Arithmetic Shift Left: value = value << 1, or visually: C <- [76543210] <- 0
void asl()
{
}
// Branch if Carry Clear: PC = PC + 2 + memory (signed)
void bcc()
{
}
// Branch if Carry Set: PC = PC + 2 + memory (signed)
void bcs()
{
}
// Branch if Equal: PC = PC + 2 + memory (signed)
void beq()
{
}
// Bit Test: A & memory
void bit()
{
}
// Branch if Minus: PC = PC + 2 + memory (signed)
void bmi()
{
}
// Branch if Not Equal: PC = PC + 2 + memory (signed)
void bne()
{
}
// Branch if Plus: PC = PC + 2 + memory (signed)
void bpl()
{
}
// Break (software IRQ):
// push PC + 2 to stack
// push NV11DIZC flags to stack
// PC = ($FFFE)
void brk()
{
}
// Branch if Overflow Clear: PC = PC + 2 + memory (signed)
void bvc()
{
}
// Branch if Overflow Set: PC = PC + 2 + memory (signed)
void bvs()
{
}
// Clear Carry: C = 0
void clc()
{
}
// Clear Decimal: D = 0
void cld()
{
}
// Clear Interrupt Disable: I = 0
void cli()
{
}
// Clear Overflow: V = 0
void clv()
{
}
// Compare A: A - memory
void cmp()
{
}
// Compare X: X - memory
void cpx()
{
}
// Compate Y: Y-memory
void cpy()
{
}
// Decrement Memory: memory = memory - 1
void dec()
{
}
// Decrement X: X = X - 1
void dex()
{
}
// Decrement Y: Y = Y - 1
void dey()
{
}
// Bitwise Exclusive OR: A = A ^ memory
void eor()
{
}
// Increment Memory: memory = memory + 1
void inc()
{
}
// Increment X: X = X + 1
void inx()
{
}
// Increment Y: Y = Y + 1
void iny()
{
}
// Jump: PC = memory
void jmp()
{
}
// Jump to Subroutine:
// push PC + 2 to stack
// PC = memory
void jsr()
{
}
// Load A: A = memory
void lda()
{
}
// Load X: X = memory
void ldx()
{
}
// Load Y: Y = memory
void ldy()
{
}
// Logical Shift Right: value = value >> 1, or visually: 0 -> [76543210] -> C
void lsr()
{
}
// No Operation: NOP has no effect; it wastes space and CPU cycles.
void nop()
{
}
// Bitwise OR: A = A | memory
void ora()
{
}
// Push A:
//($0100 + SP) = A
// SP = SP - 1
void pha()
{
}
// Push Processor Status:
//($0100 + SP) = NV11DIZC
// SP = SP - 1
void php()
{
}
// Pull A:
// SP = SP + 1
// A = ($0100 + SP)
void pla()
{
}
// Pull Processor Status:
// SP = SP + 1
// NVxxDIZC = ($0100 + SP)
void plp()
{
}
// Rotate Left: value = value << 1 through C, or visually: C <- [76543210] <- C
void rol()
{
}
// Rotate Right: value = value >> 1 through C, or visually: C -> [76543210] -> C
void ror()
{
}
// Return from Interrupt:
// pull NVxxDIZC flags from stack
// pull PC from stack
void rti()
{
}
// Return from Subroutine:
// pull PC from stack
// PC = PC + 1
void rts()
{
}
// Subtract with Carry: A = A - memory - ~C, or equivalently: A = A + ~memory + C
void sbc()
{
}
// Set Carry: C = 1
void sec()
{
}
// Set Decimal: D = 1
void sed()
{
}
// Set Interrupt Disable: I = 1
void sei()
{
}
// Store A: memory = A
void sta()
{
}
// Store X: memory = X
void stx()
{
}
// Store Y: memory = Y
void sty()
{
}
// Transfer A to X: X = A
void tax()
{
}
// Transfer A to Y: Y = A
void tay()
{
}
// Transfer Stack Pointer to X: X = SP
void tsx()
{
}
// Transfer X to A: A = X
void txa()
{
}
// Transfer X to Stack Pointer: SP = X
void txs()
{
}
// Transfer Y to A: A = Y
void tya()
{
}

// Todo implement undocumented opcodes
