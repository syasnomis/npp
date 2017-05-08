#include <fstream>

#include "cpu.h"
#include "rom.h"

class Nes {
  public:
    void loadGame(char *romBuf, std::streampos size);
    void start();

  private:
    Cpu cpu;
    Rom game;

    void debugPrint();
};
