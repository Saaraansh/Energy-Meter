#include <Arduino.h>
#include <WiFi.h>
#include<chip_detail.h>

uint32_t chipId = 0;
const char* ssid = "airtel_148";
const char* password = "srIshtI@2204";

void Chip()
{
    for(int i=0; i<17; i=i+8) 
    {
	  chipId |= ((ESP.getEfuseMac() >> (40 - i)) & 0xff) << i;
	  }

	  Serial.printf("ESP32 Chip model = %s Rev %d\n", ESP.getChipModel(), ESP.getChipRevision());
    Serial.printf("This chip has %d cores\n", ESP.getChipCores());
    Serial.print("Chip ID: "); 
    Serial.println(chipId);
  
	delay(3000);
}

void MACaddress()
{
  Serial.println();
  Serial.print("ESP Board MAC Address:  ");
  Serial.println(WiFi.macAddress());
}

void IPaddress()
{
  delay(100);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi connected");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}