#include <Arduino.h>

// const int stepPins[] = {4, 16, 17, 5, 18, 19};
// const int dirPins[] = {12, 14, 27, 26, 25, 33};  

const int stepPins[] = {33, 19, 26, 5, 14, 16};
const int dirPins[] = {25, 18, 27, 17, 12, 4};  


#define STEP_PIN_1  33   // Motor 1 (U)
#define DIR_PIN_1   25    

#define STEP_PIN_2  19   // Motor 2 (R)
#define DIR_PIN_2   18  

#define STEP_PIN_3  26   // Motor 3 (F)
#define DIR_PIN_3   27  

#define STEP_PIN_4  5   // Motor 4 (D)
#define DIR_PIN_4   17  

#define STEP_PIN_5  14  // Motor 5 (L)
#define DIR_PIN_5   12  

#define STEP_PIN_6  16  // Motor 6 (B)
#define DIR_PIN_6   4  

const int enable_motor5 = 35;

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
  delay(2000);
  
  D();
  delay(2000);
  
  digitalWrite(enable_motor5, LOW);

  L();
  delay(2000);
  
  B();
  delay(2000);


  B(true);
  delay(2000);

  L(true);
  delay(2000);

  digitalWrite(enable_motor5, HIGH);


  D(true);
  delay(2000);

  Move_F(true);
  delay(2000);

  R(true);
  delay(2000);

  U(true);
  delay(2000);

}

void setup() {

  delay(3000);
  
  for (int i = 0; i < 6; i++) {
    pinMode(stepPins[i], OUTPUT);
    pinMode(dirPins[i], OUTPUT);
  }

  pinMode(enable_motor5, OUTPUT);
  digitalWrite(enable_motor5, HIGH);

  delay(1000);
  solveSequence();
}

void loop() {
  // No automatic loop action yet
}
