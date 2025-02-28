#define MOTOR  19
#define LED1   18
#define LED2   17
#define button 16

#include <LCD_I2C.h>
LCD_I2C lcd(0x27, 16, 2);

int buttoncount = 0;


bool buttonstate = false;    
bool buttonlaststate = true; 

void setup()
{

  lcd.begin();
  lcd.backlight();
  Serial.begin(9600);
  pinMode(MOTOR, OUTPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(button, INPUT);

  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
}

void loop()
{
  buttonstate = digitalRead(button);  // Update the current button state
  Serial.println(buttoncount);
  
  if (buttonstate == LOW && buttonstate != buttonlaststate) {
    buttoncount++;
  }

  if (buttoncount == 3) {
    buttoncount = 0;
  }

  if (buttoncount > 0) {
    digitalWrite(LED1, HIGH);
  } else {
    digitalWrite(LED1, LOW);
  }

  if (buttoncount > 1) {
    digitalWrite(LED2, HIGH);
    digitalWrite(MOTOR, HIGH);
  } else {
    digitalWrite(LED2, LOW);
    digitalWrite(MOTOR, LOW);
  }

  // if (buttoncount > 2) {
  //   digitalWrite(MOTOR, HIGH);
  // } else {
  //   digitalWrite(MOTOR, LOW);
  // }

  
    lcd.setCursor(0, 0);
    lcd.print(buttoncount);

  buttonlaststate = buttonstate; // Store the current state for next comparison
}
