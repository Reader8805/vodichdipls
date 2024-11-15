#include <Arduino.h>
#include "button.hpp"
#include "encoder.hpp"
#include "sensor.hpp"
#include "pid.hpp"
void setup() {
  Serial.begin(9600);
  button_setup();
  encoder_setup();
}

void loop() {
  //button_read();
  // sensor_read();
  encoder_read();
  delay(200);
}


