#include <fstream>
#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {

  if (argc <= 1) {
    cout << "Wrong number of args" << endl;
    return 1;
  }

  ifstream rom;
  rom.open(argv[1], ios::in|ios::binary|ios::ate);
  streampos size;
  char* memblock;

  if (rom.is_open()) {
    size = rom.tellg();
    cout << "Rom size: " << size << endl;
    memblock = new char[size];
    rom.seekg(0, ios::beg);
    rom.read(memblock, size);
    rom.close();
    cout << "rom read into memory" << endl;

    for (int i = 0; i < size; ++i) {
      //cout << memblock[i];
    }
  }
  return 0;
}
