#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9, 10);  // CE, CSN

const byte address[6] = "00001";

char text[32] = "";
int counter = 0;

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(address);
  radio.openReadingPipe(1, address);
  radio.setPALevel(RF24_PA_LOW);
  radio.startListening();
}

void loop() {

  // ----- RECEIVE -----
//   if (radio.available()) {
//     radio.read(&text, sizeof(text));
//     Serial.print("Received: ");
//     Serial.println(text);
//   }

  // ----- SEND -----
  radio.stopListening();
  sprintf(text, " Aerodyn - %d", counter++);
  radio.write(&text, sizeof(text));
  Serial.println("Message Sent");
  radio.startListening();

  delay(1000);
}