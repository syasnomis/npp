#include <iostream>

#include "cpu.h"

Cpu::Cpu() : A(0), X(0), Y(0), S(0xFD), P(0x34), PC(0), cycles(0) {
  mem.resize(CPU_MEM_SIZE);
  // todo: ensure rom from cart is in mem to ensure correct init of PC
}


void Cpu::fdxCycle() {
  uint8_t opcode = mem[PC];
  std::cout << "EXECUTING OPCODE: " << std::hex << static_cast<uint16_t>(opcode) << std::endl << std::endl;
  switch (opcode) {

    // ADC Immediate
    case 0x69:
      {
        auto C = P & 0x1;
        auto nn = mem[PC+1];
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

    // STA (Store Accumulator, Absolute addressing mode)
    case 0x8D:
      {
        auto operand = (mem[PC+2] << 8) | mem[PC+1];
        mem[operand] = A;
      }
      PC += 3;
      cycles += 4;
      break;

    // LDX (Load X, Immediate addressing mode)
    case 0xA2:
      {
        auto immediate = mem[PC+1];
        X = immediate;
        setNegative(immediate);
        setZero(immediate);
      }
      PC += 2;
      cycles += 2;

    // CLD (Clear Decimal Flag, bit 3 of P)
    case 0xD8:
      P &= ~(0x01 << 3);
      PC += 1;
      cycles += 2;
      break;

    // LDA (Load Accumulator, Immediate addressing mode)
    case 0xA9:
      {
        auto immediate = mem[PC+1];
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
        auto operand = (mem[PC+2] << 8) | mem[PC+1];
        A = operand;
        setNegative(operand);
        setZero(operand);
      }
      PC += 3;
      cycles += 4;
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

// Since uint8_t is typedef for char stream interprets it as character to print
// and not the value itself. Cast to unit16_t to ensure value is printed.
void Cpu::debugPrint() {
  std::cout << "CPU DEBUG INFO:" << std::endl;
  std::cout << "P: " << std::hex << static_cast<uint16_t>(P) << std::endl;
  std::cout << "X: " << std::hex << static_cast<uint16_t>(X) << std::endl;
  std::cout << "Y: " << std::hex << static_cast<uint16_t>(Y) << std::endl;
  std::cout << "A: " << std::hex << static_cast<uint16_t>(A) << std::endl;
  std::cout << "S: " << std::hex << static_cast<uint16_t>(S) << std::endl;
  std::cout << "PC: " << std::hex << PC << std::endl;
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
