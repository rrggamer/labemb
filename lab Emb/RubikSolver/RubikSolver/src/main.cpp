#include "esp_camera.h"
#include <WiFi.h>
#include <PubSubClient.h>
#include "../config/camconfig.h"

// Camera configuration
#define CAMERA_MODEL_AI_THINKER 

// MQTT configuration
const char* mqtt_server = "test.mosquitto.org"; 
const char* mqtt_topic = "rubiks/cmd";      // Topic to listen for commands 
const char* mqtt_publish_topic = "rubiks/color"; // Topic to publish the detected colors
int MQTT_PORT=1883;

WiFiClient espClient;
PubSubClient client(espClient);

// WiFi credentials
const char* ssid = "iloveaut";
const char* password = "autloveme";

// Function Prototypes
void setup_wifi();
void setup_mqtt();
void mqtt_callback(char* topic, byte* payload, unsigned int length);
void setup_camera();
void capture_image();
void detect_colors(uint8_t* image_data, size_t len);

void setup() {
  Serial.begin(115200);
  setup_wifi();
  setup_mqtt();
  setup_camera();
}

void loop() {
  if (!client.connected()) {
    setup_mqtt();
  }
  client.loop();
  delay(1000); 
}

// Setup WiFi
void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to WiFi");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected to WiFi");
}

// MQTT setup
void setup_mqtt() {
  client.setServer(mqtt_server, 1883);
  client.setCallback(mqtt_callback); 
  while (!client.connected()) {
    Serial.print("Connecting to MQTT...");
    if (client.connect("ESP32Cam")) {
      Serial.println("Connected to MQTT");
      client.subscribe(mqtt_topic);
    } else {
      delay(5000);
    }
  }
}

// MQTT callback function
void mqtt_callback(char* topic, byte* payload, unsigned int length) {
  String message = "";
  for (unsigned int i = 0; i < length; i++) {
    message += (char)payload[i];
  }
  
  // If the received message is "capture", take a picture
  if (message == "capture") {
    Serial.println("Capture command received!");
    capture_image();  // Trigger image capture
  }
}

// Setup camera
void setup_camera() {
  camera_config_t config;
  
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = Y2_GPIO_NUM;
  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM;
  config.pin_d4 = Y6_GPIO_NUM;
  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;
  config.pin_d7 = Y9_GPIO_NUM;
  config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM;
  config.pin_vsync = VSYNC_GPIO_NUM;
  config.pin_href = HREF_GPIO_NUM;
  config.pin_sscb_sda = SIOD_GPIO_NUM;
  config.pin_sscb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;
  config.xclk_freq_hz = 20000000;
  config.pixel_format = PIXFORMAT_JPEG; 
  
  if(psramFound()){
    config.frame_size = FRAMESIZE_UXGA;
    config.jpeg_quality = 10;
    config.fb_count = 2;
  } else {
    config.frame_size = FRAMESIZE_SVGA;
    config.jpeg_quality = 12;
    config.fb_count = 1;
  }
  
  // Camera init
  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    Serial.printf("Camera init failed with error 0x%x", err);
    return;
  }

}

// Capture image
void capture_image() {
  camera_fb_t *fb = esp_camera_fb_get();
  if (!fb) {
    Serial.println("Camera capture failed");
    return;
  }
  Serial.println("Image captured");

  // Process image
  detect_colors(fb->buf, fb->len);

  // Free the frame buffer
  esp_camera_fb_return(fb);
}

// Detect colors (simplified example for RGB color detection)
void detect_colors(uint8_t* image_data, size_t len) {
  // Implement color detection logic
  // Example: Convert the image data to a format usable for detecting colors
  String detected_colors = "Red, Blue, Green";  

  // Send the result via MQTT
  client.publish(mqtt_publish_topic, detected_colors.c_str());
}
