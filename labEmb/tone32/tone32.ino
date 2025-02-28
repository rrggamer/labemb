#define Buzzer 21
#define Button 35

#define C6 477
#define D6 426
#define E6 379
#define F6 358
#define G6 319
#define A6 284
#define B6 253
 
volatile int FAST_NOTE = 200;
volatile int NOTE_DURATION = 400;       
volatile int HALF_NOTE_DURATION = 800;  
volatile int EIGHTH_NOTE_DURATION = 200; 
volatile int PAUSE_DURATION = 100;  
int Speed = 0;

int buttoncount = 0;


unsigned long lastDebounceTime = 0;  // the last time the button input was toggled
unsigned long debounceDelay = 50;    // debounce delay in milliseconds


hw_timer_t *My_timer = NULL;
volatile bool buzzerState = false;

// Interrupt Service Routine (ISR)
void IRAM_ATTR onTimer() {
    digitalWrite(Buzzer, buzzerState);
    buzzerState = !buzzerState;
}

void IRAM_ATTR buttonISR() {
    unsigned long currentTime = millis();
    if (currentTime - lastDebounceTime > debounceDelay) {
        if (digitalRead(Button) == LOW) {
            buttoncount = (buttoncount + 1) % 5;  // Loop from 0 to 4
        }
        lastDebounceTime = currentTime;
    }
    
    Serial.println(buttoncount);
    Speed = 20 * buttoncount;

    FAST_NOTE = max(50, 200 - Speed);  // Prevents negative or too fast
    NOTE_DURATION = max(100, 400 - Speed);
    PAUSE_DURATION = max(50, 100 - Speed);
}



// Function to generate a tone with a given frequency
void tone(int frequency) {
    My_timer = timerBegin(1000000); // Initialize timer with the desired frequency
    timerAttachInterrupt(My_timer, &onTimer); // Attach ISR
    timerAlarm(My_timer, frequency, true, 0);
}

// Function to stop the tone
void noTone() {
    if (My_timer != NULL) {
        timerEnd(My_timer); // End the timer
        My_timer = NULL;
    }
    digitalWrite(Buzzer, LOW); // Ensure buzzer is off
}

void setup() {
  
  Serial.begin(9600);
  pinMode(Buzzer, OUTPUT);
  digitalWrite(Buzzer, LOW);
  pinMode(Button, INPUT);


 attachInterrupt(digitalPinToInterrupt(Button), buttonISR, CHANGE);
   
}

void loop() {

tone(C6);
delay(FAST_NOTE);
noTone();
delay(PAUSE_DURATION);

tone(C6);
delay(FAST_NOTE);
noTone();
delay(PAUSE_DURATION);

tone(D6);
delay(NOTE_DURATION);
noTone();
delay(PAUSE_DURATION);

tone(C6);
delay(NOTE_DURATION);
noTone();
delay(PAUSE_DURATION);

tone(F6);
delay(NOTE_DURATION);
noTone();
delay(PAUSE_DURATION);

tone(E6);
delay(HALF_NOTE_DURATION);
noTone();
delay(PAUSE_DURATION);

tone(C6);
delay(FAST_NOTE);
noTone();
delay(PAUSE_DURATION);

tone(C6);
delay(FAST_NOTE);
noTone();
delay(PAUSE_DURATION);

tone(D6);
delay(NOTE_DURATION);
noTone();
delay(PAUSE_DURATION);

tone(C6);
delay(NOTE_DURATION);
noTone();
delay(PAUSE_DURATION);

tone(G6);
delay(NOTE_DURATION);
noTone();
delay(PAUSE_DURATION);

tone(F6);
delay(HALF_NOTE_DURATION);
noTone();
delay(PAUSE_DURATION);

    // Pause before replaying
    delay(2000);
    

}
