#include <iostream>

#include "rom.h"

bool Rom::bytesCleared() {
  return !(gameRom[12] || gameRom[13] || gameRom[14] || gameRom[15]);
}

uint32_t Rom::getPrgRomSize() {
  return 16384 * programPages;
}

uint32_t Rom::getChrRomSize() {
  return 8192 * charPages;
}

void Rom::loadRom(char* romBuf, std::streampos size) {
  gameRom.resize(size);
  for (int i = 0; i < size; ++i) {
    gameRom[i] = romBuf[i];
  }

  // parse ROM header
  if (((gameRom[7] & 0xC) == 0x08) && gameRom[9] <= size) {
    parseNES2();
  } else if (((gameRom[7] & 0x0C) == 0x00) && bytesCleared()) {
    parseiNES();
  } else {
    parseArchaic();
  }
}

// Since uint8_t is typedef for char stream interprets it as character to print
// and not the value itself. Cast to unit16_t to ensure value is printed.
void Rom::debugPrint() {
  std::cout << "ROM DEBUG INFO:" << std::endl;
  std::cout << "Header type: " << header << std::endl;
  std::cout << "Rom size in bytes: " << std::dec << gameRom.size() << std::endl;
  std::cout << "Number of 16384 byte program ROM pages: " << static_cast<uint16_t>(programPages) << std::endl;
  std::cout << "Number of 8192 byte character ROM pages: " << static_cast<uint16_t>(charPages) << std::endl;
  std::cout << "Mapper number: " << mapperNumber << std::endl;
  std::cout << "Flags 6: " << std::hex << static_cast<uint16_t>(flags6) << std::endl;
  std::cout << "Flags 7: " << std::hex << static_cast<uint16_t>(flags7) << std::endl;
}

void Rom::parseNES2() {
  header = "NES2.0";
}

void Rom::parseiNES() {
  header = "iNES";
  programPages = gameRom[4];
  charPages = gameRom[5];
  flags6 = gameRom[6];
  flags7 = gameRom[7];
  mapperNumber = (flags7 & 0xF0) | (flags6 >> 4);
}

void Rom::parseArchaic() {
  header = "Archaic iNES";
}
