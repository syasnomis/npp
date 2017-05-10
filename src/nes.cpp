#include <iostream>

#include "nes.h"

void Nes::loadGame(char* romBuf, size_t size) {
  game.loadRom(romBuf, size);

  // todo: this assumes mapper 0 only for now, handle others later
  for (uint32_t i = 0; i < 0x4000; ++i) {
    // read 32kB from rom, mirroring in memory 0x4000 spots down
    cpu.mem[PRG_ROM_MEM_OFFSET+i] = game.gameRom[i];
    cpu.mem[PRG_ROM_MEM_OFFSET+0x4000+i] = game.gameRom[i];
  }

  // pc reset vector
  //cpu.PC = (cpu.mem[0xFFFD] << 8) + cpu.mem[0xFFFC];
  // harcoded reset vector for nestest rom automatic mode
  cpu.PC = 0xC000;
}

void Nes::debugPrint() {
  cpu.debugPrint();
  std::cout << std::endl;
  game.debugPrint();
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

