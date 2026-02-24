#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9, 10);   // CE, CSN
const byte address[6] = "00001";

char text[32] = "";

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_LOW);
  radio.stopListening();   // Transmitter mode
}

void loop() {

  if (Serial.available()) {
    String input = Serial.readStringUntil('\n');
    input.trim();

    if (input == "FORWARD") {
      input.toCharArray(text, 32);
      radio.write(&text, sizeof(text));
      Serial.println("Sent: FORWARD");
    }
  }
}