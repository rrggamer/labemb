#include <AccelStepper.h>

// Define motor pins
#define DIR_PIN 12
#define STEP_PIN 14
#define ENABLE_PIN 27

// Stepper motor setup: 1 = Driver mode
AccelStepper stepper(1, STEP_PIN, DIR_PIN);

void setup() {
  pinMode(ENABLE_PIN, OUTPUT);
  digitalWrite(ENABLE_PIN, LOW); // Enable the driver

  stepper.setMaxSpeed(1000);      // Max speed (steps/sec)
  stepper.setAcceleration(500);   // Acceleration (steps/sec²)
  stepper.setSpeed(500);          // Initial speed (steps/sec)
}

void loop() {
  stepper.move(200);  // Move 200 steps (1 full rotation for 1.8° step motor)
  stepper.runToPosition();  // Blocking call (wait until done)

  delay(1000);  // Wait 1 second

  stepper.move(-200);  // Move back
  stepper.runToPosition();

  delay(1000);
}
