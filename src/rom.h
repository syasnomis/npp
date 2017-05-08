#include <fstream>
#include <vector>

#define HEADER_OFFSET 0x10

struct Rom {
public:
  uint32_t getPrgRomSize();
  uint32_t getChrRomSize();
  void loadRom(char* romBuf, std::streampos size);
  void debugPrint();

  uint8_t programPages, charPages, flags6, flags7;
  uint16_t mapperNumber;
  std::string header;
  std::vector<uint8_t> gameRom;

private:
  bool bytesCleared();
  void parseNES2();
  void parseiNES();
  void parseArchaic();
};
