// Firmware: Aerodyn Receptor
// Designed and Developed by: Akhil P Jacob

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <string.h>   // Required for strcmp and memset

RF24 radio(9, 10); 
const byte address[6] = "00001";

int motorPinLeft1 = 8; 
int motorPinLeft2 = 7; 
int motorPinRight1 = 6; 
int motorPinRight2 = 5; 
int motorPinMiddle1 = 4; 
int motorPinMiddle2 = 2;
int speedControlPin = 3;

int speed = 50; // Speed control (0-255)

char msg_aerodyn_rx[32];   // No need to initialize here

void setup() {
  Serial.begin(9600);

  radio.begin();
  // radio.setRetries(5, 15);
  radio.openReadingPipe(1, address);
  radio.setPALevel(RF24_PA_LOW);
  radio.startListening();   // Receiver mode

  for (int i = 2; i <= 8; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);   // Ensure all motor pins are LOW at startup
  }
}

// ---------------- MOTOR FUNCTIONS ----------------

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

// ---------------- MAIN LOOP ----------------

void loop() {

  if (radio.available()) {

    // Clear buffer before reading
    memset(msg_aerodyn_rx, 0, sizeof(msg_aerodyn_rx));

    radio.read(&msg_aerodyn_rx, sizeof(msg_aerodyn_rx));

    // Ensure null termination
    msg_aerodyn_rx[31] = '\0';

    Serial.print("Received: [");
    Serial.print(msg_aerodyn_rx);
    Serial.println("]");

    if (strcmp(msg_aerodyn_rx, "CMD_FORWARD") == 0) {
      forward();
    }
    else if (strcmp(msg_aerodyn_rx, "CMD_LEFT") == 0) {
      left();
    }
    else if (strcmp(msg_aerodyn_rx, "CMD_RIGHT") == 0) {
      right();
    }
    else if (strcmp(msg_aerodyn_rx, "CMD_ASCEND") == 0) {
      ascend();
    }
    else if (strcmp(msg_aerodyn_rx, "CMD_DESCEND") == 0) {
      descend();
    }
    else if (strcmp(msg_aerodyn_rx, "CMD_STOP") == 0) {
      stop();
    }
  }
}