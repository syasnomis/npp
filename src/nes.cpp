#include <iostream>

#include "nes.h"

void Nes::loadGame(char* romBuf, std::streampos size) {
  game.loadRom(romBuf, size);

  // todo: this assumes mapper 0 only for now, handle others later
  for (uint32_t i = 0; i < game.getPrgRomSize(); ++i) {
    cpu.mem[PRG_ROM_MEM_OFFSET+i] = game.gameRom[HEADER_OFFSET+i];
  }

  // pc reset vector
  cpu.PC = (cpu.mem[0xFFFD] << 8) + cpu.mem[0xFFFC];
}

void Nes::debugPrint() {
  cpu.debugPrint();
  std::cout << std::endl;
  game.debugPrint();
  std::cout<<std::endl;
}

void Nes::start() {
  debugPrint();
  cpu.fdxCycle();
}

