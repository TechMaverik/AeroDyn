//Firmware: Aerodyn Receptor
//Designed and Developed by: Akhil P Jacob
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9, 10); 
const byte address[6] = "00001";

int motorPinLeft1 = 8; 
int motorPinLeft2 = 7; 
int motorPinRight1 = 6; 
int motorPinRight2 = 5; 
int motorPinMiddle1 = 4; 
int motorPinMiddle2 = 2;
int speedControlPin = 3;
int speed=90; // Speed control (0-255)

char msg_aerodyn_rx[32] = "";

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(1, address);
  radio.setPALevel(RF24_PA_LOW);
  radio.startListening();   // Receiver mode
  for (int i = 2; i <= 8; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW); // Ensure all motor pins are LOW at startup
  }
}

void forward() {
  digitalWrite(motorPinLeft1, HIGH);
  digitalWrite(motorPinLeft2, LOW);
  digitalWrite(motorPinRight1, HIGH);
  digitalWrite(motorPinRight2, LOW);
  analogWrite(speedControlPin, speed); 
}

void left() {
  digitalWrite(motorPinLeft1, LOW);
  digitalWrite(motorPinLeft2, HIGH);
  digitalWrite(motorPinRight1, HIGH);
  digitalWrite(motorPinRight2, LOW);
  analogWrite(speedControlPin, speed); 
}

void right() {
  digitalWrite(motorPinLeft1, HIGH);
  digitalWrite(motorPinLeft2, LOW);
  digitalWrite(motorPinRight1, LOW);
  digitalWrite(motorPinRight2, HIGH);
  analogWrite(speedControlPin, speed); 
}

void ascend() {
  digitalWrite(motorPinMiddle1, HIGH);
  digitalWrite(motorPinMiddle2, LOW);
  analogWrite(speedControlPin, speed); 
}

void descend() {
  digitalWrite(motorPinMiddle1, LOW);
  digitalWrite(motorPinMiddle2, HIGH);
  analogWrite(speedControlPin, speed); 
}

void stop() {
  for (int i = 2; i <= 8; i++) {
    digitalWrite(i, LOW);
  }
}

void loop() {

  if (radio.available()) {
    radio.read(&msg_aerodyn_rx, sizeof(msg_aerodyn_rx));
    
    if (String(msg_aerodyn_rx) == "CMD_FORWARD") {
      forward();
    } else if (String(msg_aerodyn_rx) == "CMD_LEFT") {
      left();
    } else if (String(msg_aerodyn_rx) == "CMD_RIGHT") {
      right();
    } else if (String(msg_aerodyn_rx) == "CMD_ASCEND") {
      ascend();
    } else if (String(msg_aerodyn_rx) == "CMD_DESCEND") {
      descend();
    } else if (String(msg_aerodyn_rx) == "CMD_STOP") {
      stop();
    }
  }
}