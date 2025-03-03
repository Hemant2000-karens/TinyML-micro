#include<TensorFlowLite.h>

#include "TinyML_int8_datahead.h"
#include "opcode_setting.h"
#include "TinyML_imageCapture.h"
#include "Response_Error_Handle.h"
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

// An area of memory to use for input, output, and intermediate arrays.
// constexpr int kTensorArenaSize = 136 * 1024;
// constexpr int kTensorArenaSize = 750 * 1024;  // 750 KB
constexpr int kTensorArenaSize = 200 * 1024;  // 200 KB

static uint8_t tensor_arena[kTensorArenaSize];
}  // namespace

void setup() {

  static tflite::MicroErrorReporter micro_error_reporter;
  error_reporter = &micro_error_reporter;


   model = tflite::GetModel(_Users_hemant_Downloads_custom_cnn_model_quantized_tflite);
  if (model->version() != TFLITE_SCHEMA_VERSION) {
    TF_LITE_REPORT_ERROR(error_reporter,
                         "Model provided is schema version %d not equal "
                         "to supported version %d.",
                         model->version(), TFLITE_SCHEMA_VERSION);
    return;
  }


 //Model Layer Made here, the same model layer we used while training, the custom layer

// Create an op resolver that supports the required operations
static tflite::MicroMutableOpResolver<5> micro_op_resolver;

micro_op_resolver.AddConv2D();           // Conv2D layer
micro_op_resolver.AddMaxPool2D();        // MaxPooling2D layer
micro_op_resolver.AddAveragePool2D(); // GlobalAveragePooling2D layer
micro_op_resolver.AddFullyConnected();   // Dense layer
micro_op_resolver.AddSoftmax();          // Sigmoid activation

// You can also add any other operations you might need
// micro_op_resolver.AddSoftmax();         // If your model uses Softmax (though your current model doesn't)




  // Model Layers Ends Here
 static tflite::MicroInterpreter static_interpreter(
      model, micro_op_resolver, tensor_arena, kTensorArenaSize, error_reporter);
  interpreter = &static_interpreter;

  // Allocate memory from the tensor_arena for the model's tensors.
  TfLiteStatus allocate_status = interpreter->AllocateTensors();
  if (allocate_status != kTfLiteOk) {
    TF_LITE_REPORT_ERROR(error_reporter, "AllocateTensors() failed");
    return;
  }

  // Get information about the memory area to use for the model's input.
  input = interpreter->input(0);

}

void loop() {

  // Accepting inferences from the camera then Processing it into model
  
  if (kTfLiteOk != GetImage(error_reporter, kNumCols, kNumRows, kNumChannels,
                            input->data.int8)) {
    TF_LITE_REPORT_ERROR(error_reporter, "Image capture failed.");
  }

  // Run the model on this input and make sure it succeeds.
  if (kTfLiteOk != interpreter->Invoke()) {
    TF_LITE_REPORT_ERROR(error_reporter, "Invoke failed.");
  }

  TfLiteTensor* output = interpreter->output(0);

  // Process the inference results.
  int8_t square_result = output->data.uint8[square];
  int8_t circle_result = output->data.uint8[circle];
  ResponseErrorHandling(error_reporter, square_result, circle_result);

}
