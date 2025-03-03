#ifndef Response_Error_Handling_H_
#define Response_Error_Handling_H_

#include "tensorflow/lite/c/common.h"
#include "tensorflow/lite/micro/micro_error_reporter.h"

void ResponseErrorHandling(
  tflite::ErrorReporter* error_reporter,
  int8_t circle, int8_t square
);
#endif 