#define LDR  36
#define led 23
int LDR_Value=0;
int static_variable = 500;

void setup() {
  Serial.begin(9600);
  pinMode(led,OUTPUT);
  digitalWrite(led,LOW);
}

void loop() {
  LDR_Value = analogRead(LDR);

  Serial.print("Variable_1:");
  Serial.print(LDR_Value);
  Serial.print(",");
  Serial.print("Variable_2:");
  Serial.println(static_variable);
  delay(20);

//No Hysteresis
 if(LDR_Value < 500){
    digitalWrite(led,HIGH);
  }else{
      digitalWrite(led,LOW);
  }

//Hysteresis
  // if(LDR_Value < 500){
  //   digitalWrite(led,HIGH);
  // }

  // if(LDR_Value > 700){
  //   digitalWrite(led,LOW);
  // }

}