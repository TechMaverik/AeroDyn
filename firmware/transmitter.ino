//Firmware: Aerodyn Receptor
//Designed and Developed by: Akhil P Jacob
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9, 10); 
const byte address[6] = "00001";

char msg_aerodyn_tx[32] = "";

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_LOW);
  radio.stopListening();   
}

void loop() {

  if (Serial.available()) {
    String input = Serial.readStringUntil('\n');
    input.trim();
    input.toCharArray(msg_aerodyn_tx, 32);
    radio.write(&msg_aerodyn_tx, sizeof(msg_aerodyn_tx));
  }
}