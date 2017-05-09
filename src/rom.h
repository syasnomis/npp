#include <fstream>
#include <vector>

static const uint8_t HEADER_OFFSET = 0x10;

struct Rom {
public:
  uint32_t getPrgRomSize();
  uint32_t getChrRomSize();
  void loadRom(char* romBuf, size_t size);
  void debugPrint();

  uint8_t programPages, charPages, flags6, flags7;
  uint16_t mapperNumber;
  std::string header;
  std::vector<uint8_t> gameRom;

private:
  bool bytesCleared();
  void parseNES2(char* romBuf);
  void parseiNES(char* romBuf);
  void parseArchaic(char* romBuf);
};
