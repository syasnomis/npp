#include <iostream>

#include "nes.h"

Nes::Nes(char* romBuf, size_t size) : rom(romBuf, size) {
  cpu.init(rom);
}

void Nes::debugPrint() {
  cpu.debugPrint();
  std::cout << std::endl;
  rom.debugPrint();
  std::cout<<std::endl;
}

void Nes::start() {
  std::cout << "START STATE:" << std::endl;
  debugPrint();
  while (1) {
    cpu.debugPrint();
    cpu.fdxCycle();
  }
}

