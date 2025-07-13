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

opcode opcode_table[0x100] = {
    // ADC
    [0x69] = {"ADC", 2, 2, &addressing_immediate, &adc},
    [0x65] = {"ADC", 2, 3, &addressing_zero_page, &adc},
    [0x75] = {"ADC", 2, 4, &addressing_zero_page_indexed_x, &adc},
    [0x6D] = {"ADC", 3, 4, &addressing_absolute, &adc},
    [0x7D] = {"ADC", 3, 4, &addressing_absolute_indexed_x, &adc},
    [0x79] = {"ADC", 3, 4, &addressing_absolute_indexed_y, &adc},
    [0x61] = {"ADC", 2, 6, &addressing_indexed_indirect_x, &adc},
    [0x71] = {"ADC", 2, 5, &addressing_indirect_indexed_y, &adc},
    // AND
    [0x29] = {"AND", 2, 2, &addressing_immediate, &and},
    [0x25] = {"AND", 2, 3, &addressing_zero_page, &and},
    [0x35] = {"AND", 2, 4, &addressing_zero_page_indexed_x, &and},
    [0x2D] = {"AND", 3, 4, &addressing_absolute, &and},
    [0x3D] = {"AND", 3, 4, &addressing_absolute_indexed_x, &and},
    [0x39] = {"AND", 3, 4, &addressing_absolute_indexed_y, &and},
    [0x21] = {"AND", 2, 6, &addressing_indexed_indirect_x, &and},
    [0x31] = {"AND", 2, 5, &addressing_indirect_indexed_y, &and},
    // ASL
    [0x0A] = {"ASL", 1, 2, &addressing_accumulator, &asl},
    [0x06] = {"ASL", 2, 5, &addressing_zero_page, &asl},
    [0x16] = {"ASL", 2, 6, &addressing_zero_page_indexed_x, &asl},
    [0x0E] = {"ASL", 3, 6, &addressing_absolute, &asl},
    [0x1E] = {"ASL", 3, 7, &addressing_absolute_indexed_x, &asl},
    // BCC
    [0x90] = {"BCC", 2, 2, &addressing_relative, &bcc},
    // BCS
    [0xB0] = {"BCS", 2, 2, &addressing_relative, &bcs},
    // BEQ
    [0xF0] = {"BEQ", 2, 2, &addressing_relative, &beq},
    // BIT
    [0x24] = {"BIT", 2, 3, &addressing_zero_page, &bit},
    [0x2C] = {"BIT", 3, 4, &addressing_absolute, &bit},
    // BMI
    [0x30] = {"BMI", 2, 2, &addressing_relative, &bmi},
    // BNE
    [0xD0] = {"BNE", 2, 2, &addressing_relative, &bne},
    // BPL
    [0x10] = {"BPL", 2, 2, &addressing_relative, &bpl},
    // BRK
    [0x00] = {"BRK", 2, 7, &addressing_implied, &brk},
    // BVC
    [0x50] = {"BVC", 2, 2, &addressing_relative, &bvc},
    // BVS
    [0x70] = {"BVS", 2, 2, &addressing_relative, &bvs},
    // CLC
    [0x18] = {"CLC", 1, 2, &addressing_implied, &clc},
    // CLD
    [0xD8] = {"CLD", 1, 2, &addressing_implied, &cld},
    // CLI
    [0x58] = {"CLI", 1, 2, &addressing_implied, &cli},
    // CLV
    [0xB8] = {"CLV", 1, 2, &addressing_implied, &clv},
    // CMP
    [0xC9] = {"CMP", 2, 2, &addressing_immediate, &cmp},
    [0xC5] = {"CMP", 2, 3, &addressing_zero_page, &cmp},
    [0xD5] = {"CMP", 2, 4, &addressing_zero_page_indexed_x, &cmp},
    [0xCD] = {"CMP", 3, 4, &addressing_absolute, &cmp},
    [0xDD] = {"CMP", 3, 4, &addressing_absolute_indexed_x, &cmp},
    [0xD9] = {"CMP", 3, 4, &addressing_absolute_indexed_y, &cmp},
    [0xC1] = {"CMP", 2, 6, &addressing_indexed_indirect_x, &cmp},
    [0xD1] = {"CMP", 2, 5, &addressing_indirect_indexed_y, &cmp},
    // CPX
    [0xE0] = {"CPX", 2, 2, &addressing_immediate, &cpx},
    [0xE4] = {"CPX", 2, 3, &addressing_zero_page, &cpx},
    [0xEC] = {"CPX", 3, 4, &addressing_absolute, &cpx},
    // CPY
    [0xC0] = {"CPY", 2, 2, &addressing_immediate, &cpy},
    [0xC4] = {"CPY", 2, 3, &addressing_zero_page, &cpy},
    [0xCC] = {"CPY", 3, 4, &addressing_absolute, &cpy},
    // DEC
    [0xC6] = {"DEC", 2, 5, &addressing_zero_page, &dec},
    [0xD6] = {"DEC", 2, 6, &addressing_zero_page_indexed_x, &dec},
    [0xCE] = {"DEC", 3, 6, &addressing_absolute, &dec},
    [0xDE] = {"DEC", 3, 7, &addressing_absolute_indexed_x, &dec},
    // DEX
    [0xCA] = {"DEX", 1, 2, &addressing_implied, &dex},
    // DEY
    [0x88] = {"DEY", 1, 2, &addressing_implied, &dey},
    // EOR
    [0x49] = {"EOR", 2, 2, &addressing_immediate, &eor},
    [0x45] = {"EOR", 2, 3, &addressing_zero_page, &eor},
    [0x55] = {"EOR", 2, 4, &addressing_zero_page_indexed_x, &eor},
    [0x4D] = {"EOR", 3, 4, &addressing_absolute, &eor},
    [0x5D] = {"EOR", 3, 4, &addressing_absolute_indexed_x, &eor},
    [0x59] = {"EOR", 3, 4, &addressing_absolute_indexed_y, &eor},
    [0x41] = {"EOR", 2, 6, &addressing_indexed_indirect_x, &eor},
    [0x51] = {"EOR", 2, 5, &addressing_indirect_indexed_y, &eor},
    // INC
    [0xE6] = {"INC", 2, 5, &addressing_zero_page, &inc},
    [0xF6] = {"INC", 2, 6, &addressing_zero_page_indexed_x, &inc},
    [0xEE] = {"INC", 3, 6, &addressing_absolute, &inc},
    [0xFE] = {"INC", 3, 7, &addressing_absolute_indexed_x, &inc},
    // INX
    [0xE8] = {"INX", 1, 2, &addressing_implied, &inx},
    // INY
    [0xC8] = {"INY", 1, 2, &addressing_implied, &iny},
    // JMP
    [0x4C] = {"JMP", 3, 3, &addressing_absolute, &jmp},
    [0x6C] = {"JMP", 3, 5, &addressing_indirect, &jmp},
    // JSR
    [0x20] = {"JSR", 3, 6, &addressing_absolute, &jsr},
    // LDA
    [0xA9] = {"LDA", 2, 2, &addressing_immediate, &lda},
    [0xA5] = {"LDA", 2, 3, &addressing_zero_page, &lda},
    [0xB5] = {"LDA", 2, 4, &addressing_zero_page_indexed_x, &lda},
    [0xAD] = {"LDA", 3, 4, &addressing_absolute, &lda},
    [0xBD] = {"LDA", 3, 4, &addressing_absolute_indexed_x, &lda},
    [0xB9] = {"LDA", 3, 4, &addressing_absolute_indexed_y, &lda},
    [0xA1] = {"LDA", 2, 6, &addressing_indexed_indirect_x, &lda},
    [0xB1] = {"LDA", 2, 5, &addressing_indirect_indexed_y, &lda},
    // LDX
    [0xA2] = {"LDX", 2, 2, &addressing_immediate, &ldx},
    [0xA6] = {"LDX", 2, 3, &addressing_zero_page, &ldx},
    [0xB6] = {"LDX", 2, 4, &addressing_zero_page_indexed_y, &ldx},
    [0xAE] = {"LDX", 3, 4, &addressing_absolute, &ldx},
    [0xBE] = {"LDX", 3, 4, &addressing_absolute_indexed_y, &ldx},
    // LDY
    [0xA0] = {"LDY", 2, 2, &addressing_immediate, &ldy},
    [0xA4] = {"LDY", 2, 3, &addressing_zero_page, &ldy},
    [0xB4] = {"LDY", 2, 4, &addressing_zero_page_indexed_x, &ldy},
    [0xAC] = {"LDY", 3, 4, &addressing_absolute, &ldy},
    [0xBC] = {"LDY", 3, 4, &addressing_absolute_indexed_x, &ldy},
    // LSR
    [0x4A] = {"LSR", 1, 2, &addressing_accumulator, &lsr},
    [0x46] = {"LSR", 2, 5, &addressing_zero_page, &lsr},
    [0x56] = {"LSR", 2, 6, &addressing_zero_page_indexed_x, &lsr},
    [0x4E] = {"LSR", 3, 6, &addressing_absolute, &lsr},
    [0x5E] = {"LSR", 3, 7, &addressing_absolute_indexed_x, &lsr},
    // NOP
    [0xEA] = {"NOP", 1, 2, &addressing_implied, &nop},
    // ORA
    [0x09] = {"ORA", 2, 2, &addressing_immediate, &ora},
    [0x05] = {"ORA", 2, 3, &addressing_zero_page, &ora},
    [0x15] = {"ORA", 2, 4, &addressing_zero_page_indexed_x, &ora},
    [0x0D] = {"ORA", 3, 4, &addressing_absolute, &ora},
    [0x1D] = {"ORA", 3, 4, &addressing_absolute_indexed_x, &ora},
    [0x19] = {"ORA", 3, 4, &addressing_absolute_indexed_y, &ora},
    [0x01] = {"ORA", 2, 6, &addressing_indexed_indirect_x, &ora},
    [0x11] = {"ORA", 2, 5, &addressing_indirect_indexed_y, &ora},
    // PHA
    [0x48] = {"PHA", 1, 3, &addressing_implied, &pha},
    // PHP
    [0x08] = {"PHP", 1, 3, &addressing_implied, &php},
    // PLA
    [0x68] = {"PLA", 1, 4, &addressing_implied, &pla},
    // PLP
    [0x28] = {"PLP", 1, 4, &addressing_implied, &plp},
    // ROL
    [0x2A] = {"ROL", 1, 2, &addressing_accumulator, &rol},
    [0x26] = {"ROL", 2, 5, &addressing_zero_page, &rol},
    [0x36] = {"ROL", 2, 6, &addressing_zero_page_indexed_x, &rol},
    [0x2E] = {"ROL", 3, 6, &addressing_absolute, &rol},
    [0x3E] = {"ROL", 3, 7, &addressing_absolute_indexed_x, &rol},
    // ROR
    [0x6A] = {"ROR", 1, 2, &addressing_accumulator, &ror},
    [0x66] = {"ROR", 2, 5, &addressing_zero_page, &ror},
    [0x76] = {"ROR", 2, 6, &addressing_zero_page_indexed_x, &ror},
    [0x6E] = {"ROR", 3, 6, &addressing_absolute, &ror},
    [0x7E] = {"ROR", 3, 7, &addressing_absolute_indexed_x, &ror},
    // RTI
    [0x40] = {"RTI", 1, 6, &addressing_implied, &rti},
    // RTS
    [0x60] = {"RTS", 1, 6, &addressing_implied, &rts},
    // SBC
    [0xE9] = {"SBC", 2, 2, &addressing_immediate, &sbc},
    [0xE5] = {"SBC", 2, 3, &addressing_zero_page, &sbc},
    [0xF5] = {"SBC", 2, 4, &addressing_zero_page_indexed_x, &sbc},
    [0xED] = {"SBC", 3, 4, &addressing_absolute, &sbc},
    [0xFD] = {"SBC", 3, 4, &addressing_absolute_indexed_x, &sbc},
    [0xF9] = {"SBC", 3, 4, &addressing_absolute_indexed_y, &sbc},
    [0xE1] = {"SBC", 2, 6, &addressing_indexed_indirect_x, &sbc},
    [0xF1] = {"SBC", 2, 5, &addressing_indirect_indexed_y, &sbc},
    // SEC
    [0x38] = {"SEC", 1, 2, &addressing_implied, &sec},
    // SED
    [0xF8] = {"SED", 1, 2, &addressing_implied, &sed},
    // SEI
    [0x78] = {"SEI", 1, 2, &addressing_implied, &sei},
    // STA
    [0x85] = {"STA", 2, 3, &addressing_zero_page, &sta},
    [0x95] = {"STA", 2, 4, &addressing_zero_page_indexed_x, &sta},
    [0x8D] = {"STA", 3, 4, &addressing_absolute, &sta},
    [0x9D] = {"STA", 3, 4, &addressing_absolute_indexed_x, &sta},
    [0x99] = {"STA", 3, 4, &addressing_absolute_indexed_y, &sta},
    [0x81] = {"STA", 2, 6, &addressing_indexed_indirect_x, &sta},
    [0x91] = {"STA", 2, 5, &addressing_indirect_indexed_y, &sta},
    // STX
    [0x86] = {"STX", 2, 3, &addressing_zero_page, &stx},
    [0x96] = {"STX", 2, 4, &addressing_zero_page_indexed_y, &stx},
    [0x8E] = {"STX", 3, 4, &addressing_absolute, &stx},
    // STY
    [0x84] = {"STY", 2, 3, &addressing_zero_page, &sty},
    [0x94] = {"STY", 2, 4, &addressing_zero_page_indexed_x, &sty},
    [0x8C] = {"STY", 3, 4, &addressing_absolute, &sty},
    // TAX
    [0xAA] = {"TAX", 1, 2, &addressing_implied, &tax},
    // TAY
    [0xA8] = {"TAY", 1, 2, &addressing_implied, &tay},
    // TSX
    [0xBA] = {"TSX", 1, 2, &addressing_implied, &tsx},
    // TXA
    [0x8A] = {"TXA", 1, 2, &addressing_implied, &txa},
    // TXS
    [0x9A] = {"TXS", 1, 2, &addressing_implied, &txs},
    // TYA
    [0x98] = {"TYA", 1, 2, &addressing_implied, &tya},
};

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
// Instructions like RTS or CLC have no address operand, the destination of results are implied.
void addressing_implied()
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
