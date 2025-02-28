#ifndef ESP32CAM_LIB_H
#define ESP32CAM_LIB_H

#include "esp_camera.h"
#include "Arduino.h"

// Camera initialization function
void initCamera();

// Function to capture an image
camera_fb_t* captureImage();

// Function to detect colors from an image and return as a string
String detectCubeColors(camera_fb_t *fb);

// Function to release the captured image memory
void releaseImage(camera_fb_t *fb);

#endif
