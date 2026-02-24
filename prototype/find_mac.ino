#include <WiFi.h>

void setup() {
  Serial.begin(115200);
  delay(1000);

  // Initialize WiFi hardware
  WiFi.mode(WIFI_STA);
  delay(100);  // small delay so hardware starts

  // Get MAC address
  String mac = WiFi.macAddress();

  Serial.println("ESP32 MAC Address:");
  Serial.println(mac);

  // OR: get raw MAC directly from eFuse (most reliable)
  uint64_t chipid = ESP.getEfuseMac();
  Serial.print("ESP32 eFuse MAC: ");
  Serial.printf("%02X:%02X:%02X:%02X:%02X:%02X\n",
                (uint8_t)(chipid >> 40), (uint8_t)(chipid >> 32),
                (uint8_t)(chipid >> 24), (uint8_t)(chipid >> 16),
                (uint8_t)(chipid >> 8), (uint8_t)chipid);
}

void loop() {}
