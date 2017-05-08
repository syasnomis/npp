#include <iostream>

#include "cpu.h"

Cpu::Cpu() : A(0), X(0), Y(0), S(0xFD), P(0x34), PC(0) {
  // todo: ensure rom from cart is in mem to ensure correct init of PC
  
  // pc reset vector
  PC = (mem[0xFFFD] << 8) + mem[0xFFFC];
}


void Cpu::fdxCycle() {
  uint8_t opcode = mem[PC];
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
      break;

    default:
      std::cout << "UNIMPLEMENTED OPCODE: " << std::hex << opcode << std::endl;
      std::cout << "PC: " << std::hex << PC;
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
