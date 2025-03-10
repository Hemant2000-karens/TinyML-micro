#include <TinyMLShield.h>
#include "TinyML_imageCapture.h"
#include "Arduino.h"

#ifndef ARDUINO_EXCLUDE_CODE

// Get an image from the camera module
TfLiteStatus GetImage(tflite::ErrorReporter* error_reporter, int image_width,
                      int image_height, int channels, int8_t* image_data) {

  byte data[176 * 144]; // Receiving QCIF grayscale from camera = 176 * 144 * 1

  static bool g_is_camera_initialized = false;
  static bool serial_is_initialized = false;

  // Initialize camera if necessary
  if (!g_is_camera_initialized) {
    if (!Camera.begin(QCIF, GRAYSCALE, 5, OV7675)) {
      TF_LITE_REPORT_ERROR(error_reporter, "Failed to initialize camera!");
      return kTfLiteError;
    }
    g_is_camera_initialized = true;
  }

  // Read camera data
  Camera.readFrame(data);

  int min_x = (176 - 96) / 2;
  int min_y = (144 - 96) / 2;
  int index = 0;

  // Crop 96x96 image. This lowers FOV, ideally we would downsample but this is simpler. 
  for (int y = min_y; y < min_y + 96; y++) {
    for (int x = min_x; x < min_x + 96; x++) {
      image_data[index++] = static_cast<int8_t>(data[(y * 176) + x] - 128); // convert TF input image to signed 8-bit
    }
  }

  return kTfLiteOk;
}

#endif
