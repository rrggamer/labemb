#define Button_Pin   35
#define LED1_Pin     23
#define LED2_Pin     22
 
void IRAM_ATTR IO_INT_ISR()
{
  // Toggle The LED
  digitalWrite(LED2_Pin, !digitalRead(LED2_Pin));
}
 
void setup()
{
  pinMode(LED1_Pin, OUTPUT);
  pinMode(LED2_Pin, OUTPUT);
  pinMode(Button_Pin, INPUT);
  attachInterrupt(Button_Pin, IO_INT_ISR, RISING); // interrupt on rising edge
  digitalWrite(LED1_Pin,LOW);
}
 
void loop()
{
  digitalWrite(LED1_Pin,HIGH);
  delay(1000);
  digitalWrite(LED1_Pin,LOW);
  delay(1000);
}