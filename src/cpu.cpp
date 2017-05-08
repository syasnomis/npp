#include "cpu.h"
#include <iostream>

Cpu::Cpu() {
  P = 0x34;
  A = X = Y = 0;
  S = 0xFD;
}

void Cpu::fdxCycle() {
  switch (PC) {
    case 0x1:
      break;
    default:
      std::cout << "UNIMPLEMTNED OPCODE: " << PC << std::endl;
      while(1) {
        // loop forever
      }
  }
}
