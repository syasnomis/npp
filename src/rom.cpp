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

void Rom::loadRom(char* romBuf, size_t size) {
  gameRom.resize(size-HEADER_OFFSET);
  for (size_t i = 0; i < size; ++i) {
    gameRom[i] = romBuf[HEADER_OFFSET+i];
  }

  // parse ROM header
  if (((romBuf[7] & 0xC) == 0x08) && romBuf[9] <= size) {
    parseNES2(romBuf);
  } else if (((romBuf[7] & 0x0C) == 0x00) && bytesCleared()) {
    parseiNES(romBuf);
  } else {
    parseArchaic(romBuf);
  }
}

// Since uint8_t is typedef for char stream operator interprets it as ascii 
// character and not the integer value. Cast to unit16_t to fix this.
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

void Rom::parseNES2(char* romBuf) {
  header = "NES2.0";
  // todo: implement real NES2 header parsing
  programPages = romBuf[4];
  charPages = romBuf[5];
  flags6 = romBuf[6];
  flags7 = romBuf[7];
  mapperNumber = (flags7 & 0xF0) | (flags6 >> 4);

}

void Rom::parseiNES(char* romBuf) {
  header = "iNES";
  programPages = romBuf[4];
  charPages = romBuf[5];
  flags6 = romBuf[6];
  flags7 = romBuf[7];
  mapperNumber = (flags7 & 0xF0) | (flags6 >> 4);
}

void Rom::parseArchaic(char* romBuf) {
  header = "Archaic iNES";
  // todo:: implement res archaic header parsing
  programPages = romBuf[4];
  charPages = romBuf[5];
  flags6 = romBuf[6];
  flags7 = romBuf[7];
  mapperNumber = (flags7 & 0xF0) | (flags6 >> 4);
}
