  // Exmaple of using the MQTT library for ESP32 
  // Library by Joël Gähwiler
  // https://github.com/256dpi/arduino-mqtt
  // Modified by Arnan Sipitakiat


  #include <WiFi.h>
  #include <MQTT.h>

  #define MOTOR  19
  #define LED1   18
  #define LED2   17
  #define button 16

  #include <LCD_I2C.h>
  LCD_I2C lcd(0x27, 16, 2);

  int buttoncount = 0;
  String motorstatus = "";


  bool buttonstate = false;    
  bool buttonlaststate = true; 


  const char ssid[] = "@JumboPlusIoT";
  const char pass[] = "12345678";

  // const char ssid[] = "ixvia";
  // const char pass[] = "12345678";

  const char mqtt_broker[]="test.mosquitto.org";
  const char mqtt_topic[]="pha/command";
  const char mqtt_topic1[]="pha/commanddata";
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
    
  }

  void messageReceived(String &topic, String &payload) {
    Serial.println("incoming: " + topic + " - " + payload);

    int payloadnum = payload.toInt();  // Use the exact value from the payload as an integer
    buttoncount = payloadnum; 

    

    // Note: Do not use the client in the callback to publish, subscribe or
    // unsubscribe as it may cause deadlocks when other things arrive while
    // sending and receiving acknowledgments. Instead, change a global variable,
    // or push to a queue and handle it in the loop after calling `client.loop()`.
  }

  void setup() {

    lcd.begin();
    lcd.backlight();
    Serial.begin(9600);
    pinMode(MOTOR, OUTPUT);
    pinMode(LED1, OUTPUT);
    pinMode(LED2, OUTPUT);
    pinMode(button, INPUT);

    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
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

    buttonstate = digitalRead(button);  // Update the current button state
    Serial.println(buttoncount);

    if (!client.connected()) {
      connect();
    }

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
      motorstatus = "Spin";
    } else {
      digitalWrite(LED2, LOW);
      digitalWrite(MOTOR, LOW);
      motorstatus = "Stop";
    }
    
    // publish a message roughly every second.
    // not that we don't use delay() because we need to keep calling the client.loop()
    // to keep the connection alive

    lcd.setCursor(0, 0);
    lcd.print(buttoncount);

    buttonlaststate = buttonstate;
    if (millis() - lastMillis > 2000) {
      lastMillis = millis();
      client.publish(mqtt_topic1, "Motor = " + motorstatus);
    }
  }