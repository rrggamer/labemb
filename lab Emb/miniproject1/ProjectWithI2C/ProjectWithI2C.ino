#include <WiFi.h>
#include <MQTT.h>
#include <LCD_I2C.h>

// WiFi credentials
const char ssid[] = "@JumboPlusIoT";
const char pass[] = "12345678";

// MQTT broker details
const char mqtt_broker[] = "test.mosquitto.org";
const char mqtt_topic[] = "test/project";
const char mqtt_topicesp[] = "test/esp32data";
const char mqtt_client_id[] = "arduino_group_1.32"; // must be a unique value

const int MQTT_PORT = 1883;

// Pin definition for LED

#define motorPin1 16
#define motorPin2 17
#define motorPin3 18
#define motorPin4 19

LCD_I2C lcd(0x27, 16, 2);

int motorSpeed = 4;  // Delay in milliseconds between each step (controls speed)
int stepsPerLetter = 20; // Number of steps between each letter position
int currentPosition = 0; // Tracks the current position of the motor in steps

// Global variables
WiFiClient net;
MQTTClient client;
unsigned long lastMillis = 0;
int counter = 0;
char lastInput = '\0';

void connect() {
  Serial.print("Checking WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }

  Serial.println("\nWiFi connected!");
  Serial.print("Connecting to MQTT...");
  
  while (!client.connect(mqtt_client_id)) {
    Serial.print(".");
    delay(1000);
  }

  Serial.println("\nConnected to MQTT broker!");

  client.subscribe(mqtt_topic);
}

// MQTT message callback
void messageReceived(String &topic, String &payload) {
  Serial.println("Incoming: " + topic + " - " + payload);

char input = payload[0];
input = toupper(input);

if (input >= 'A' && input <= 'Z') {
      lastInput = input;
      int targetPosition = (input - 'A') * stepsPerLetter; // Map letter to steps
      moveToPosition(targetPosition);
      client.publish(mqtt_topicesp, "Moving To : " + String(input));
      
    }
 
}

void moveToPosition(int targetPosition) {
  int totalSteps = 26 * stepsPerLetter;  // Total steps in a full circle (A-Z loop)
  int counterclockwiseSteps = (targetPosition - currentPosition + totalSteps) % totalSteps;
  int clockwiseSteps = (currentPosition - targetPosition + totalSteps) % totalSteps;

  if (counterclockwiseSteps <= clockwiseSteps) {
    stepCounterClockwise(counterclockwiseSteps);
  } else {
    stepClockwise(clockwiseSteps);
  }

  currentPosition = targetPosition; // Update the current position
}

void stepClockwise(int steps) {
  for (int i = 0; i < steps; i++) {
    step(1, 0, 0, 0);
    step(1, 1, 0, 0);
    step(0, 1, 0, 0);
    step(0, 1, 1, 0);
    step(0, 0, 1, 0);
    step(0, 0, 1, 1);
    step(0, 0, 0, 1);
    step(1, 0, 0, 1);
  }
}

void stepCounterClockwise(int steps) {
  for (int i = 0; i < steps; i++) {
    step(1, 0, 0, 1);
    step(0, 0, 0, 1);
    step(0, 0, 1, 1);
    step(0, 0, 1, 0);
    step(0, 1, 1, 0);
    step(0, 1, 0, 0);
    step(1, 1, 0, 0);
    step(1, 0, 0, 0);
  }
}

void step(int pin1, int pin2, int pin3, int pin4) {
  digitalWrite(motorPin1, pin1);
  digitalWrite(motorPin2, pin2);
  digitalWrite(motorPin3, pin3);
  digitalWrite(motorPin4, pin4);
  delay(motorSpeed);  // Control speed by adjusting this delay
}

void setup() {
  lcd.begin();
  lcd.backlight();

  Serial.begin(9600);

  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);
  


  // Connect to WiFi
  WiFi.begin(ssid, pass);

  // Set up MQTT client
  client.begin(mqtt_broker, MQTT_PORT, net);
  client.onMessage(messageReceived);

  connect();
}

void loop() {
  client.loop();
  delay(10);  // Helps WiFi stability

if (lastInput >= 'A' && lastInput <= 'Z') {
    lcd.setCursor(0, 0);
    lcd.print("Pointing At: ");
    lcd.setCursor(13, 0);
    lcd.print(lastInput);
  }

  // Reconnect to MQTT if disconnected
  if (!client.connected()) {
    connect();
  }

}
