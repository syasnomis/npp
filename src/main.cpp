#include <fstream>
#include <iostream>

#include "nes.h"

using namespace std;

int main(int argc, char* argv[]) {

  if (argc <= 1) {
    cout << "Wrong number of args" << endl;
    return 1;
  }

  ifstream rom;
  rom.open(argv[1], ios::in|ios::binary|ios::ate);
  streampos size;
  char* gameBuf;

  if (rom.is_open()) {
    size = rom.tellg();
    gameBuf = new char[size];
    rom.seekg(0, ios::beg);
    rom.read(gameBuf, size);
    rom.close();
  } else {
    cout << "Error trying to open rom file." << endl;
    return 1;
  }

  Nes nes(gameBuf, size);
  delete[] gameBuf;
  nes.start();

  return 0;
}
