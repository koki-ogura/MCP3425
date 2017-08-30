#include <Arduino.h>

class MCP3425 {
 private:
  uint8_t _addr;
  uint8_t _bits;
  uint8_t _command;
  uint16_t _delay;
  float _gain;
 public:
  MCP3425(uint8_t addr);
  void Init(uint8_t bits, uint8_t gain);
  float GetVoltage(void);
};
