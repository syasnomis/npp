struct Mmc1 {
  uint8_t SR; // Shift register
  uint8_t loadReg, controlReg;
  uint8_t chrBank0, chrBank1, prgBank;
};
