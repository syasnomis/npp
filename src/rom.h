#include <fstream>
#include <vector>

class Rom {
public:
  void loadRom(char* romBuf, std::streampos size);
  void debugPrint();

private:
  bool bytesCleared();
  void parseNES2();
  void parseiNES();
  void parseArchaic();

  uint8_t programPages, charPages, flags6, flags7;
  uint16_t mapperNumber;
  std::string header;
  std::vector<uint8_t> gameRom;
};
