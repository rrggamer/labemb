#define motorPin1 23
#define motorPin2 22
#define motorPin3 19
#define motorPin4 18

int motorSpeed = 4;  // Delay in milliseconds between each step (controls speed)
int stepsPerLetter = 20; // Number of steps between each letter position
int currentPosition = 0; // Tracks the current position of the motor in steps

void setup() {
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);

  Serial.begin(9600);  // Initialize serial communication
}

void loop() {
  if (Serial.available()) {
    char input = Serial.read();  // Read input from keyboard
    input = toupper(input);      // Convert to uppercase for consistency
    Serial.println(input);       // Echo the input

    if (input >= 'A' && input <= 'Z') {
      int targetPosition = (input - 'A') * stepsPerLetter; // Map letter to steps
      moveToPosition(targetPosition);
      
    } else {
      Serial.println("Invalid input. Please enter a letter (A-Z).");
    }
  }

  Serial.println(currentPosition);
}

// Function to move the motor to the target position
void moveToPosition(int targetPosition) {
  int totalSteps = 26 * stepsPerLetter;  // Total steps in a full circle (A-Z loop)
  int counterclockwiseSteps = (targetPosition - currentPosition + totalSteps) % totalSteps;
  int clockwiseSteps = (currentPosition - targetPosition + totalSteps) % totalSteps;

  if (counterclockwiseSteps <= clockwiseSteps) {
    stepCounterClockwise(counterclockwiseSteps);
  } else {
    stepClockwise(clockwiseSteps);
  }

  currentPosition = targetPosition; // Update the current position
}


// Function to move the motor clockwise by a number of steps
void stepClockwise(int steps) {
  for (int i = 0; i < steps; i++) {
    step(1, 0, 0, 0);
    step(1, 1, 0, 0);
    step(0, 1, 0, 0);
    step(0, 1, 1, 0);
    step(0, 0, 1, 0);
    step(0, 0, 1, 1);
    step(0, 0, 0, 1);
    step(1, 0, 0, 1);
  }
}

// Function to move the motor counterclockwise by a number of steps
void stepCounterClockwise(int steps) {
  for (int i = 0; i < steps; i++) {
    step(1, 0, 0, 1);
    step(0, 0, 0, 1);
    step(0, 0, 1, 1);
    step(0, 0, 1, 0);
    step(0, 1, 1, 0);
    step(0, 1, 0, 0);
    step(1, 1, 0, 0);
    step(1, 0, 0, 0);
  }
}

// Helper function to set the stepper motor pins for one step
void step(int pin1, int pin2, int pin3, int pin4) {
  digitalWrite(motorPin1, pin1);
  digitalWrite(motorPin2, pin2);
  digitalWrite(motorPin3, pin3);
  digitalWrite(motorPin4, pin4);
  delay(motorSpeed);  // Control speed by adjusting this delay
}
