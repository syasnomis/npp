#include <iostream>

#include "cpu.h"

Cpu::Cpu() : A(0), X(0), Y(0), P(0x34), S(0x01FD), PC(0), cycles(0), ram(RAM_SIZE) {}


void Cpu::fdxCycle() {
  uint8_t opcode = read_byte(PC);
  std::cout << "EXECUTING OPCODE: " << std::hex << static_cast<uint16_t>(opcode) << std::endl << std::endl;
  switch (opcode) {

    // JSR (Jump to subroutine)
    case 0x20:
      {
        auto operand = read_byte2(PC+1);
        write_byte(S, PC+2);
        S -= 1;
        PC = operand;
      }
      cycles += 6;
      break;

    // SEC (Set carry)
    case 0x38:
      P |= 0x01;
      PC += 1;
      cycles += 2;
      break;

    // JMP Absolute
    case 0x4C:
      {
        auto operand = read_byte2(PC+1);
        PC = operand;
      }
      cycles += 3;
      break;

    // ADC Immediate
    case 0x69:
      {
        auto C = P & 0x1;
        auto nn = read_byte(PC+1);
        P &= 0xFE;
        P |= (((A+C+nn) & 0x100) >> 8);
        A = A+C+nn;
      }
      PC += 2;
      // todo: add cycles
      break;

    // SEI (Set Interrupt Disable Flag, bit 2 of P)
    case 0x78:
      P |= 0x04;
      PC += 1;
      cycles += 2;
      break;

    // STX (Store X, Zero page)
    case 0x86:
      {
        auto operand = read_byte(PC+1);
        write_byte(operand, X);
      }
      PC += 2;
      cycles += 3;
      break;

    // STA (Store Accumulator, Absolute addressing mode)
    case 0x8D:
      {
        auto operand = read_byte2(PC+1);
        write_byte(operand, A);
      }
      PC += 3;
      cycles += 4;
      break;

    // LDX (Load X, Immediate addressing mode)
    case 0xA2:
      {
        auto immediate = read_byte(PC+1);
        X = immediate;
        setNegative(immediate);
        setZero(immediate);
      }
      PC += 2;
      cycles += 2;
      break;

    // LDA (Load Accumulator, Immediate addressing mode)
    case 0xA9:
      {
        auto immediate = read_byte(PC+1);
        A = immediate;
        setNegative(immediate);
        setZero(immediate);
      }
      PC += 2;
      cycles += 2;
      break;

    // LDA (Load Accumulator, Absolute addressing mode)
    case 0xAD:
      {
        auto operand = read_byte2(PC+1);
        A = operand;
        setNegative(operand);
        setZero(operand);
      }
      PC += 3;
      cycles += 4;
      break;

    // CLD (Clear Decimal Flag, bit 3 of P)
    case 0xD8:
      P &= ~(0x01 << 3);
      PC += 1;
      cycles += 2;
      break;

    // NOP
    case 0xEA:
      PC += 1;
      cycles += 2;
      break;

    default:
      std::cout << "UNIMPLEMENTED OPCODE: " << std::hex << static_cast<uint16_t>(opcode) << std::endl;
      debugPrint();
      std::cout << std::flush;
      while(1) {
        // loop forever
      }
  }
}

// Since uint8_t is typedef for char stream operator interprets it as ascii 
// character and not the integer value. Cast to unit16_t to fix this.
void Cpu::debugPrint() {
  std::cout << "CPU DEBUG INFO:" << std::endl;
  std::cout << "A:" << std::hex << static_cast<uint16_t>(A) << " ";
  std::cout << "X:" << std::hex << static_cast<uint16_t>(X) << " ";
  std::cout << "Y:" << std::hex << static_cast<uint16_t>(Y) << " ";
  std::cout << "P:" << std::hex << static_cast<uint16_t>(P) << " ";
  std::cout << "S:" << std::hex << static_cast<uint16_t>(S) << " ";
  std::cout << "CYC:" << std::dec << cycles << " ";
  std::cout << "PC:" << std::hex << PC << std::endl;
}

void Cpu::init(const Rom& rom) {
  // todo: init segments of cpu other than banks
  
  // todo: implement initialization for MMC other than NROM
  prgRomBank1 = &rom.rom[0];
  prgRomBank2 = &rom.rom[0];

  //PC = read_byte2(0xFFFC);
  // hardcode PC for cpu nestest
  PC = 0xC000;
}


uint8_t Cpu::read_byte(uint16_t loc) {
  uint8_t byte;
  if (loc < 0x2000) {
    byte = ram[loc%RAM_SIZE];
  } else if (loc < 0x4000) {
    byte = ppuRegisters;
  } else if (loc < 0x4020) {
    byte = registers[loc%NUM_REGISTERS];
  } else if (loc < 0x6000) {
    byte = expansionRom[loc%EXPANSION_ROM_SIZE];
  } else if (loc < 0x8000) {
    byte = sram[loc%SRAM_SIZE];
  } else if (loc < 0xC000) {
    byte = prgRomBank1[loc%PRG_ROM_BANK_SIZE];
  } else {
    byte = prgRomBank2[loc%PRG_ROM_BANK_SIZE];
  }
  return byte;
}

uint16_t Cpu::read_byte2(uint16_t loc) {
  return (read_byte(loc+1) << 8) | read_byte(loc);
}

void Cpu::write_byte(uint16_t loc, uint8_t byte) {
  if (loc < 0x2000) {
    ram[loc%RAM_SIZE] = byte;
  } else if (loc < 0x4000) {
    ppuRegisters = byte;
  } else if (loc < 0x4020) {
    registers[loc%NUM_REGISTERS] = byte;
  } else if (loc > 0x5FFF && loc < 0x8000) {
    sram[loc%SRAM_SIZE] = byte;
  } else {
    std::cout << "WRITE TO ILLEGAL ADDRESS: " << std::hex << loc << std::endl;
    debugPrint();
    while(1) {}
  }
}


void Cpu::setNegative(uint8_t operand) {
  if (operand <= 0x7F) {
    P &= ~(1 << 0x07);
  } else {
    P |= (1 << 0x07);
  }
}

void Cpu::setZero(uint8_t operand) {
  if (!operand) {
    P |= 0x02;
  } else {
    P &= ~(0x02);
  }
}
