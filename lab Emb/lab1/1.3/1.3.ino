#define LED     23
#define BUTTON  32

int count = 0;               // Initialize count to 0
bool buttonstate = false;    // Current button state
bool buttonlaststate = true; // Previous button state

void setup() {
  pinMode(BUTTON, INPUT);    // Set the button pin to input mode
  pinMode(LED, OUTPUT);      // Set the LED pin to output mode
  Serial.begin(9600);        // Start serial communication at 9600 baud
}

void loop() {
  buttonstate = digitalRead(BUTTON); // Read the button state         0 1 0
  
  if (buttonstate == LOW) {         // Check if the button is pressed (active LOW)
    digitalWrite(LED, HIGH);
    if (buttonstate != buttonlaststate) { // Detect button state change
      count++; 
      Serial.println(count);         // Print the count to the Serial Monitor
    }
  } else {
    digitalWrite(LED, LOW);         // Turn the LED off
  }
  
  buttonlaststate = buttonstate;    // Update the last button state   1 0 1
}