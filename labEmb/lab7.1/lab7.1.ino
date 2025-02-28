// the number of the LED pin
const int ledPin = 16;  // 16 corresponds to GPIO16
#define button 17
// setting PWM properties
const int freq = 1000;
const int resolution = 8;
int dutyCycle = 0;
 

int buttoncount = 0;


bool buttonstate = false;    
bool buttonlaststate = true; 

void setup(){
  // attach the channel to the GPIO to be controlled
  ledcAttach(ledPin, freq, resolution);
  pinMode(button, INPUT);
  Serial.begin(9600);
  // pinMode(ledPin,OUTPUT);
}
 
void loop(){

  buttonstate = digitalRead(button);  // Update the current button state
  Serial.println(buttoncount);
  
  if (buttonstate == LOW && buttonstate != buttonlaststate) {
    buttoncount++;
  }

  if(buttoncount == 6){
    buttoncount = 0;
  }

  dutyCycle = 51*buttoncount;
  
  ledcWrite(ledPin,dutyCycle);
  buttonlaststate = buttonstate;

  // // increase the LED brightness
  // for(int dutyCycle = 0; dutyCycle <= 255; dutyCycle++){   
  //   // changing the LED brightness with PWM
  //   ledcWrite(ledPin, dutyCycle);
  //   // analogWrite(ledPin,dutyCycle);
  //   delay(15);
  // }

  // // decrease the LED brightness
  // for(int dutyCycle = 255; dutyCycle >= 0; dutyCycle--){
  //   // changing the LED brightness with PWM
  //   ledcWrite(ledPin, dutyCycle);   
  //   // analogWrite(ledPin,dutyCycle);
  //   delay(15);
  // }


}