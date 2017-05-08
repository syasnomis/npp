#include <vector>

#define CPU_MEM_SIZE 65536
#define PRG_ROM_MEM_OFFSET 0x8000

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
  uint8_t A, X, Y, S, P; 
  uint16_t PC; 
  std::vector<uint8_t> mem;

  Cpu();

  // fetch, decode, execute cycle
  void fdxCycle();

  void debugPrint();

};
