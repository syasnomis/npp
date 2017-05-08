#include "cpu.h"
#include <iostream>

Cpu::Cpu() {
  P = 0x34; 
  A = X = Y = 0; 
  S = 0xFD; 

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
      std::cout << "PC: " << PC;
      while(1) {
        // loop forever
      }
  }
}
