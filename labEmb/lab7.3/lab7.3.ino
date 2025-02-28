// the number of the LED pin
const int ledPin = 16;  // 16 corresponds to GPIO16
#define button 17
#define servo 18


// setting PWM properties
const int freq = 1000;
const int freq_servo = 50;
const int resolution = 8;

int dutyCycle_led = 0;
int dutyCycle_servo = 0;
 

int buttoncount_led = 0;
int buttoncount_servo = 1;


bool buttonstate = false;    
bool buttonlaststate = true; 

void setup(){
  // attach the channel to the GPIO to be controlled
  ledcAttach(ledPin, freq, resolution);
  ledcAttach(servo, freq_servo,resolution);
  pinMode(button, INPUT);
  Serial.begin(9600);
  // pinMode(ledPin,OUTPUT);
}
 
void loop(){

  buttonstate = digitalRead(button);  // Update the current button state
  
  if (buttonstate == LOW && buttonstate != buttonlaststate) {
    buttoncount_led++;
    buttoncount_servo++;
  }

  if(buttoncount_led == 6){
    buttoncount_led = 0;
  }

  if(buttoncount_servo == 4){
    buttoncount_servo = 1;
  }

  dutyCycle_led = 51 * buttoncount_led;
  
  if(buttoncount_servo == 1){
    dutyCycle_servo = 13;
  }

   if(buttoncount_servo == 2){
    dutyCycle_servo = 19;
  }

   if(buttoncount_servo == 3){
    dutyCycle_servo = 27;
  }

  ledcWrite(ledPin,dutyCycle_led);
  ledcWrite(servo,dutyCycle_servo);


  // Serial.println(buttoncount_led);
  Serial.println(buttoncount_servo);
  buttonlaststate = buttonstate;


}