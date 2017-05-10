#pragma once

#include <fstream>

#include "cpu.h"
#include "rom.h"

class Nes {
  public:
    Nes(char* romBuf, size_t size);
    void start();

  private:
    Cpu cpu;
    Rom rom;

    void debugPrint();
};
