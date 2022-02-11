#include <Arduino.h>
#include <zmpt.h>

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  zmptInit(250, 0, 4095, 2047, 34);
}

void loop()
{
  // put your main code here, to run repeatedly:
  zmptTester(10000, 50);
  delay(100);
}