#include <TinyMLShield.h>
#include "TinyML_imageCapture.h"
#include "Arduino.h"

#ifndef ARDUINO_EXCLUDE_CODE

TfLiteStatus GetImage(tflite::ErrorReporter* error_reporter, int image_width,
                      int image_height, int channels, int8_t* image_data) {

  byte data[176 * 144]; // Buffer to store original camera frame
  byte resizedData[224 * 224]; // Buffer for resized image

  static bool g_is_camera_initialized = false;

  // Initialize camera if necessary
  if (!g_is_camera_initialized) {
    if (!Camera.begin(QCIF, GRAYSCALE, 5, OV7675)) {
      TF_LITE_REPORT_ERROR(error_reporter, "Failed to initialize camera!");
      return kTfLiteError;
    }
    g_is_camera_initialized = true;
  }

  // Capture image from camera
  Camera.readFrame(data);

  // Resize function: Nearest Neighbor Interpolation
  for (int y = 0; y < 224; y++) {
    for (int x = 0; x < 224; x++) {
      int srcX = (x * 176) / 224;
      int srcY = (y * 144) / 224;
      resizedData[y * 224 + x] = data[srcY * 176 + srcX];
    }
  }

  // Convert resized image to signed 8-bit format (-128 to 127)
  for (int i = 0; i < 224 * 224; i++) {
    image_data[i] = static_cast<int8_t>(resizedData[i] - 128);
  }

  return kTfLiteOk;
}

#endif
