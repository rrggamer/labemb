// Exmaple of using the MQTT library for ESP32 
// Library by Joël Gähwiler
// https://github.com/256dpi/arduino-mqtt
// Modified by Arnan Sipitakiat


#include <WiFi.h>
#include <MQTT.h>

const char ssid[] = "@JumboPlusIoT";
const char pass[] = "12345678";

// const char ssid[] = "ixvia";
// const char pass[] = "12345678";

const char mqtt_broker[]="test.mosquitto.org";
const char mqtt_topic[]="pha/command";
const char mqtt_client_id[]="arduino_group_pha"; // must change this string to a unique value
int MQTT_PORT=1883;

int counter=0;

WiFiClient net;
MQTTClient client;

unsigned long lastMillis = 0;

void connect() {
  Serial.print("checking wifi...");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }

  Serial.print("\nconnecting...");
  while (!client.connect(mqtt_client_id)) {  
    Serial.print(".");
    delay(1000);
  }

  Serial.println("\nconnected!");

  client.subscribe(mqtt_topic);
  // client.unsubscribe("/hello");
}

void messageReceived(String &topic, String &payload) {
  Serial.println("incoming: " + topic + " - " + payload);

  // Note: Do not use the client in the callback to publish, subscribe or
  // unsubscribe as it may cause deadlocks when other things arrive while
  // sending and receiving acknowledgments. Instead, change a global variable,
  // or push to a queue and handle it in the loop after calling `client.loop()`.
}

void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid, pass);

  // Note: Local domain names (e.g. "Computer.local" on OSX) are not supported
  // by Arduino. You need to set the IP address directly.
  client.begin(mqtt_broker, MQTT_PORT, net);
  client.onMessage(messageReceived);

  connect();
}

void loop() {
  client.loop();
  delay(10);  // <- fixes some issues with WiFi stability

  if (!client.connected()) {
    connect();
  }

  // publish a message roughly every second.
  // not that we don't use delay() because we need to keep calling the client.loop()
  // to keep the connection alive
  if (millis() - lastMillis > 2000) {
    lastMillis = millis();
    client.publish(mqtt_topic, "Counter = " + String(counter++));
  }
}