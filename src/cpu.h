#pragma once

#include <vector>
#include <memory>

#include "rom.h"

static const uint16_t RAM_SIZE = 0x0800;
static const uint16_t NUM_REGISTERS = 0x20;
static const uint16_t EXPANSION_ROM_SIZE = 0x1FDF;
static const uint16_t SRAM_SIZE = 0x2000;
static const uint16_t PRG_ROM_BANK_SIZE = 0x4000;

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
  std::vector<uint8_t*> mem;

  std::vector<uint8_t> ram;
  uint8_t ppuRegisters;
  std::vector<uint8_t> registers;
  std::vector<uint8_t> expansionRom;
  std::vector<uint8_t> sram;
  
  const uint8_t* prgRomBank1;
  const uint8_t* prgRomBank2;

  Cpu();

  // fetch, decode, execute cycle
  void fdxCycle();

  void debugPrint();

  void init(const Rom& rom);

  uint8_t read_byte(uint16_t loc); // read a single byte
  uint16_t read_byte2(uint16_t loc); // little endian aware read of two bytes

  void write_byte(uint16_t loc, uint8_t byte);

  private:
    void setNegative(uint8_t operand); // set bit 7 of P iff operand < 0
    void setZero(uint8_t operand); // set bit 1 of P iff operand == 0

};
