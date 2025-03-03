#include<TensorFlowLite.h>

#include "TinyML_int8_datahead.h"
#include <Nano33BLE_System.h>
#include <ArduinoBLE.h>
#include "opcode_setting.h"
#include "tensorflow/lite/micro/micro_error_reporter.h"
#include "tensorflow/lite/micro/micro_interpreter.h"
#include "tensorflow/lite/micro/micro_mutable_op_resolver.h"
#include "tensorflow/lite/schema/schema_generated.h"
#include "tensorflow/lite/version.h"

// const unsigned char *model = _Users_hemant_Downloads_custom_cnn_model_quantized_tflite;
// const unsigned int model_size = _Users_hemant_Downloads_custom_cnn_model_quantized_tflite_len;


// Globals, used for compatibility with Arduino-style sketches.
namespace {
tflite::ErrorReporter* error_reporter = nullptr;
const tflite::Model *model = nullptr;
tflite::MicroInterpreter* interpreter = nullptr;
TfLiteTensor* input = nullptr;

// In order to use optimized tensorflow lite kernels, a signed int8_t quantized
// model is preferred over the legacy unsigned model format. This means that
// throughout this project, input images must be converted from unisgned to
// signed format. The easiest and quickest way to co.nvert from unsigned to
// signed 8-bit integers is to subtract 128 from the unsigned value to get a
// signed value.

// An area of memory to use for input, output, and intermediate arrays.
// constexpr int kTensorArenaSize = 136 * 1024;
// constexpr int kTensorArenaSize = 750 * 1024;  // 750 KB
constexpr int kTensorArenaSize = 200 * 1024;  // 200 KB

static uint8_t tensor_arena[kTensorArenaSize];
}  // namespace

void setup() {

  Serial.begin(9600);
  // put your setup code here, to run once:

}

void loop() {

  Serial.print(" \n Working on Model");
  // put your main code here, to run repeatedly:

}
