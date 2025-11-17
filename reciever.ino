#include <esp_now.h>
#include <WiFi.h>

void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  Serial.print("Received: ");
  Serial.write(incomingData, len);
  Serial.println();
}

void setup() {
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK) {
    Serial.println("ESP-NOW init failed");
    return;
  }

  esp_now_register_recv_cb(OnDataRecv);

  Serial.println("ESP32-B Ready (ESP-NOW → Serial)");
}

void loop() {
  // Nothing needed here
}
