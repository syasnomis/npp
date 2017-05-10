#include <iostream>

#include "rom.h"

bool Rom::bytesCleared() {
  return !(header[12] || header[13] || header[14] || header[15]);
}

Rom::Rom(char* romBuf, size_t size) {

  // copy header from headerfer
  for (int i = 0; i < HEADER_SIZE; ++i) {
    header.push_back(romBuf[i]);
  }
  // parse ROM header
  if (((header[7] & 0xC) == 0x08) && header[9] <= size) {
    parseNES2(header);
  } else if (((header[7] & 0x0C) == 0x00) && bytesCleared()) {
    parseiNES(header);
  } else {
    parseArchaic(header);
  }

  // at this point header related vars should be intialized
  for (size_t i = HEADER_SIZE; i < size; i++) {
    rom.push_back(romBuf[i]);
  }
}

// Since uint8_t is typedef for char stream operator interprets it as ascii 
// character and not the integer value. Cast to unit16_t to fix this.
void Rom::debugPrint() {
  std::cout << "ROM DEBUG INFO:" << std::endl;
  std::cout << "Header type: " << headerType << std::endl;
  std::cout << "Rom size in bytes: " << std::dec << header.size() << std::endl;
  std::cout << "Number of 16384 byte program ROM pages: " << static_cast<uint16_t>(prgPages) << std::endl;
  std::cout << "Number of 8192 byte character ROM pages: " << static_cast<uint16_t>(chrPages) << std::endl;
  std::cout << "Mapper number: " << mapperNumber << std::endl;
  std::cout << "Flags 6: " << std::hex << static_cast<uint16_t>(flags6) << std::endl;
  std::cout << "Flags 7: " << std::hex << static_cast<uint16_t>(flags7) << std::endl;
}

void Rom::parseNES2(const std::vector<uint8_t>& header) {
  headerType = "NES2.0";
  // todo: implement real NES2 header parsing
  prgPages = header[4];
  chrPages = header[5];
  flags6 = header[6];
  flags7 = header[7];
  mapperNumber = (flags7 & 0xF0) | (flags6 >> 4);

}

void Rom::parseiNES(const std::vector<uint8_t>& header) {
  headerType = "iNES";
  prgPages = header[4];
  chrPages = header[5];
  flags6 = header[6];
  flags7 = header[7];
  mapperNumber = (flags7 & 0xF0) | (flags6 >> 4);
}

void Rom::parseArchaic(const std::vector<uint8_t>& header) {
  headerType = "Archaic iNES";
  // todo:: implement res archaic header parsing
  prgPages = header[4];
  chrPages = header[5];
  flags6 = header[6];
  flags7 = header[7];
  mapperNumber = (flags7 & 0xF0) | (flags6 >> 4);
}
