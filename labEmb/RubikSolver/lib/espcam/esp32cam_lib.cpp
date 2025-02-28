#include "esp32cam_lib.h"

// Camera configuration settings
#define PWDN_GPIO_NUM     -1
#define RESET_GPIO_NUM    -1
#define XCLK_GPIO_NUM      0
#define SIOD_GPIO_NUM     26
#define SIOC_GPIO_NUM     27

#define Y9_GPIO_NUM       35
#define Y8_GPIO_NUM       34
#define Y7_GPIO_NUM       39
#define Y6_GPIO_NUM       36
#define Y5_GPIO_NUM       21
#define Y4_GPIO_NUM       19
#define Y3_GPIO_NUM       18
#define Y2_GPIO_NUM        5
#define VSYNC_GPIO_NUM    25
#define HREF_GPIO_NUM     23
#define PCLK_GPIO_NUM     22

void initCamera() {
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
    config.pixel_format = PIXFORMAT_RGB565;

    // Adjust resolution for better color detection
    config.frame_size = FRAMESIZE_QVGA;
    config.fb_count = 1;

    // Initialize the camera
    if (esp_camera_init(&config) != ESP_OK) {
        Serial.println("Camera initialization failed!");
        return;
    }
    Serial.println("Camera initialized successfully.");
}

camera_fb_t* captureImage() {
    camera_fb_t *fb = esp_camera_fb_get();
    if (!fb) {
        Serial.println("Failed to capture image.");
    }
    return fb;
}

String detectCubeColors(camera_fb_t *fb) {
    if (!fb) return "";

    // Example: Simulated detection logic (replace with real processing)
    // Here, we assume a function that processes the image and extracts colors
    String detectedColors = "RRGYBWOYW"; // Example 3x3 Rubik's cube face colors
    
    return detectedColors;
}

void releaseImage(camera_fb_t *fb) {
    if (fb) {
        esp_camera_fb_return(fb);
    }
}
