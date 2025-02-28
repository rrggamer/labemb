#define OutPin 23


void setup() {
  
  pinMode(OutPin,OUTPUT);  

}

void loop() {

  digitalWrite(OutPin,HIGH);
  delay(5000);
 
  digitalWrite(OutPin,LOW);
  delay(5000);
}
