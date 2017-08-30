#include <Wire.h>
#include "MCP3425.h"

MCP3425::MCP3425(uint8_t addr)
{
  _addr = addr;
  Init(12, 1);
}

void MCP3425::Init(uint8_t bits, uint8_t gain)
{
  if (bits != 12 && bits != 14 && bits != 16) {
    bits = 12;
  }
  _bits = bits;
  if (gain != 1 && gain != 2 && gain != 4 && gain != 8) {
    gain = 1;
  }
  uint8_t gain_bits = 0x00;
  if (gain == 2) {
    gain_bits = 0x01;
  }
  else if (gain == 4) {
    gain_bits = 0x02;
  }
  else if (gain == 8) {
    gain_bits = 0x03;
  }
  _command = 0x80 | gain_bits;
  _delay = 5;
  _gain = 1000.0 * (float)gain;
  if (_bits == 14)  {
    _command = 0x84 | gain_bits;
    _delay = 17;
    _gain = 4000.0 * (float)gain;
  }
  if (_bits == 16)  {
    _command = 0x88 | gain_bits;
    _delay = 67;
    _gain = 16000.0 * (float)gain;
  }
}

float MCP3425::GetVoltage()
{
  Wire.beginTransmission(_addr);
  Wire.write(_command);
  Wire.endTransmission();
  delay(_delay);
  Wire.requestFrom(_addr, (uint8_t)2);
  while (Wire.available() != 2);
  uint8_t data[2];
  for (int i = 0; i < 2; i++) {
    data[i] = Wire.read();
  }
  uint16_t ud = ((uint16_t)data[0] << 8) | (uint16_t)data[1];
  int16_t sd = (int16_t)ud;
  if (_bits == 14) {
    if (ud & 0x2000)  {
      sd = (int16_t)(ud | 0xc000);
    }
    else {
      sd = (int16_t)(ud & 0x3fff);
    }
  }
  else if (_bits == 12) {
    if (ud & 0x0800)  {
      sd = (int16_t)(ud | 0xf000);
    }
    else {
      sd = (int16_t)(ud & 0x0fff);
    }
  }
  return (float)sd / _gain;
}
