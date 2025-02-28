#include <WiFi.h>
#include <MQTT.h>

// WiFi credentials
const char ssid[] = "ixvia";
const char pass[] = "12345678";

// MQTT broker details
const char mqtt_broker[] = "test.mosquitto.org";
const char mqtt_topic[] = "test/led";
const char mqtt_client_id[] = "arduino_group_1.32"; // must be a unique value
const int MQTT_PORT = 1883;

// Pin definition for LED
#define led 19

// Global variables
WiFiClient net;
MQTTClient client;
unsigned long lastMillis = 0;
int counter = 0;

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

  // Handle the LED control based on the received payload
  if (payload == "on") {
    digitalWrite(led, HIGH);
    Serial.println("LED turned ON");
  } else if (payload == "off") {
    digitalWrite(led, LOW);
    Serial.println("LED turned OFF");
  }
}

void setup() {
  Serial.begin(9600);
  
  // Initialize LED pin
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW); // Ensure LED is off at start

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

  // Reconnect to MQTT if disconnected
  if (!client.connected()) {
    connect();
  }

  // Publish a message roughly every 2 seconds
  if (millis() - lastMillis > 2000) {
    lastMillis = millis();
    client.publish(mqtt_topic, "Counter = " + String(counter++));
    Serial.println("Message published: Counter = " + String(counter - 1));
  }
}
