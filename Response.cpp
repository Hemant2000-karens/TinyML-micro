#include "Response_Error_Handle.h"
#if defined(ARDUINO) && !defined(ARDUINO_ARDUINO_NANO33BLE)
#define ARDUINO_EXCLUDE_CODE
#endif  // defined(ARDUINO) && !defined(ARDUINO_ARDUINO_NANO33BLE)

#ifndef ARDUINO_EXCLUDE_CODE
#include "Arduino.h"

void ResponseErrorHandling(tflite::ErrorReporter* error_reporter, int8_t circle, int8_t square) {
    static bool is_initialized = false;
    if (!is_initialized) {
        // Pins for the built-in RGB LEDs on the Arduino Nano 33 BLE Sense
        pinMode(LEDR, OUTPUT);
        pinMode(LEDG, OUTPUT);
        pinMode(LEDB, OUTPUT);
        is_initialized = true;
    }

    // Turn off all LEDs initially (HIGH = OFF)
    digitalWrite(LEDG, HIGH);
    digitalWrite(LEDR, HIGH);
    digitalWrite(LEDB, HIGH);

    // Flash blue LED after inference (indicating process completed)
    digitalWrite(LEDB, LOW);
    delay(100);
    digitalWrite(LEDB, HIGH);

    // Decision logic based on model output
    if (circle > square) {  
        digitalWrite(LEDG, LOW);  // Green ON for Circle
        digitalWrite(LEDR, HIGH); // Red OFF
    } else {  
        digitalWrite(LEDG, HIGH); // Green OFF
        digitalWrite(LEDR, LOW);  // Red ON for Square
    }

    TF_LITE_REPORT_ERROR(error_reporter, "Circle score: %d, Square score: %d", circle, square);
}

#endif 
