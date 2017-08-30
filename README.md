# mcp3425 adc library for arduino

# sample program
```
#include <stdio.h>
#include <Wire.h>
#include <MCP3425.h>

#define SDA 21
#define SCL 22

MCP3425 mcp3425(0x68);

void setup() {
  // Serial init
  Serial.begin(115200);

  // i2c init
  Serial.println("Init i2c...");
  Wire.begin(SDA, SCL);
  // init mcp3425 with 16bit, 1x
  mcp3425.Init(16, 1);
}

void loop() {
  // Get voltage from mcp3425
  float v = mcp3425.GetVoltage();
  Serial.println(v);
  delay(1000);
}
```
