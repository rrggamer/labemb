void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(23, OUTPUT);
}// the loop function runs over and over again forever
void loop() {
  digitalWrite(23, HIGH);   // turn the LED on 
  delay(1000);             // wait for a second
  digitalWrite(23, LOW);    // turn the LED off 
  delay(1000);             // wait for a second
}