#include <vector>

static const uint32_t CPU_MEM_SIZE = 65536;
static const uint32_t PRG_ROM_MEM_OFFSET = 0x8000;

/**
 * Data structure emulating NES CPU core (mos 6502)
 * Register mapping:
 * A = Accumulator
 * X, Y = General purpose registers
 * S = Stack pointer
 * P = Status register
 * PC = Program counter
 */

struct Cpu {
  uint8_t A, X, Y, P; 
  uint16_t S, PC; 
  uint16_t cycles;
  std::vector<uint8_t> mem;

  Cpu();

  // fetch, decode, execute cycle
  void fdxCycle();

  void debugPrint();

  private:
    void setNegative(uint8_t operand); // set bit 7 of P iff operand < 0
    void setZero(uint8_t operand); // set bit 1 of P iff operand == 0

};
