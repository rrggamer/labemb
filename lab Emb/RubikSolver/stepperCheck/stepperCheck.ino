const int dirPins[] = {12, 14, 27, 26, 25, 33};  // Define unique DIR pins
const int stepPins[] = {4, 16, 17, 5, 18, 19};
const int enablePin = 34;   // Define unique STEP pins

void setup() {
  for (int i = 0; i < 6; i++) {
    pinMode(dirPins[i], OUTPUT);
    pinMode(stepPins[i], OUTPUT);

  }
   
   pinMode(enablePin,OUTPUT);
   digitalWrite(enablePin,LOW);

}

void loop() {
  const int steps = 200;       // Steps per cycle
  const int delayMicros = 500; // Microsecond delay between steps
  const int delayMillis = 1000; // Millisecond delay after each move

  for (int motor = 0; motor < 6; motor++) {
    digitalWrite(dirPins[motor], HIGH); // Set direction CW
    for (int i = 0; i < steps; i++) {
      digitalWrite(stepPins[motor], HIGH);
      delayMicroseconds(delayMicros);
      digitalWrite(stepPins[motor], LOW);
      delayMicroseconds(delayMicros);
    }
    delay(delayMillis);

    digitalWrite(dirPins[motor], LOW); // Set direction CCW
    for (int i = 0; i < steps; i++) {
      digitalWrite(stepPins[motor], HIGH);
      delayMicroseconds(delayMicros);
      digitalWrite(stepPins[motor], LOW);
      delayMicroseconds(delayMicros);
    }
    delay(delayMillis);
  }
}
