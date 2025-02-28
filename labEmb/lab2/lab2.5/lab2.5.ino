#define enable 23
#define input1 22
#define input2 19


void setup() {
  pinMode(input1,OUTPUT);
  pinMode(input2,OUTPUT);
  pinMode(enable,OUTPUT);
  digitalWrite(enable,HIGH);
}

void loop() {
  
  digitalWrite(input1,HIGH);
  digitalWrite(input2,LOW);
  delay(5000);
  digitalWrite(input2,HIGH);
  digitalWrite(input1,LOW);
  delay(5000);

}
