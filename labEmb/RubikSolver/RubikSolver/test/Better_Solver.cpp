#include <Arduino.h>

// Stepper Motor Pin Definitions
const int stepPins[] = {32, 19, 26, 5, 14, 16};
const int dirPins[] = {25, 18, 27, 17, 12, 4};  

// Motor enable pin (optional)
const int enable_motor5 = 35;

// Enum for Moves
enum MoveType { 
  U, R, F, D, L, B, 
  U_PRIME, R_PRIME, F_PRIME, D_PRIME, L_PRIME, B_PRIME, 
  U2, R2, F2, D2, L2, B2 
};

// Move Execution Function
void moveMotor(int stepPin, int dirPin, bool clockwise, int steps) {
  digitalWrite(dirPin, clockwise ? HIGH : LOW);
  for (int i = 0; i < steps; i++) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(500);
  }
}

// Individual Move Functions
void U(bool prime = false) { moveMotor(32, 25, !prime, 50); }
void R(bool prime = false) { moveMotor(19, 18, !prime, 50); }
void Move_F(bool prime = false) { moveMotor(26, 27, !prime, 50); }
void D(bool prime = false) { moveMotor(5, 17, !prime, 50); }
void L(bool prime = false) { moveMotor(14, 12, !prime, 50); }
void B(bool prime = false) { moveMotor(16, 4, !prime, 50); }

// Executes a move based on the enum type
void executeMove(MoveType move) {
  switch (move) {
    case U:        U(); break;
    case R:        R(); break;
    case F:        Move_F(); break;
    case D:        D(); break;
    case L:        L(); break;
    case B:        B(); break;
    case U_PRIME:  U(true); break;
    case R_PRIME:  R(true); break;
    case F_PRIME:  Move_F(true); break;
    case D_PRIME:  D(true); break;
    case L_PRIME:  L(true); break;
    case B_PRIME:  B(true); break;
    case U2:       U(); U(); break;
    case R2:       R(); R(); break;
    case F2:       Move_F(); Move_F(); break;
    case D2:       D(); D(); break;
    case L2:       L(); L(); break;
    case B2:       B(); B(); break;
  }
}

// Structure for Move Sequences (Supports Multi-Step Moves)
struct Move {
  MoveType move;
  int count;  // How many times to execute the move
};

// Solve Sequence Function
void solveSequence() {
  Move sequence[] = {
    {U, 1}, {R, 1}, {F, 1}, {D, 1}, {L, 1}, {B, 1},  // Basic moves
    {B_PRIME, 1}, {L_PRIME, 1}, {D_PRIME, 1}, {F_PRIME, 1}, {R_PRIME, 1}, {U_PRIME, 1}, // Prime moves
    {U, 2}, {R, 2}, {F, 2}  // Double moves
  };

  int sequenceLength = sizeof(sequence) / sizeof(sequence[0]);

  for (int i = 0; i < sequenceLength; i++) {
    for (int j = 0; j < sequence[i].count; j++) {
      executeMove(sequence[i].move);
      delay(100);  // Small delay between moves
    }
  }
}

// Setup Function
void setup() {
  delay(1000);

  for (int i = 0; i < 6; i++) {
    pinMode(stepPins[i], OUTPUT);
    pinMode(dirPins[i], OUTPUT);
  }

  // Optional: Enable motors
  pinMode(enable_motor5, OUTPUT);
  digitalWrite(enable_motor5, HIGH);

  delay(1000);

  // Run the solving sequence
  solveSequence();
}

// Loop Function (Unused for now)
void loop() {
  // Leave empty or implement additional logic
}
