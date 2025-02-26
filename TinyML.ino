#include <Nano33BLE_System.h>

#include <ArduinoBLE.h>

// #include <Chirale_TensorFlowLite.h>
#include<tinymodel_int8_datahead.h>

char model[] = _Users_hemant_Downloads_custom_cnn_model_quantized_tflite;
int model_size = _Users_hemant_Downloads_custom_cnn_model_quantized_tflite_len;



void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:

}

void loop() {

  Serial.print(" \n Working on Model");
  // put your main code here, to run repeatedly:

}
