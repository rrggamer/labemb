#define MOTOR  23
#define LED    22

void setup()
{
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);
}

void loop()
{
  digitalWrite(MOTOR, HIGH);
  digitalWrite(LED, HIGH);
  delay(5000); // Wait for 5000 millisecond(s)
  digitalWrite(MOTOR, LOW);
  digitalWrite(LED,LOW);
  delay(5000); // Wait for 5000 millisecond(s)

  
}
