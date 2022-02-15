#include <Arduino.h>
#include <WiFi.h>
#include <chip_detail.h>


void setup() {
  Serial.begin(115200);
  Chip();
  MACaddress();
  IPaddress();
  
}

void loop() {
  // put your main code here, to run repeatedly:

}