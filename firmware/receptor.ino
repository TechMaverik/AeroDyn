#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9, 10);   // CE, CSN
const byte address[6] = "00001";

char text[32] = "";

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(1, address);
  radio.setPALevel(RF24_PA_LOW);
  radio.startListening();   // Receiver mode
}

void loop() {

  if (radio.available()) {
    radio.read(&text, sizeof(text));
    
    if (String(text) == "FORWARD") {
      Serial.println("forward");
      
      // You can trigger motor or LED here
      // digitalWrite(LED_BUILTIN, HIGH);
    }
  }
}