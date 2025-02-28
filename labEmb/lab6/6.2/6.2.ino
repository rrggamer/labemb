#define Buzzer 21
hw_timer_t *My_timer = NULL;

int buzzer_freq = 420;

void IRAM_ATTR onTimer(){
  digitalWrite(Buzzer, !digitalRead(Buzzer));
}

void setup() {
  pinMode(Buzzer, OUTPUT);

  My_timer = timerBegin(1000000);  
  timerAttachInterrupt(My_timer, &onTimer); // point to the ISR
  timerAlarm(My_timer, 1190, true, 0);  // set alarm every 1 sec
  
}

void loop() {

}