#define CPU_MEM_SIZE 65536

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
  uint8_t mem[CPU_MEM_SIZE];

  Cpu();

  // fetch, decode, execute cycle
  void fdxCycle();

  void debugPrint();

};
