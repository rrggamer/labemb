#define motorPin1 23
#define motorPin2 22
#define motorPin3 19
#define motorPin4 18
int motorSpeed = 4;  // Delay in milliseconds between each step (controls speed)
int rotationTime = 5; // Rotation time in seconds

void setup() {
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);
}

void loop() {
  // Rotate clockwise for `rotationTime` seconds
  rotateStepperByTime(rotationTime, true);
  delay(1000);  // Pause for 1 second before changing direction

  // Rotate counterclockwise for `rotationTime` seconds
  rotateStepperByTime(rotationTime, false);
  delay(1000);  // Pause for 1 second before next loop
}

// Function to rotate the stepper motor for a specific duration (in seconds)
// `timeInSeconds` is the duration of rotation, `clockwise` determines direction
void rotateStepperByTime(int timeInSeconds, bool clockwise) {
  unsigned long startMillis = millis();  // Record the start time
  unsigned long currentMillis;

  // Continue rotating until the specified time has passed
  while (true) {
    currentMillis = millis();
    
    // Stop when the desired time has passed
    if (currentMillis - startMillis >= timeInSeconds * 1000) {
      break;
    }

    // Perform the next step based on the direction
    if (clockwise) {
      step(LOW, LOW, LOW, HIGH);   // Step 1
      step(LOW, LOW, HIGH, LOW);   // Step 2
      step(LOW, HIGH, LOW, LOW);   // Step 3
      step(HIGH, LOW, LOW, LOW);   // Step 4
    } else {
      step(HIGH, LOW, LOW, LOW);   // Step 1
      step(LOW, HIGH, LOW, LOW);   // Step 2
      step(LOW, LOW, HIGH, LOW);   // Step 3
      step(LOW, LOW, LOW, HIGH);   // Step 4
    }
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
