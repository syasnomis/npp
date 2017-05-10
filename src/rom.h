#pragma once

#include <fstream>
#include <memory>
#include <vector>

static const uint8_t HEADER_SIZE = 0x10;
static const uint32_t PRG_ROM_PAGE_SIZE = 16384;
static const uint32_t CHR_ROM_PAGE_SIZE = 8192;

struct Rom {
public:
  Rom(char* romBuf, size_t size);
  void debugPrint();

  uint8_t prgPages, chrPages, flags6, flags7;
  uint16_t mapperNumber;
  std::string headerType;
  std::vector<uint8_t> header;
  std::vector<uint8_t> rom;

private:
  bool bytesCleared();
  void parseNES2(const std::vector<uint8_t>& header);
  void parseiNES(const std::vector<uint8_t>& header);
  void parseArchaic(const std::vector<uint8_t>& header);
};
