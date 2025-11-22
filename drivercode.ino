// Motor pins on D1 Mini
#define M1 D8
#define M2 D7
#define M3 D6
#define M4 D5

void setup() {
  // Set all pins as OUTPUT
  pinMode(M1, OUTPUT);
  pinMode(M2, OUTPUT);
  pinMode(M3, OUTPUT);
  pinMode(M4, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);

  // Start motors OFF
  digitalWrite(M1, LOW);
  digitalWrite(M2, LOW);
  digitalWrite(M3, LOW);
  digitalWrite(M4, LOW);
}

void loop() {
  // Turn all motors ON
  digitalWrite(M1, HIGH);
  digitalWrite(M2, LOW);
  digitalWrite(M3, HIGH);
  digitalWrite(M4, LOW);
  pinMode(LED_BUILTIN, HIGH);

  delay(1000); // Run for 2 seconds
  pinMode(LED_BUILTIN, LOW);
  delay(1000);


}
