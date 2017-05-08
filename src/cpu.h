#include <cstdint>

struct Cpu {
  uint8_t A, X, Y, S, P; 
  uint16_t PC; 

  Cpu();

  // fetch, decode, execute cycle
  void fdxCycle();

  // opcodes named by instruction mnemonics
  void ADC();
  void AND();
  void ASL();
  void BIT();
  void BPL();
  void BMI();
  void BVC();
  void BCC();
  void BCS();
  void BNE();
  void BEQ();
  void BRK();
};
