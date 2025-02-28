#define LDR  36
int LDR_Value=0;
int static_variable = 500;

void setup() {
  Serial.begin(9600);
}

void loop() {
  LDR_Value = analogRead(LDR);

  Serial.print("Variable_1:");
  Serial.print(LDR_Value);
  Serial.print(",");
  Serial.print("Variable_2:");
  Serial.println(static_variable);
  delay(20);
}