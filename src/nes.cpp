#include <iostream>

#include "nes.h"

void Nes::loadGame(char* romBuf, std::streampos size) {
  game.loadRom(romBuf, size);
}

void Nes::debugPrint() {
  cpu.debugPrint();
  std::cout << std::endl;
  game.debugPrint();
}

void Nes::start() {
  debugPrint();
}

