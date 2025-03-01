#include <Arduino.h>

const int dirPins[] = {12, 14, 27, 26, 25, 33};  
const int stepPins[] = {4, 16, 17, 5, 18, 19};

#define STEP_PIN_1  4   // Motor 1 (U)
#define DIR_PIN_1   12    

#define STEP_PIN_2  16   // Motor 2 (R)
#define DIR_PIN_2   14  

#define STEP_PIN_3  17   // Motor 3 (F)
#define DIR_PIN_3   27  

#define STEP_PIN_4  5   // Motor 4 (D)
#define DIR_PIN_4   26  

#define STEP_PIN_5  18  // Motor 5 (L)
#define DIR_PIN_5   25  

#define STEP_PIN_6  19  // Motor 6 (B)
#define DIR_PIN_6   33  

const int enablePin = 34;

void moveMotor(int stepPin, int dirPin, bool clockwise, int steps) {
  digitalWrite(dirPin, clockwise ? HIGH : LOW);
  for (int i = 0; i < steps; i++) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(500);
  }
}

void U(bool prime = false) { moveMotor(STEP_PIN_1, DIR_PIN_1, !prime, 50); }
void R(bool prime = false) { moveMotor(STEP_PIN_2, DIR_PIN_2, !prime, 50); }
void Move_F(bool prime = false) { moveMotor(STEP_PIN_3, DIR_PIN_3, !prime, 50); }
void D(bool prime = false) { moveMotor(STEP_PIN_4, DIR_PIN_4, !prime, 50); }
void L(bool prime = false) { moveMotor(STEP_PIN_5, DIR_PIN_5, !prime, 50); }
void B(bool prime = false) { moveMotor(STEP_PIN_6, DIR_PIN_6, !prime, 50); }

void U2() { U(); U(); }
void R2() { R(); R(); }
void Move_F2() { Move_F(); Move_F(); }
void D2() { D(); D(); }
void L2() { L(); L(); }
void B2() { B(); B(); }

void solveSequence() {
  U();
  delay(2000);

  R();
  delay(2000);

  Move_F();
  
  // delay(2000);
  // D();
  // delay(2000);
  // L();
  // delay(2000);
  // B();
  // delay(2000);
}

void setup() {
  for (int i = 0; i < 6; i++) {
    pinMode(stepPins[i], OUTPUT);
    pinMode(dirPins[i], OUTPUT);
  }

  pinMode(enablePin, OUTPUT);
  digitalWrite(enablePin, LOW);

  delay(1000);
  solveSequence();
}

void loop() {
  // No automatic loop action yet
}
